// Copyright 2022 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "google/cloud/storage/internal/async/connection_impl.h"
#include "google/cloud/storage/async/idempotency_policy.h"
#include "google/cloud/storage/async/options.h"
#include "google/cloud/storage/async/read_all.h"
#include "google/cloud/storage/async/reader.h"
#include "google/cloud/storage/async/resume_policy.h"
#include "google/cloud/storage/async/retry_policy.h"
#include "google/cloud/storage/internal/async/default_options.h"
#include "google/cloud/storage/internal/async/handle_redirect_error.h"
#include "google/cloud/storage/internal/async/insert_object.h"
#include "google/cloud/storage/internal/async/object_descriptor_impl.h"
#include "google/cloud/storage/internal/async/open_object.h"
#include "google/cloud/storage/internal/async/open_stream.h"
#include "google/cloud/storage/internal/async/read_payload_impl.h"
#include "google/cloud/storage/internal/async/reader_connection_impl.h"
#include "google/cloud/storage/internal/async/reader_connection_resume.h"
#include "google/cloud/storage/internal/async/rewriter_connection_impl.h"
#include "google/cloud/storage/internal/async/write_object.h"
#include "google/cloud/storage/internal/async/write_payload_impl.h"
#include "google/cloud/storage/internal/async/writer_connection_buffered.h"
#include "google/cloud/storage/internal/async/writer_connection_finalized.h"
#include "google/cloud/storage/internal/async/writer_connection_impl.h"
#include "google/cloud/storage/internal/async/writer_connection_resumed.h"
#include "google/cloud/storage/internal/crc32c.h"
#include "google/cloud/storage/internal/grpc/channel_refresh.h"
#include "google/cloud/storage/internal/grpc/configure_client_context.h"
#include "google/cloud/storage/internal/grpc/ctype_cord_workaround.h"
#include "google/cloud/storage/internal/grpc/enable_metrics.h"
#include "google/cloud/storage/internal/grpc/object_metadata_parser.h"
#include "google/cloud/storage/internal/grpc/object_request_parser.h"
#include "google/cloud/storage/internal/grpc/scale_stall_timeout.h"
#include "google/cloud/storage/internal/hash_function.h"
#include "google/cloud/storage/internal/hash_function_impl.h"
#include "google/cloud/storage/internal/hash_validator.h"
#include "google/cloud/storage/internal/hash_validator_impl.h"
#include "google/cloud/storage/internal/storage_stub.h"
#include "google/cloud/storage/internal/storage_stub_factory.h"
#include "google/cloud/storage/options.h"
#include "google/cloud/internal/async_read_write_stream_timeout.h"
#include "google/cloud/internal/async_retry_loop.h"
#include "google/cloud/internal/async_streaming_read_rpc_timeout.h"
#include "google/cloud/internal/async_streaming_write_rpc_timeout.h"
#include "google/cloud/internal/make_status.h"
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace storage_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN
namespace {

inline std::unique_ptr<storage_experimental::AsyncRetryPolicy> retry_policy(
    Options const& options) {
  return options.get<storage_experimental::AsyncRetryPolicyOption>()->clone();
}

inline std::unique_ptr<BackoffPolicy> backoff_policy(Options const& options) {
  return options.get<storage::BackoffPolicyOption>()->clone();
}

inline std::unique_ptr<storage_experimental::IdempotencyPolicy>
idempotency_policy(Options const& options) {
  return options.get<storage_experimental::IdempotencyPolicyOption>()();
}

std::unique_ptr<storage::internal::HashFunction> CreateHashFunction(
    Options const& options) {
  auto crc32c = std::unique_ptr<storage::internal::HashFunction>();
  if (options.has<storage_experimental::UseCrc32cValueOption>()) {
    crc32c = std::make_unique<storage::internal::PrecomputedHashFunction>(
        storage::internal::HashValues{
            Crc32cFromProto(
                options.get<storage_experimental::UseCrc32cValueOption>()),
            /*.md5=*/{}});
  } else if (options
                 .get<storage_experimental::EnableCrc32cValidationOption>()) {
    crc32c = std::make_unique<storage::internal::Crc32cHashFunction>();
  }

  auto md5 = std::unique_ptr<storage::internal::HashFunction>();
  if (options.has<storage_experimental::UseMD5ValueOption>()) {
    md5 = std::make_unique<storage::internal::PrecomputedHashFunction>(
        storage::internal::HashValues{
            /*.crc32=*/{},
            MD5FromProto(
                options.get<storage_experimental::UseMD5ValueOption>())});
  } else if (options.get<storage_experimental::EnableMD5ValidationOption>()) {
    md5 = storage::internal::MD5HashFunction::Create();
  }

  if (crc32c && md5) {
    return std::make_unique<storage::internal::CompositeFunction>(
        std::move(crc32c), std::move(md5));
  }
  if (crc32c) return crc32c;
  if (md5) return md5;
  return storage::internal::CreateNullHashFunction();
}

std::unique_ptr<storage::internal::HashValidator> CreateHashValidator(
    google::storage::v2::ReadObjectRequest const& request,
    Options const& options) {
  auto const is_ranged_read =
      request.read_limit() != 0 || request.read_offset() != 0;
  if (is_ranged_read) return storage::internal::CreateNullHashValidator();

  auto const enable_crc32c =
      options.get<storage_experimental::EnableCrc32cValidationOption>();
  auto const enable_md5 =
      options.get<storage_experimental::EnableMD5ValidationOption>();

  if (enable_crc32c && enable_md5) {
    return std::make_unique<storage::internal::CompositeValidator>(
        std::make_unique<storage::internal::Crc32cHashValidator>(),
        std::make_unique<storage::internal::MD5HashValidator>());
  }
  if (!enable_crc32c && !enable_md5) {
    return std::make_unique<storage::internal::NullHashValidator>();
  }
  if (enable_crc32c) {
    return std::make_unique<storage::internal::Crc32cHashValidator>();
  }
  return std::make_unique<storage::internal::MD5HashValidator>();
}

}  // namespace

AsyncConnectionImpl::AsyncConnectionImpl(
    CompletionQueue cq, std::shared_ptr<GrpcChannelRefresh> refresh,
    std::shared_ptr<StorageStub> stub, Options options)
    : cq_(std::move(cq)),
      refresh_(std::move(refresh)),
      stub_(std::move(stub)),
      options_(std::move(options)) {}

future<StatusOr<google::storage::v2::Object>> AsyncConnectionImpl::InsertObject(
    InsertObjectParams p) {
  auto current = internal::MakeImmutableOptions(std::move(p.options));
  auto request = std::move(p.request);
  auto payload = std::move(p.payload);
  auto const idempotency = idempotency_policy(*current)->InsertObject(request);

  auto call = [stub = stub_, payload = std::move(payload),
               id = invocation_id_generator_.MakeInvocationId()](
                  CompletionQueue& cq,
                  std::shared_ptr<grpc::ClientContext> context,
                  google::cloud::internal::ImmutableOptions options,
                  google::storage::v2::WriteObjectRequest const& request) {
    using StreamingRpcTimeout =
        google::cloud::internal::AsyncStreamingWriteRpcTimeout<
            google::storage::v2::WriteObjectRequest,
            google::storage::v2::WriteObjectResponse>;
    auto timeout = ScaleStallTimeout(
        options->get<storage::TransferStallTimeoutOption>(),
        options->get<storage::TransferStallMinimumRateOption>(),
        google::storage::v2::ServiceConstants::MAX_WRITE_CHUNK_BYTES);

    auto hash_function = CreateHashFunction(*options);
    ApplyRoutingHeaders(*context, request.write_object_spec());
    context->AddMetadata("x-goog-gcs-idempotency-token", id);
    auto rpc = stub->AsyncWriteObject(cq, std::move(context), options);
    rpc = std::make_unique<StreamingRpcTimeout>(cq, timeout, timeout,
                                                std::move(rpc));
    auto running = InsertObject::Call(
        std::move(rpc), std::move(hash_function), request,
        WritePayloadImpl::GetImpl(payload), std::move(options));
    return running->Start().then([running](auto f) mutable {
      running.reset();  // extend the life of the co-routine until it co-returns
      return f.get();
    });
  };
  auto retry = retry_policy(*current);
  auto backoff = backoff_policy(*current);
  return google::cloud::internal::AsyncRetryLoop(
      std::move(retry), std::move(backoff), idempotency, cq_, std::move(call),
      std::move(current), std::move(request), __func__);
}

future<
    StatusOr<std::shared_ptr<storage_experimental::ObjectDescriptorConnection>>>
AsyncConnectionImpl::Open(OpenParams p) {
  auto initial_request = google::storage::v2::BidiReadObjectRequest{};
  *initial_request.mutable_read_object_spec() = p.read_spec;
  auto current = internal::MakeImmutableOptions(p.options);
  // Get the policy factory and immediately create a policy.
  auto resume_policy =
      current->get<storage_experimental::ResumePolicyOption>()();

  auto retry = std::shared_ptr<storage_experimental::AsyncRetryPolicy>(
      retry_policy(*current));
  auto backoff =
      std::shared_ptr<storage::BackoffPolicy>(backoff_policy(*current));
  auto const* function_name = __func__;
  auto factory = OpenStreamFactory(
      [stub = stub_, cq = cq_, retry = std::move(retry),
       backoff = std::move(backoff), current = std::move(current),
       function_name](google::storage::v2::BidiReadObjectRequest request) {
        struct DummyRequest {};

        auto call = [stub, request = std::move(request)](
                        CompletionQueue& cq,
                        std::shared_ptr<grpc::ClientContext> context,
                        google::cloud::internal::ImmutableOptions options,
                        DummyRequest const&) mutable {
          auto open = std::make_shared<OpenObject>(
              *stub, cq, std::move(context), std::move(options), request);
          // Extend the lifetime of the coroutine until it finishes.
          return open->Call().then([open, &request](auto f) mutable {
            open.reset();
            auto response = f.get();
            if (response) return response;
            ApplyRedirectErrors(*request.mutable_read_object_spec(),
                                ExtractGrpcStatus(response.status()));
            return response;
          });
        };

        return google::cloud::internal::AsyncRetryLoop(
            retry->clone(), backoff->clone(), Idempotency::kIdempotent, cq,
            std::move(call), current, DummyRequest{}, function_name);
      });

  auto pending = factory(std::move(initial_request));
  using ReturnType =
      std::shared_ptr<storage_experimental::ObjectDescriptorConnection>;
  return pending.then(
      [rp = std::move(resume_policy), fa = std::move(factory),
       rs = std::move(p.read_spec),
       options = std::move(p.options)](auto f) mutable -> StatusOr<ReturnType> {
        auto result = f.get();
        if (!result) return std::move(result).status();

        auto impl = std::make_shared<ObjectDescriptorImpl>(
            std::move(rp), std::move(fa), std::move(rs),
            std::move(result->stream), std::move(options));
        impl->Start(std::move(result->first_response));
        return ReturnType(impl);
      });
}

future<StatusOr<std::unique_ptr<storage_experimental::AsyncReaderConnection>>>
AsyncConnectionImpl::ReadObject(ReadObjectParams p) {
  using ReturnType =
      StatusOr<std::unique_ptr<storage_experimental::AsyncReaderConnection>>;
  auto current = internal::MakeImmutableOptions(std::move(p.options));

  // Get the policy factory and immediately create a policy.
  auto resume_policy =
      current->get<storage_experimental::ResumePolicyOption>()();
  // Create the hash function and validator based on the original request. Note
  // that p.request will be moved-from, so we have to do it relatively early in
  // this function.
  auto hash_function =
      std::make_shared<storage::internal::Crc32cMessageHashFunction>(
          CreateHashFunction(*current));
  auto hash_validator = CreateHashValidator(p.request, *current);

  auto connection_factory = MakeReaderConnectionFactory(
      std::move(current), std::move(p.request), hash_function);
  auto connection = std::make_unique<AsyncReaderConnectionResume>(
      std::move(resume_policy), std::move(hash_function),
      std::move(hash_validator), std::move(connection_factory));

  return make_ready_future(ReturnType(std::move(connection)));
}

future<StatusOr<storage_experimental::ReadPayload>>
AsyncConnectionImpl::ReadObjectRange(ReadObjectParams p) {
  return ReadObject(std::move(p))
      .then([](auto f) -> future<StatusOr<storage_experimental::ReadPayload>> {
        auto r = f.get();
        if (!r) {
          return make_ready_future(StatusOr<storage_experimental::ReadPayload>(
              std::move(r).status()));
        }
        auto token = storage_internal::MakeAsyncToken(r->get());
        return storage_experimental::ReadAll(
            storage_experimental::AsyncReader(*std::move(r)), std::move(token));
      });
}

future<StatusOr<std::unique_ptr<storage_experimental::AsyncWriterConnection>>>
AsyncConnectionImpl::StartAppendableObjectUpload(AppendableUploadParams p) {
  return AppendableObjectUploadImpl(std::move(p));
}

future<StatusOr<std::unique_ptr<storage_experimental::AsyncWriterConnection>>>
AsyncConnectionImpl::ResumeAppendableObjectUpload(AppendableUploadParams p) {
  return AppendableObjectUploadImpl(std::move(p));
}

future<StatusOr<std::unique_ptr<storage_experimental::AsyncWriterConnection>>>
AsyncConnectionImpl::AppendableObjectUploadImpl(AppendableUploadParams p) {
  auto current = internal::MakeImmutableOptions(std::move(p.options));
  auto request = p.request;
  std::int64_t persisted_size = 0;
  std::shared_ptr<storage::internal::HashFunction> hash_function =
      CreateHashFunction(*current);
  auto retry = std::shared_ptr<storage_experimental::AsyncRetryPolicy>(
      retry_policy(*current));
  auto backoff =
      std::shared_ptr<storage::BackoffPolicy>(backoff_policy(*current));
  using StreamingRpcTimeout =
      google::cloud::internal::AsyncStreamingReadWriteRpcTimeout<
          google::storage::v2::BidiWriteObjectRequest,
          google::storage::v2::BidiWriteObjectResponse>;
  struct RequestPlaceholder {};

  using WriteResultFactory =
      std::function<future<StatusOr<WriteObject::WriteResult>>(
          google::storage::v2::BidiWriteObjectRequest)>;

  auto factory = WriteResultFactory(
      [stub = stub_, cq = cq_, retry = std::move(retry),
       // NOLINTNEXTLINE(bugprone-lambda-function-name)
       backoff = std::move(backoff), current, function_name = __func__](
          google::storage::v2::BidiWriteObjectRequest req) {
        auto call = [stub, request = std::move(req)](
                        CompletionQueue& cq,
                        std::shared_ptr<grpc::ClientContext> context,
                        google::cloud::internal::ImmutableOptions options,
                        RequestPlaceholder const&) mutable
            -> future<StatusOr<WriteObject::WriteResult>> {
          auto start_timeout = ScaleStallTimeout(
              options->get<storage::TransferStallTimeoutOption>(),
              options->get<storage::TransferStallMinimumRateOption>(),
              google::storage::v2::ServiceConstants::MAX_WRITE_CHUNK_BYTES);
          auto per_read_timeout = start_timeout;
          auto per_write_timeout = start_timeout;

          // Apply the routing header
          if (request.has_write_object_spec())
            ApplyRoutingHeaders(*context, request.write_object_spec());
          else
            ApplyRoutingHeaders(*context, request.append_object_spec());

          auto rpc = stub->AsyncBidiWriteObject(cq, std::move(context),
                                                std::move(options));
          rpc = std::make_unique<StreamingRpcTimeout>(
              cq, start_timeout, per_read_timeout, per_write_timeout,
              std::move(rpc));
          request.set_state_lookup(true);
          auto open = std::make_shared<WriteObject>(std::move(rpc), request);
          return open->Call().then([open, &request](auto f) mutable {
            open.reset();
            auto response = f.get();
            if (!response) {
              google::rpc::Status grpc_status =
                  ExtractGrpcStatus(response.status());
              EnsureFirstMessageAppendObjectSpec(request, grpc_status);
              ApplyWriteRedirectErrors(*request.mutable_append_object_spec(),
                                       grpc_status);
            }
            return response;
          });
        };

        return google::cloud::internal::AsyncRetryLoop(
            retry->clone(), backoff->clone(), Idempotency::kIdempotent, cq,
            std::move(call), std::move(current), RequestPlaceholder{},
            function_name);
      });

  auto pending = factory(std::move(request));
  return pending.then(
      [current, request = std::move(p.request), persisted_size,
       hash = std::move(hash_function), fa = std::move(factory)](auto f) mutable
      -> StatusOr<
          std::unique_ptr<storage_experimental::AsyncWriterConnection>> {
        auto rpc = f.get();
        if (!rpc) return std::move(rpc).status();
        persisted_size = rpc->first_response.resource().size();
        auto impl = std::make_unique<AsyncWriterConnectionImpl>(
            current, request, std::move(rpc->stream), hash, persisted_size,
            false);
        return MakeWriterConnectionResumed(std::move(fa), std::move(impl),
                                           std::move(request), std::move(hash),
                                           *current);
      });
}

future<StatusOr<std::unique_ptr<storage_experimental::AsyncWriterConnection>>>
AsyncConnectionImpl::StartUnbufferedUpload(UploadParams p) {
  auto current = internal::MakeImmutableOptions(std::move(p.options));

  auto response = StartResumableWrite(current, p.request);
  return response.then([w = WeakFromThis(), current = std::move(current),
                        request = std::move(p.request)](auto f) mutable {
    auto self = w.lock();
    if (auto self = w.lock()) {
      return self->StartUnbufferedUploadImpl(std::move(current),
                                             std::move(request), f.get());
    }
    return make_ready_future(
        StatusOr<std::unique_ptr<storage_experimental::AsyncWriterConnection>>(
            internal::CancelledError("Cannot lock self", GCP_ERROR_INFO())));
  });
}

future<StatusOr<std::unique_ptr<storage_experimental::AsyncWriterConnection>>>
AsyncConnectionImpl::StartBufferedUpload(UploadParams p) {
  auto current = internal::MakeImmutableOptions(p.options);
  auto async_write_object = [c = current, start = p.request,
                             w = WeakFromThis()](
                                std::string const& upload_id) mutable {
    auto query = google::storage::v2::QueryWriteStatusRequest{};
    query.set_upload_id(upload_id);
    *query.mutable_common_object_request_params() =
        start.common_object_request_params();
    if (auto self = w.lock()) return self->ResumeUpload(c, std::move(query));
    return make_ready_future(
        StatusOr<std::unique_ptr<storage_experimental::AsyncWriterConnection>>{
            internal::CancelledError("Cannot lock self", GCP_ERROR_INFO())});
  };
  return StartUnbufferedUpload(std::move(p))
      .then([current = std::move(current),
             async_write_object = std::move(async_write_object)](auto f) mutable
            -> StatusOr<
                std::unique_ptr<storage_experimental::AsyncWriterConnection>> {
        auto w = f.get();
        if (!w) return std::move(w).status();
        auto factory = [upload_id = (*w)->UploadId(),
                        f = std::move(async_write_object)]() mutable {
          return f(upload_id);
        };
        return MakeWriterConnectionBuffered(std::move(factory), *std::move(w),
                                            *current);
      });
}

future<StatusOr<std::unique_ptr<storage_experimental::AsyncWriterConnection>>>
AsyncConnectionImpl::ResumeUnbufferedUpload(ResumeUploadParams p) {
  auto current = internal::MakeImmutableOptions(std::move(p.options));
  return ResumeUpload(current, std::move(p.request));
}

future<StatusOr<std::unique_ptr<storage_experimental::AsyncWriterConnection>>>
AsyncConnectionImpl::ResumeBufferedUpload(ResumeUploadParams p) {
  auto current = internal::MakeImmutableOptions(std::move(p.options));
  // This is a factory to create unbuffered writer connections. We will call
  // it and wrap its result with a BufferedWriterConnection. Cleverly (too
  // cleverly?) this wrapper calls the factory again if it needs to resume an
  // upload.
  auto make_unbuffered = [c = current, query = p.request,
                          w = WeakFromThis()]() mutable {
    if (auto self = w.lock()) return self->ResumeUpload(c, std::move(query));
    return make_ready_future(
        StatusOr<std::unique_ptr<storage_experimental::AsyncWriterConnection>>{
            internal::CancelledError("Cannot lock self", GCP_ERROR_INFO())});
  };

  auto f = make_unbuffered();
  return f.then(
      [current = std::move(current),
       make_unbuffered = std::move(make_unbuffered)](auto f) mutable
      -> StatusOr<
          std::unique_ptr<storage_experimental::AsyncWriterConnection>> {
        auto w = f.get();
        if (!w) return std::move(w).status();
        return MakeWriterConnectionBuffered(std::move(make_unbuffered),
                                            *std::move(w), *current);
      });
}

future<StatusOr<google::storage::v2::Object>>
AsyncConnectionImpl::ComposeObject(ComposeObjectParams p) {
  auto current = internal::MakeImmutableOptions(std::move(p.options));
  auto const idempotency =
      idempotency_policy(*current)->ComposeObject(p.request);
  auto call = [stub = stub_](
                  CompletionQueue& cq,
                  std::shared_ptr<grpc::ClientContext> context,
                  google::cloud::internal::ImmutableOptions options,
                  google::storage::v2::ComposeObjectRequest const& request) {
    return stub->AsyncComposeObject(cq, std::move(context), std::move(options),
                                    request);
  };
  auto retry = retry_policy(*current);
  auto backoff = backoff_policy(*current);
  return google::cloud::internal::AsyncRetryLoop(
      std::move(retry), std::move(backoff), idempotency, cq_, std::move(call),
      current, std::move(p.request), __func__);
}

future<Status> AsyncConnectionImpl::DeleteObject(DeleteObjectParams p) {
  auto current = internal::MakeImmutableOptions(std::move(p.options));
  auto const idempotency =
      idempotency_policy(*current)->DeleteObject(p.request);
  auto retry = retry_policy(*current);
  auto backoff = backoff_policy(*current);
  return google::cloud::internal::AsyncRetryLoop(
      std::move(retry), std::move(backoff), idempotency, cq_,
      [stub = stub_](CompletionQueue& cq,
                     std::shared_ptr<grpc::ClientContext> context,
                     google::cloud::internal::ImmutableOptions options,
                     google::storage::v2::DeleteObjectRequest const& proto) {
        return stub->AsyncDeleteObject(cq, std::move(context),
                                       std::move(options), proto);
      },
      std::move(current), std::move(p.request), __func__);
}

std::shared_ptr<storage_experimental::AsyncRewriterConnection>
AsyncConnectionImpl::RewriteObject(RewriteObjectParams p) {
  auto current = internal::MakeImmutableOptions(std::move(p.options));

  return std::make_shared<RewriterConnectionImpl>(
      cq_, stub_, std::move(current), std::move(p.request));
}

AsyncReaderConnectionFactory AsyncConnectionImpl::MakeReaderConnectionFactory(
    google::cloud::internal::ImmutableOptions current,
    google::storage::v2::ReadObjectRequest request,
    std::shared_ptr<storage::internal::HashFunction> hash_function) {
  using StreamingRpc = google::cloud::internal::AsyncStreamingReadRpc<
      google::storage::v2::ReadObjectResponse>;
  using StreamingRpcTimeout =
      google::cloud::internal::AsyncStreamingReadRpcTimeout<
          google::storage::v2::ReadObjectResponse>;

  auto make_rpc = [stub = stub_](
                      CompletionQueue& cq,
                      std::shared_ptr<grpc::ClientContext> context,
                      google::cloud::internal::ImmutableOptions options,
                      google::storage::v2::ReadObjectRequest const& proto)
      -> future<StatusOr<std::unique_ptr<StreamingRpc>>> {
    auto timeout = ScaleStallTimeout(
        options->get<storage::DownloadStallTimeoutOption>(),
        options->get<storage::DownloadStallMinimumRateOption>(),
        google::storage::v2::ServiceConstants::MAX_READ_CHUNK_BYTES);
    auto rpc = stub->AsyncReadObject(cq, std::move(context), std::move(options),
                                     proto);
    rpc = std::make_unique<StreamingRpcTimeout>(cq, timeout, timeout,
                                                std::move(rpc));
    auto start = rpc->Start();
    return start.then([rpc = std::move(rpc)](auto f) mutable {
      if (f.get()) return make_ready_future(make_status_or(std::move(rpc)));
      auto pending = rpc->Finish();
      return pending.then([rpc = std::move(rpc)](auto f) mutable {
        // Extend the lifetime until Finish() completes, but not any longer.
        rpc.reset();
        auto status = f.get();
        return StatusOr<std::unique_ptr<StreamingRpc>>(std::move(status));
      });
    });
  };

  auto const* caller = __func__;
  return [caller, cq = cq_, current = std::move(current),
          make_rpc = std::move(make_rpc),
          hash_function = std::move(hash_function),
          request = std::move(request)](storage::Generation generation,
                                        std::int64_t received_bytes) mutable {
    UpdateGeneration(request, std::move(generation));
    UpdateReadRange(request, received_bytes);

    // Make this mutable, because it is called only once and we can
    // `std::move()` the captured values.
    auto transform = [current, hash_function](auto f) mutable
        -> StatusOr<
            std::unique_ptr<storage_experimental::AsyncReaderConnection>> {
      auto rpc = f.get();
      if (!rpc) return std::move(rpc).status();
      return std::unique_ptr<storage_experimental::AsyncReaderConnection>(
          std::make_unique<AsyncReaderConnectionImpl>(
              std::move(current), *std::move(rpc), std::move(hash_function)));
    };

    auto retry = retry_policy(*current);
    auto backoff = backoff_policy(*current);
    // Do not use `std::move()` for the captured variables, as we need to keep
    // such variables valid for all factory invocations.
    return google::cloud::internal::AsyncRetryLoop(
               std::move(retry), std::move(backoff), Idempotency::kIdempotent,
               cq, make_rpc, current, request, caller)
        .then(std::move(transform));
  };
}

future<StatusOr<google::storage::v2::StartResumableWriteResponse>>
AsyncConnectionImpl::StartResumableWrite(
    internal::ImmutableOptions current,
    google::storage::v2::StartResumableWriteRequest request) {
  // Starting an upload is always idempotent. The side-effects, if any, are not
  // observable. That is, calling the RPC twice creates two upload sessions, but
  // there is no query, list, or any other RPC that can help you detect if the
  // first call ever happened. Not even billing, the upload id is free and
  // automatically garbage collected.
  auto const idempotency = Idempotency::kIdempotent;
  auto retry = retry_policy(*current);
  auto backoff = backoff_policy(*current);
  return google::cloud::internal::AsyncRetryLoop(
      std::move(retry), std::move(backoff), idempotency, cq_,
      [stub = stub_](
          CompletionQueue& cq, std::shared_ptr<grpc::ClientContext> context,
          google::cloud::internal::ImmutableOptions options,
          google::storage::v2::StartResumableWriteRequest const& proto) {
        internal::ConfigureContext(*context, *options);
        return stub->AsyncStartResumableWrite(cq, std::move(context),
                                              std::move(options), proto);
      },
      std::move(current), std::move(request), __func__);
}

future<StatusOr<google::storage::v2::QueryWriteStatusResponse>>
AsyncConnectionImpl::QueryWriteStatus(
    internal::ImmutableOptions current,
    google::storage::v2::QueryWriteStatusRequest request) {
  // Starting a new upload is always idempotent. Any side-effects of early
  // attempts are not observable.
  auto const idempotency = Idempotency::kIdempotent;
  auto retry = retry_policy(*current);
  auto backoff = backoff_policy(*current);
  return google::cloud::internal::AsyncRetryLoop(
      std::move(retry), std::move(backoff), idempotency, cq_,
      [stub = stub_](
          CompletionQueue& cq, std::shared_ptr<grpc::ClientContext> context,
          google::cloud::internal::ImmutableOptions options,
          google::storage::v2::QueryWriteStatusRequest const& proto) {
        google::cloud::internal::ConfigurePollContext(*context, *options);
        return stub->AsyncQueryWriteStatus(cq, std::move(context),
                                           std::move(options), proto);
      },
      std::move(current), std::move(request), __func__);
}

// Combines a call to QueryWriteStatus and creates an unbuffered upload.
future<StatusOr<std::unique_ptr<storage_experimental::AsyncWriterConnection>>>
AsyncConnectionImpl::ResumeUpload(
    internal::ImmutableOptions current,
    google::storage::v2::QueryWriteStatusRequest query) {
  auto response = QueryWriteStatus(current, query);
  return response.then([w = WeakFromThis(), c = std::move(current),
                        q = std::move(query)](auto f) mutable {
    auto self = w.lock();
    if (auto self = w.lock()) {
      return self->ResumeUnbufferedUploadImpl(std::move(c), std::move(q),
                                              f.get());
    }
    return make_ready_future(
        StatusOr<std::unique_ptr<storage_experimental::AsyncWriterConnection>>(
            internal::CancelledError("Cannot lock self", GCP_ERROR_INFO())));
  });
}

future<StatusOr<std::unique_ptr<storage_experimental::AsyncWriterConnection>>>
AsyncConnectionImpl::StartUnbufferedUploadImpl(
    internal::ImmutableOptions current,
    google::storage::v2::StartResumableWriteRequest request,
    StatusOr<google::storage::v2::StartResumableWriteResponse> response) {
  if (!response) {
    return make_ready_future(
        StatusOr<std::unique_ptr<storage_experimental::AsyncWriterConnection>>(
            std::move(response).status()));
  }
  auto hash_function = CreateHashFunction(*current);
  auto configure =
      [current, upload = response->upload_id()](grpc::ClientContext& context) {
        ApplyResumableUploadRoutingHeader(context, upload);
      };

  auto proto = google::storage::v2::BidiWriteObjectRequest{};
  proto.set_upload_id(*response->mutable_upload_id());
  *proto.mutable_common_object_request_params() =
      std::move(*request.mutable_common_object_request_params());

  return UnbufferedUploadImpl(std::move(current), std::move(configure),
                              std::move(proto), std::move(hash_function), 0);
}

future<StatusOr<std::unique_ptr<storage_experimental::AsyncWriterConnection>>>
AsyncConnectionImpl::ResumeUnbufferedUploadImpl(
    internal::ImmutableOptions current,
    google::storage::v2::QueryWriteStatusRequest query,
    StatusOr<google::storage::v2::QueryWriteStatusResponse> response) {
  if (!response) {
    return make_ready_future(
        StatusOr<std::unique_ptr<storage_experimental::AsyncWriterConnection>>(
            std::move(response).status()));
  }
  if (response->has_resource()) {
    return make_ready_future(
        StatusOr<std::unique_ptr<storage_experimental::AsyncWriterConnection>>(
            std::make_unique<AsyncWriterConnectionFinalized>(
                std::move(*query.mutable_upload_id()),
                std::move(*response->mutable_resource()))));
  }

  // In most cases computing a hash for a resumed upload is not feasible. We
  // lack the data to initialize the hash functions. The one exception is when
  // the upload resumes from the beginning of the file.
  auto hash_function = storage::internal::CreateNullHashFunction();
  if (response->persisted_size() == 0) {
    hash_function = CreateHashFunction(*current);
  }
  auto configure =
      [current, upload_id = query.upload_id()](grpc::ClientContext& context) {
        internal::ConfigureContext(context, *current);
        ApplyResumableUploadRoutingHeader(context, upload_id);
      };
  auto proto = google::storage::v2::BidiWriteObjectRequest{};
  proto.set_upload_id(std::move(*query.mutable_upload_id()));
  *proto.mutable_common_object_request_params() =
      std::move(*query.mutable_common_object_request_params());
  return UnbufferedUploadImpl(std::move(current), std::move(configure),
                              std::move(proto), std::move(hash_function),
                              response->persisted_size());
}

future<StatusOr<std::unique_ptr<storage_experimental::AsyncWriterConnection>>>
AsyncConnectionImpl::UnbufferedUploadImpl(
    internal::ImmutableOptions current,
    std::function<void(grpc::ClientContext&)> configure_context,
    google::storage::v2::BidiWriteObjectRequest request,
    std::shared_ptr<storage::internal::HashFunction> hash_function,
    std::int64_t persisted_size) {
  using StreamingRpc = AsyncWriterConnectionImpl::StreamingRpc;
  using StreamingRpcTimeout =
      google::cloud::internal::AsyncStreamingReadWriteRpcTimeout<
          google::storage::v2::BidiWriteObjectRequest,
          google::storage::v2::BidiWriteObjectResponse>;
  struct RequestPlaceholder {};

  auto call = [stub = stub_, configure_context = std::move(configure_context)](
                  CompletionQueue& cq,
                  std::shared_ptr<grpc::ClientContext> context,
                  google::cloud::internal::ImmutableOptions options,
                  RequestPlaceholder const&)
      -> future<StatusOr<std::unique_ptr<StreamingRpc>>> {
    configure_context(*context);
    auto timeout = ScaleStallTimeout(
        options->get<storage::TransferStallTimeoutOption>(),
        options->get<storage::TransferStallMinimumRateOption>(),
        google::storage::v2::ServiceConstants::MAX_WRITE_CHUNK_BYTES);
    auto rpc =
        stub->AsyncBidiWriteObject(cq, std::move(context), std::move(options));
    rpc = std::make_unique<StreamingRpcTimeout>(cq, timeout, timeout, timeout,
                                                std::move(rpc));
    auto start = rpc->Start();
    return start.then([rpc = std::move(rpc)](auto f) mutable {
      if (f.get()) return make_ready_future(make_status_or(std::move(rpc)));
      auto pending = rpc->Finish();
      return pending.then([rpc = std::move(rpc)](auto f) mutable {
        // Extend the lifetime until Finish() completes, but not any longer.
        rpc.reset();
        auto status = f.get();
        return StatusOr<std::unique_ptr<StreamingRpc>>(std::move(status));
      });
    });
  };

  auto transform = [current, request = std::move(request), persisted_size,
                    hash = std::move(hash_function)](auto f) mutable
      -> StatusOr<
          std::unique_ptr<storage_experimental::AsyncWriterConnection>> {
    auto rpc = f.get();
    if (!rpc) return std::move(rpc).status();
    return std::unique_ptr<storage_experimental::AsyncWriterConnection>(
        std::make_unique<AsyncWriterConnectionImpl>(
            current, std::move(request), *std::move(rpc), std::move(hash),
            persisted_size, true));
  };

  auto retry = retry_policy(*current);
  auto backoff = backoff_policy(*current);
  return google::cloud::internal::AsyncRetryLoop(
             std::move(retry), std::move(backoff), Idempotency::kIdempotent,
             cq_, std::move(call), std::move(current), RequestPlaceholder{},
             __func__)
      .then(std::move(transform));
}

std::shared_ptr<storage_experimental::AsyncConnection> MakeAsyncConnection(
    CompletionQueue cq, Options options) {
  options = DefaultOptionsAsync(std::move(options));
  EnableGrpcMetrics(options);
  auto p = CreateStorageStub(cq, options);
  return std::make_shared<AsyncConnectionImpl>(
      std::move(cq), std::move(p.first), std::move(p.second),
      std::move(options));
}

std::shared_ptr<storage_experimental::AsyncConnection> MakeAsyncConnection(
    CompletionQueue cq, std::shared_ptr<StorageStub> stub, Options options) {
  return std::make_shared<AsyncConnectionImpl>(
      std::move(cq), std::shared_ptr<GrpcChannelRefresh>{}, std::move(stub),
      std::move(options));
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace storage_internal
}  // namespace cloud
}  // namespace google
