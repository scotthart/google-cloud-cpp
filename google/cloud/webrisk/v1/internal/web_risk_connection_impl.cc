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

// Generated by the Codegen C++ plugin.
// If you make any local changes, they will be lost.
// source: google/cloud/webrisk/v1/webrisk.proto

#include "google/cloud/webrisk/v1/internal/web_risk_connection_impl.h"
#include "google/cloud/webrisk/v1/internal/web_risk_option_defaults.h"
#include "google/cloud/background_threads.h"
#include "google/cloud/common_options.h"
#include "google/cloud/grpc_options.h"
#include "google/cloud/internal/async_long_running_operation.h"
#include "google/cloud/internal/pagination_range.h"
#include "google/cloud/internal/retry_loop.h"
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace webrisk_v1_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN
namespace {

std::unique_ptr<webrisk_v1::WebRiskServiceRetryPolicy> retry_policy(
    Options const& options) {
  return options.get<webrisk_v1::WebRiskServiceRetryPolicyOption>()->clone();
}

std::unique_ptr<BackoffPolicy> backoff_policy(Options const& options) {
  return options.get<webrisk_v1::WebRiskServiceBackoffPolicyOption>()->clone();
}

std::unique_ptr<webrisk_v1::WebRiskServiceConnectionIdempotencyPolicy>
idempotency_policy(Options const& options) {
  return options
      .get<webrisk_v1::WebRiskServiceConnectionIdempotencyPolicyOption>()
      ->clone();
}

std::unique_ptr<PollingPolicy> polling_policy(Options const& options) {
  return options.get<webrisk_v1::WebRiskServicePollingPolicyOption>()->clone();
}

}  // namespace

WebRiskServiceConnectionImpl::WebRiskServiceConnectionImpl(
    std::unique_ptr<google::cloud::BackgroundThreads> background,
    std::shared_ptr<webrisk_v1_internal::WebRiskServiceStub> stub,
    Options options)
    : background_(std::move(background)),
      stub_(std::move(stub)),
      options_(internal::MergeOptions(std::move(options),
                                      WebRiskServiceConnection::options())) {}

StatusOr<google::cloud::webrisk::v1::ComputeThreatListDiffResponse>
WebRiskServiceConnectionImpl::ComputeThreatListDiff(
    google::cloud::webrisk::v1::ComputeThreatListDiffRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->ComputeThreatListDiff(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::cloud::webrisk::v1::ComputeThreatListDiffRequest const&
                 request) {
        return stub_->ComputeThreatListDiff(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::cloud::webrisk::v1::SearchUrisResponse>
WebRiskServiceConnectionImpl::SearchUris(
    google::cloud::webrisk::v1::SearchUrisRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->SearchUris(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::cloud::webrisk::v1::SearchUrisRequest const& request) {
        return stub_->SearchUris(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::cloud::webrisk::v1::SearchHashesResponse>
WebRiskServiceConnectionImpl::SearchHashes(
    google::cloud::webrisk::v1::SearchHashesRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->SearchHashes(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::cloud::webrisk::v1::SearchHashesRequest const& request) {
        return stub_->SearchHashes(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::cloud::webrisk::v1::Submission>
WebRiskServiceConnectionImpl::CreateSubmission(
    google::cloud::webrisk::v1::CreateSubmissionRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->CreateSubmission(request),
      [this](
          grpc::ClientContext& context, Options const& options,
          google::cloud::webrisk::v1::CreateSubmissionRequest const& request) {
        return stub_->CreateSubmission(context, options, request);
      },
      *current, request, __func__);
}

future<StatusOr<google::cloud::webrisk::v1::Submission>>
WebRiskServiceConnectionImpl::SubmitUri(
    google::cloud::webrisk::v1::SubmitUriRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  auto request_copy = request;
  auto const idempotent = idempotency_policy(*current)->SubmitUri(request_copy);
  return google::cloud::internal::AsyncLongRunningOperation<
      google::cloud::webrisk::v1::Submission>(
      background_->cq(), current, std::move(request_copy),
      [stub = stub_](
          google::cloud::CompletionQueue& cq,
          std::shared_ptr<grpc::ClientContext> context,
          google::cloud::internal::ImmutableOptions options,
          google::cloud::webrisk::v1::SubmitUriRequest const& request) {
        return stub->AsyncSubmitUri(cq, std::move(context), std::move(options),
                                    request);
      },
      [stub = stub_](google::cloud::CompletionQueue& cq,
                     std::shared_ptr<grpc::ClientContext> context,
                     google::cloud::internal::ImmutableOptions options,
                     google::longrunning::GetOperationRequest const& request) {
        return stub->AsyncGetOperation(cq, std::move(context),
                                       std::move(options), request);
      },
      [stub = stub_](
          google::cloud::CompletionQueue& cq,
          std::shared_ptr<grpc::ClientContext> context,
          google::cloud::internal::ImmutableOptions options,
          google::longrunning::CancelOperationRequest const& request) {
        return stub->AsyncCancelOperation(cq, std::move(context),
                                          std::move(options), request);
      },
      &google::cloud::internal::ExtractLongRunningResultResponse<
          google::cloud::webrisk::v1::Submission>,
      retry_policy(*current), backoff_policy(*current), idempotent,
      polling_policy(*current), __func__);
}

StatusOr<google::longrunning::Operation>
WebRiskServiceConnectionImpl::SubmitUri(
    NoAwaitTag, google::cloud::webrisk::v1::SubmitUriRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->SubmitUri(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::cloud::webrisk::v1::SubmitUriRequest const& request) {
        return stub_->SubmitUri(context, options, request);
      },
      *current, request, __func__);
}

future<StatusOr<google::cloud::webrisk::v1::Submission>>
WebRiskServiceConnectionImpl::SubmitUri(
    google::longrunning::Operation const& operation) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  if (!operation.metadata()
           .Is<typename google::cloud::webrisk::v1::SubmitUriMetadata>()) {
    return make_ready_future<StatusOr<google::cloud::webrisk::v1::Submission>>(
        internal::InvalidArgumentError(
            "operation does not correspond to SubmitUri",
            GCP_ERROR_INFO().WithMetadata("operation",
                                          operation.metadata().DebugString())));
  }

  return google::cloud::internal::AsyncAwaitLongRunningOperation<
      google::cloud::webrisk::v1::Submission>(
      background_->cq(), current, operation,
      [stub = stub_](google::cloud::CompletionQueue& cq,
                     std::shared_ptr<grpc::ClientContext> context,
                     google::cloud::internal::ImmutableOptions options,
                     google::longrunning::GetOperationRequest const& request) {
        return stub->AsyncGetOperation(cq, std::move(context),
                                       std::move(options), request);
      },
      [stub = stub_](
          google::cloud::CompletionQueue& cq,
          std::shared_ptr<grpc::ClientContext> context,
          google::cloud::internal::ImmutableOptions options,
          google::longrunning::CancelOperationRequest const& request) {
        return stub->AsyncCancelOperation(cq, std::move(context),
                                          std::move(options), request);
      },
      &google::cloud::internal::ExtractLongRunningResultResponse<
          google::cloud::webrisk::v1::Submission>,
      polling_policy(*current), __func__);
}

StreamRange<google::longrunning::Operation>
WebRiskServiceConnectionImpl::ListOperations(
    google::longrunning::ListOperationsRequest request) {
  request.clear_page_token();
  auto current = google::cloud::internal::SaveCurrentOptions();
  auto idempotency = idempotency_policy(*current)->ListOperations(request);
  char const* function_name = __func__;
  return google::cloud::internal::MakePaginationRange<
      StreamRange<google::longrunning::Operation>>(
      current, std::move(request),
      [idempotency, function_name, stub = stub_,
       retry = std::shared_ptr<webrisk_v1::WebRiskServiceRetryPolicy>(
           retry_policy(*current)),
       backoff = std::shared_ptr<BackoffPolicy>(backoff_policy(*current))](
          Options const& options,
          google::longrunning::ListOperationsRequest const& r) {
        return google::cloud::internal::RetryLoop(
            retry->clone(), backoff->clone(), idempotency,
            [stub](grpc::ClientContext& context, Options const& options,
                   google::longrunning::ListOperationsRequest const& request) {
              return stub->ListOperations(context, options, request);
            },
            options, r, function_name);
      },
      [](google::longrunning::ListOperationsResponse r) {
        std::vector<google::longrunning::Operation> result(
            r.operations().size());
        auto& messages = *r.mutable_operations();
        std::move(messages.begin(), messages.end(), result.begin());
        return result;
      });
}

StatusOr<google::longrunning::Operation>
WebRiskServiceConnectionImpl::GetOperation(
    google::longrunning::GetOperationRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->GetOperation(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::longrunning::GetOperationRequest const& request) {
        return stub_->GetOperation(context, options, request);
      },
      *current, request, __func__);
}

Status WebRiskServiceConnectionImpl::DeleteOperation(
    google::longrunning::DeleteOperationRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->DeleteOperation(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::longrunning::DeleteOperationRequest const& request) {
        return stub_->DeleteOperation(context, options, request);
      },
      *current, request, __func__);
}

Status WebRiskServiceConnectionImpl::CancelOperation(
    google::longrunning::CancelOperationRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->CancelOperation(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::longrunning::CancelOperationRequest const& request) {
        return stub_->CancelOperation(context, options, request);
      },
      *current, request, __func__);
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace webrisk_v1_internal
}  // namespace cloud
}  // namespace google
