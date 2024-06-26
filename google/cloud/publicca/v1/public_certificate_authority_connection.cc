// Copyright 2024 Google LLC
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
// source: google/cloud/security/publicca/v1/service.proto

#include "google/cloud/publicca/v1/public_certificate_authority_connection.h"
#include "google/cloud/publicca/v1/internal/public_certificate_authority_connection_impl.h"
#include "google/cloud/publicca/v1/internal/public_certificate_authority_option_defaults.h"
#include "google/cloud/publicca/v1/internal/public_certificate_authority_stub_factory.h"
#include "google/cloud/publicca/v1/internal/public_certificate_authority_tracing_connection.h"
#include "google/cloud/publicca/v1/public_certificate_authority_options.h"
#include "google/cloud/background_threads.h"
#include "google/cloud/common_options.h"
#include "google/cloud/credentials.h"
#include "google/cloud/grpc_options.h"
#include "google/cloud/internal/unified_grpc_credentials.h"
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace publicca_v1 {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

PublicCertificateAuthorityServiceConnection::
    ~PublicCertificateAuthorityServiceConnection() = default;

StatusOr<google::cloud::security::publicca::v1::ExternalAccountKey>
PublicCertificateAuthorityServiceConnection::CreateExternalAccountKey(
    google::cloud::security::publicca::v1::
        CreateExternalAccountKeyRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

std::shared_ptr<PublicCertificateAuthorityServiceConnection>
MakePublicCertificateAuthorityServiceConnection(Options options) {
  internal::CheckExpectedOptions<
      CommonOptionList, GrpcOptionList, UnifiedCredentialsOptionList,
      PublicCertificateAuthorityServicePolicyOptionList>(options, __func__);
  options =
      publicca_v1_internal::PublicCertificateAuthorityServiceDefaultOptions(
          std::move(options));
  auto background = internal::MakeBackgroundThreadsFactory(options)();
  auto auth = internal::CreateAuthenticationStrategy(background->cq(), options);
  auto stub =
      publicca_v1_internal::CreateDefaultPublicCertificateAuthorityServiceStub(
          std::move(auth), options);
  return publicca_v1_internal::
      MakePublicCertificateAuthorityServiceTracingConnection(
          std::make_shared<publicca_v1_internal::
                               PublicCertificateAuthorityServiceConnectionImpl>(
              std::move(background), std::move(stub), std::move(options)));
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace publicca_v1
}  // namespace cloud
}  // namespace google
