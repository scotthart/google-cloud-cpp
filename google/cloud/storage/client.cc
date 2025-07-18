// Copyright 2018 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "google/cloud/storage/client.h"
#include "google/cloud/storage/internal/base64.h"
#include "google/cloud/storage/internal/connection_factory.h"
#include "google/cloud/storage/oauth2/service_account_credentials.h"
#include "google/cloud/internal/absl_str_cat_quiet.h"
#include "google/cloud/internal/curl_handle.h"
#include "google/cloud/internal/curl_options.h"
#include "google/cloud/internal/filesystem.h"
#include "google/cloud/internal/make_status.h"
#include "google/cloud/internal/opentelemetry.h"
#include "google/cloud/log.h"
#include "absl/strings/str_split.h"
#include <fstream>
#include <memory>
#include <string>
#include <thread>
#include <utility>
#include <vector>

namespace google {
namespace cloud {
namespace storage {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

using ::google::cloud::rest_internal::CurlHandle;

static_assert(std::is_copy_constructible<storage::Client>::value,
              "storage::Client must be constructible");
static_assert(std::is_copy_assignable<storage::Client>::value,
              "storage::Client must be assignable");

// This is the constructor used by most applications. We apply the default
// options, and then call the constructor that creates a connection.
Client::Client(Options opts)
    : Client(InternalOnly{},
             internal::DefaultOptionsWithCredentials(std::move(opts))) {}

/// Apply all decorators to @p connection, based on @p opts.
Client::Client(InternalOnly, Options const& opts,
               std::shared_ptr<internal::StorageConnection> connection)
    : Client(InternalOnlyNoDecorations{}, storage_internal::DecorateConnection(
                                              opts, std::move(connection))) {}

/// Create a connection from @p opts, applying all decorators if needed.
Client::Client(InternalOnly, Options const& opts)
    : Client(InternalOnlyNoDecorations{},
             storage_internal::MakeStorageConnection(opts)) {}

StatusOr<Client> Client::CreateDefaultClient() { return Client(Options{}); }

ObjectReadStream Client::ReadObjectImpl(
    internal::ReadObjectRangeRequest const& request) {
  auto source = connection_->ReadObject(request);
  if (!source) {
    ObjectReadStream error_stream(
        std::make_unique<internal::ObjectReadStreambuf>(
            request, std::move(source).status()));
    error_stream.setstate(std::ios::badbit | std::ios::eofbit);
    return error_stream;
  }
  auto stream =
      ObjectReadStream(std::make_unique<internal::ObjectReadStreambuf>(
          request, *std::move(source)));
  (void)stream.peek();
#if !GOOGLE_CLOUD_CPP_HAVE_EXCEPTIONS
  // Without exceptions the streambuf cannot report errors, so we have to
  // manually update the status bits.
  if (!stream.status().ok()) {
    stream.setstate(std::ios::badbit | std::ios::eofbit);
  }
#endif  // GOOGLE_CLOUD_CPP_HAVE_EXCEPTIONS
  return stream;
}

ObjectWriteStream Client::WriteObjectImpl(
    internal::ResumableUploadRequest const& request) {
  auto response = internal::CreateOrResume(*connection_, request);
  if (!response) {
    ObjectWriteStream error_stream(
        std::make_unique<internal::ObjectWriteStreambuf>(
            std::move(response).status()));
    error_stream.setstate(std::ios::badbit | std::ios::eofbit);
    error_stream.Close();
    return error_stream;
  }
  auto const& current = google::cloud::internal::CurrentOptions();
  auto const buffer_size = request.GetOption<UploadBufferSize>().value_or(
      current.get<UploadBufferSizeOption>());
  return ObjectWriteStream(std::make_unique<internal::ObjectWriteStreambuf>(
      connection_, request, std::move(response->upload_id),
      response->committed_size, std::move(response->metadata), buffer_size,
      internal::CreateHashFunction(request),
      internal::HashValues{
          request.GetOption<Crc32cChecksumValue>().value_or(""),
          request.GetOption<MD5HashValue>().value_or(""),
      },
      internal::CreateHashValidator(request),
      request.GetOption<AutoFinalize>().value_or(
          AutoFinalizeConfig::kEnabled)));
}

bool Client::UseSimpleUpload(std::string const& file_name, std::size_t& size) {
  auto status = google::cloud::internal::status(file_name);
  if (!is_regular(status)) {
    return false;
  }
  auto const fs = google::cloud::internal::file_size(file_name);
  auto const& current = google::cloud::internal::CurrentOptions();
  if (fs <= current.get<MaximumSimpleUploadSizeOption>()) {
    size = static_cast<std::size_t>(fs);
    return true;
  }
  return false;
}

StatusOr<ObjectMetadata> Client::UploadFileSimple(
    std::string const& file_name, std::size_t file_size,
    internal::InsertObjectMediaRequest request) {
  auto payload = connection_->UploadFileSimple(file_name, file_size, request);
  if (!payload) return payload.status();
  request.set_payload(*payload.value());
  return connection_->InsertObjectMedia(request);
}

StatusOr<ObjectMetadata> Client::UploadFileResumable(
    std::string const& file_name, internal::ResumableUploadRequest request) {
  auto source = connection_->UploadFileResumable(file_name, request);
  if (!source) return source.status();
  return UploadStreamResumable(*source.value(), request);
}

StatusOr<ObjectMetadata> Client::UploadStreamResumable(
    std::istream& source,
    internal::ResumableUploadRequest const& request) const {
  auto response = internal::CreateOrResume(*connection_, request);
  if (!response) return std::move(response).status();

  if (response->metadata.has_value()) return *std::move(response->metadata);

  // How many bytes of the local file are uploaded to the GCS server.
  auto upload_id = std::move(response->upload_id);
  auto committed_size = response->committed_size;
  auto upload_limit = request.GetOption<UploadLimit>().value_or(
      (std::numeric_limits<std::uint64_t>::max)());
  // If `committed_size == upload_limit`, we will upload an empty string and
  // finalize the upload.
  if (committed_size > upload_limit) {
    return google::cloud::internal::OutOfRangeError(
        absl::StrCat("UploadLimit (", upload_limit,
                     ") is not bigger than the uploaded size (", committed_size,
                     ") on GCS server"),
        GCP_ERROR_INFO());
  }
  source.seekg(committed_size, std::ios::cur);

  // GCS requires chunks to be a multiple of 256KiB.
  auto const& current = google::cloud::internal::CurrentOptions();
  auto chunk_size = internal::UploadChunkRequest::RoundUpToQuantum(
      current.get<UploadBufferSizeOption>());

  // We iterate while `source` is good, the upload size does not reach the
  // `UploadLimit` and the retry policy has not been exhausted.
  bool reach_upload_limit = false;
  internal::ConstBufferSequence buffers(1);
  std::vector<char> buffer(chunk_size);
  std::shared_ptr<internal::HashFunction> hash_function =
      internal::CreateHashFunction(request);
  while (!source.eof() && !reach_upload_limit) {
    // Read a chunk of data from the source file.
    if (upload_limit - committed_size <= chunk_size) {
      // We don't want the `source_size` to exceed `upload_limit`.
      chunk_size = static_cast<std::size_t>(upload_limit - committed_size);
      reach_upload_limit = true;
    }
    source.read(buffer.data(), buffer.size());
    auto gcount = static_cast<std::size_t>(source.gcount());
    auto expected = committed_size + gcount;
    buffers[0] = internal::ConstBuffer{buffer.data(), gcount};
    auto upload_request = [&] {
      bool final_chunk = (gcount < buffer.size()) || reach_upload_limit;
      if (!final_chunk) {
        return internal::UploadChunkRequest(upload_id, committed_size, buffers,
                                            hash_function);
      }
      return internal::UploadChunkRequest(upload_id, committed_size, buffers,
                                          hash_function,
                                          internal::HashValues{});
    }();
    request.ForEachOption(internal::CopyCommonOptions(upload_request));
    auto upload = connection_->UploadChunk(upload_request);
    if (!upload) return std::move(upload).status();
    if (upload->payload.has_value()) return *std::move(upload->payload);
    auto const actual_committed_size = upload->committed_size.value_or(0);
    if (actual_committed_size != expected) {
      // Defensive programming: unless there is a bug, this should be dead code.
      return google::cloud::internal::InternalError(
          absl::StrCat(
              "Mismatch in committed size expected=", expected,
              " got=", actual_committed_size,
              ". This is a bug, please report it at "
              "https://github.com/googleapis/google-cloud-cpp/issues/new"),
          GCP_ERROR_INFO());
    }

    // We only update `committed_size` when uploading is successful.
    committed_size = expected;
  }
  return google::cloud::internal::InternalError(
      "Upload did not complete but source is exhausted", GCP_ERROR_INFO());
}

Status Client::DownloadFileImpl(internal::ReadObjectRangeRequest const& request,
                                std::string const& file_name) {
  auto const* func = __func__;
  auto msg = [&request, &file_name, func](char const* what) {
    std::ostringstream os;
    os << func << "(" << request << ", " << file_name << "): " << what;
    return std::move(os).str();
  };

  auto stream = ReadObjectImpl(request);
  if (stream.bad()) return stream.status();

  // Open the destination file, and immediate raise an exception on failure.
  std::ofstream os(file_name, std::ios::binary);
  if (!os.is_open()) {
    return google::cloud::internal::InvalidArgumentError(
        msg("cannot open download destination file - ofstream::open()"),
        GCP_ERROR_INFO());
  }

  auto const& current = google::cloud::internal::CurrentOptions();
  auto const size = current.get<DownloadBufferSizeOption>();
  std::unique_ptr<char[]> buffer(new char[size]);
  do {
    stream.read(buffer.get(), size);
    os.write(buffer.get(), stream.gcount());
  } while (os.good() && stream.good());
  os.close();
  if (!os.good()) {
    return google::cloud::internal::UnknownError(
        msg("cannot close download destination file - ofstream::close()"),
        GCP_ERROR_INFO());
  }
  if (stream.bad()) return stream.status();
  return Status();
}

std::string Client::SigningEmail(SigningAccount const& signing_account) const {
  if (signing_account.has_value()) {
    return signing_account.value();
  }
  return connection_->client_options().credentials()->AccountEmail();
}

StatusOr<Client::SignBlobResponseRaw> Client::SignBlobImpl(
    SigningAccount const& signing_account, std::string const& string_to_sign) {
  auto credentials = connection_->client_options().credentials();

  // First try to sign locally.
  auto signed_blob = credentials->SignBlob(signing_account, string_to_sign);
  if (signed_blob) {
    return SignBlobResponseRaw{credentials->KeyId(), *std::move(signed_blob)};
  }

  // If signing locally fails that may be because the credentials do not
  // support signing, or because the signing account is different than the
  // credentials account. In either case, try to sign using the API.
  // In this case, however, we want to validate the signing account, because
  // otherwise the errors are almost impossible to troubleshoot.
  auto signing_email = SigningEmail(signing_account);
  if (signing_email.empty()) {
    return google::cloud::internal::InvalidArgumentError(
        "signing account cannot be empty."
        " The client library was unable to fetch a valid signing email from"
        " the configured credentials, and the application did not provide"
        " a value in the `google::cloud::storage::SigningAccount` option.",
        GCP_ERROR_INFO());
  }
  internal::SignBlobRequest sign_request(
      std::move(signing_email), internal::Base64Encode(string_to_sign), {});
  auto response = connection_->SignBlob(sign_request);
  if (!response) return response.status();
  auto decoded = internal::Base64Decode(response->signed_blob);
  if (!decoded) return std::move(decoded).status();
  return SignBlobResponseRaw{response->key_id, *std::move(decoded)};
}

StatusOr<std::string> Client::SignUrlV2(
    internal::V2SignUrlRequest const& request) {
  SigningAccount const& signing_account = request.signing_account();
  auto signed_blob = SignBlobImpl(signing_account, request.StringToSign());
  if (!signed_blob) return std::move(signed_blob).status();

  CurlHandle curl;
  auto encoded = internal::Base64Encode(signed_blob->signed_blob);
  std::string signature = curl.MakeEscapedString(encoded).get();

  std::ostringstream os;
  os << Endpoint() << '/' << request.bucket_name();
  if (!request.object_name().empty()) {
    os << '/' << curl.MakeEscapedString(request.object_name()).get();
  }
  os << "?GoogleAccessId=" << SigningEmail(signing_account)
     << "&Expires=" << request.expiration_time_as_seconds().count()
     << "&Signature=" << signature;

  return std::move(os).str();
}

StatusOr<std::string> Client::SignUrlV4(internal::V4SignUrlRequest request) {
  auto valid = request.Validate();
  if (!valid.ok()) {
    return valid;
  }
  request.AddMissingRequiredHeaders();
  SigningAccount const& signing_account = request.signing_account();
  auto signing_email = SigningEmail(signing_account);

  auto string_to_sign = request.StringToSign(signing_email);
  auto signed_blob = SignBlobImpl(signing_account, string_to_sign);
  if (!signed_blob) {
    return signed_blob.status();
  }

  std::string signature =
      google::cloud::internal::HexEncode(signed_blob->signed_blob);
  CurlHandle curl;
  std::ostringstream os;
  os << request.HostnameWithBucket();
  for (auto& part : request.ObjectNameParts()) {
    os << '/' << curl.MakeEscapedString(part).get();
  }
  os << "?" << request.CanonicalQueryString(signing_email)
     << "&X-Goog-Signature=" << signature;

  return std::move(os).str();
}

StatusOr<PolicyDocumentResult> Client::SignPolicyDocument(
    internal::PolicyDocumentRequest const& request) {
  SigningAccount const& signing_account = request.signing_account();
  auto signing_email = SigningEmail(signing_account);

  auto string_to_sign = request.StringToSign();
  auto base64_policy = internal::Base64Encode(string_to_sign);
  auto signed_blob = SignBlobImpl(signing_account, base64_policy);
  if (!signed_blob) {
    return signed_blob.status();
  }

  return PolicyDocumentResult{
      signing_email, request.policy_document().expiration, base64_policy,
      internal::Base64Encode(signed_blob->signed_blob)};
}

StatusOr<PolicyDocumentV4Result> Client::SignPolicyDocumentV4(
    internal::PolicyDocumentV4Request request) {
  SigningAccount const& signing_account = request.signing_account();
  auto signing_email = SigningEmail(signing_account);
  request.SetSigningEmail(signing_email);

  auto string_to_sign = request.StringToSign();
  auto escaped = internal::PostPolicyV4Escape(string_to_sign);
  if (!escaped) return escaped.status();
  auto base64_policy = internal::Base64Encode(*escaped);
  auto signed_blob = SignBlobImpl(signing_account, base64_policy);
  if (!signed_blob) {
    return signed_blob.status();
  }
  std::string signature =
      google::cloud::internal::HexEncode(signed_blob->signed_blob);
  auto required_fields = request.RequiredFormFields();
  required_fields["x-goog-signature"] = signature;
  required_fields["policy"] = base64_policy;
  return PolicyDocumentV4Result{request.Url(),
                                request.Credentials(),
                                request.ExpirationDate(),
                                base64_policy,
                                signature,
                                "GOOG4-RSA-SHA256",
                                std::move(required_fields)};
}

std::string CreateRandomPrefixName(std::string const& prefix) {
  auto constexpr kPrefixNameSize = 16;
  auto rng = google::cloud::internal::MakeDefaultPRNG();
  return prefix + google::cloud::internal::Sample(rng, kPrefixNameSize,
                                                  "abcdefghijklmnopqrstuvwxyz");
}

std::string Client::Endpoint() const {
  return connection_->options().get<RestEndpointOption>();
}

// This can be optimized to not have a lot of string copies.
// But the code is rarely used and not in any critical path.
std::string Client::EndpointAuthority() const {
  auto endpoint = Endpoint();
  auto endpoint_authority = absl::string_view(endpoint);
  if (!absl::ConsumePrefix(&endpoint_authority, "https://")) {
    absl::ConsumePrefix(&endpoint_authority, "http://");
  }
  return std::string(endpoint_authority);
}

namespace internal {

Client ClientImplDetails::CreateWithDecorations(
    Options const& opts, std::shared_ptr<StorageConnection> connection) {
  return Client(
      Client::InternalOnlyNoDecorations{},
      storage_internal::DecorateConnection(opts, std::move(connection)));
}

ScopedDeleter::ScopedDeleter(
    std::function<Status(std::string, std::int64_t)> df)
    : delete_fun_(std::move(df)) {}

ScopedDeleter::~ScopedDeleter() {
  if (enabled_) {
    ExecuteDelete();
  }
}

void ScopedDeleter::Add(ObjectMetadata const& object) {
  auto generation = object.generation();
  Add(std::move(object).name(), generation);
}

void ScopedDeleter::Add(std::string object_name, std::int64_t generation) {
  object_list_.emplace_back(std::move(object_name), generation);
}

Status ScopedDeleter::ExecuteDelete() {
  std::vector<std::pair<std::string, std::int64_t>> object_list;
  // make sure the dtor will not do this again
  object_list.swap(object_list_);

  // Perform deletion in reverse order. We rely on it in functions which create
  // a "lock" object - it is created as the first file and should be removed as
  // last.
  for (auto object_it = object_list.rbegin(); object_it != object_list.rend();
       ++object_it) {
    Status status = delete_fun_(std::move(object_it->first), object_it->second);
    // Fail on first error. If the service is unavailable, every deletion
    // would potentially keep retrying until the timeout passes - this would
    // take way too much time and would be pointless.
    if (!status.ok()) {
      return status;
    }
  }
  return Status();
}

}  // namespace internal

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace storage
}  // namespace cloud
}  // namespace google
