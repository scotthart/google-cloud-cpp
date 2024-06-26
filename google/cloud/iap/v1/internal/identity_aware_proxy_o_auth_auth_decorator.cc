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
// source: google/cloud/iap/v1/service.proto

#include "google/cloud/iap/v1/internal/identity_aware_proxy_o_auth_auth_decorator.h"
#include <google/cloud/iap/v1/service.grpc.pb.h>
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace iap_v1_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

IdentityAwareProxyOAuthServiceAuth::IdentityAwareProxyOAuthServiceAuth(
    std::shared_ptr<google::cloud::internal::GrpcAuthenticationStrategy> auth,
    std::shared_ptr<IdentityAwareProxyOAuthServiceStub> child)
    : auth_(std::move(auth)), child_(std::move(child)) {}

StatusOr<google::cloud::iap::v1::ListBrandsResponse>
IdentityAwareProxyOAuthServiceAuth::ListBrands(
    grpc::ClientContext& context, Options const& options,
    google::cloud::iap::v1::ListBrandsRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->ListBrands(context, options, request);
}

StatusOr<google::cloud::iap::v1::Brand>
IdentityAwareProxyOAuthServiceAuth::CreateBrand(
    grpc::ClientContext& context, Options const& options,
    google::cloud::iap::v1::CreateBrandRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->CreateBrand(context, options, request);
}

StatusOr<google::cloud::iap::v1::Brand>
IdentityAwareProxyOAuthServiceAuth::GetBrand(
    grpc::ClientContext& context, Options const& options,
    google::cloud::iap::v1::GetBrandRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->GetBrand(context, options, request);
}

StatusOr<google::cloud::iap::v1::IdentityAwareProxyClient>
IdentityAwareProxyOAuthServiceAuth::CreateIdentityAwareProxyClient(
    grpc::ClientContext& context, Options const& options,
    google::cloud::iap::v1::CreateIdentityAwareProxyClientRequest const&
        request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->CreateIdentityAwareProxyClient(context, options, request);
}

StatusOr<google::cloud::iap::v1::ListIdentityAwareProxyClientsResponse>
IdentityAwareProxyOAuthServiceAuth::ListIdentityAwareProxyClients(
    grpc::ClientContext& context, Options const& options,
    google::cloud::iap::v1::ListIdentityAwareProxyClientsRequest const&
        request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->ListIdentityAwareProxyClients(context, options, request);
}

StatusOr<google::cloud::iap::v1::IdentityAwareProxyClient>
IdentityAwareProxyOAuthServiceAuth::GetIdentityAwareProxyClient(
    grpc::ClientContext& context, Options const& options,
    google::cloud::iap::v1::GetIdentityAwareProxyClientRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->GetIdentityAwareProxyClient(context, options, request);
}

StatusOr<google::cloud::iap::v1::IdentityAwareProxyClient>
IdentityAwareProxyOAuthServiceAuth::ResetIdentityAwareProxyClientSecret(
    grpc::ClientContext& context, Options const& options,
    google::cloud::iap::v1::ResetIdentityAwareProxyClientSecretRequest const&
        request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->ResetIdentityAwareProxyClientSecret(context, options, request);
}

Status IdentityAwareProxyOAuthServiceAuth::DeleteIdentityAwareProxyClient(
    grpc::ClientContext& context, Options const& options,
    google::cloud::iap::v1::DeleteIdentityAwareProxyClientRequest const&
        request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->DeleteIdentityAwareProxyClient(context, options, request);
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace iap_v1_internal
}  // namespace cloud
}  // namespace google
