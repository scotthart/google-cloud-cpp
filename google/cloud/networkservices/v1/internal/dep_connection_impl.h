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
// source: google/cloud/networkservices/v1/dep.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_NETWORKSERVICES_V1_INTERNAL_DEP_CONNECTION_IMPL_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_NETWORKSERVICES_V1_INTERNAL_DEP_CONNECTION_IMPL_H

#include "google/cloud/networkservices/v1/dep_connection.h"
#include "google/cloud/networkservices/v1/dep_connection_idempotency_policy.h"
#include "google/cloud/networkservices/v1/dep_options.h"
#include "google/cloud/networkservices/v1/internal/dep_retry_traits.h"
#include "google/cloud/networkservices/v1/internal/dep_stub.h"
#include "google/cloud/background_threads.h"
#include "google/cloud/backoff_policy.h"
#include "google/cloud/future.h"
#include "google/cloud/options.h"
#include "google/cloud/polling_policy.h"
#include "google/cloud/status_or.h"
#include "google/cloud/stream_range.h"
#include "google/cloud/version.h"
#include <google/longrunning/operations.grpc.pb.h>
#include <memory>

namespace google {
namespace cloud {
namespace networkservices_v1_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

class DepServiceConnectionImpl
    : public networkservices_v1::DepServiceConnection {
 public:
  ~DepServiceConnectionImpl() override = default;

  DepServiceConnectionImpl(
      std::unique_ptr<google::cloud::BackgroundThreads> background,
      std::shared_ptr<networkservices_v1_internal::DepServiceStub> stub,
      Options options);

  Options options() override { return options_; }

  StreamRange<google::cloud::networkservices::v1::LbTrafficExtension>
  ListLbTrafficExtensions(
      google::cloud::networkservices::v1::ListLbTrafficExtensionsRequest
          request) override;

  StatusOr<google::cloud::networkservices::v1::LbTrafficExtension>
  GetLbTrafficExtension(
      google::cloud::networkservices::v1::GetLbTrafficExtensionRequest const&
          request) override;

  future<StatusOr<google::cloud::networkservices::v1::LbTrafficExtension>>
  CreateLbTrafficExtension(
      google::cloud::networkservices::v1::CreateLbTrafficExtensionRequest const&
          request) override;

  StatusOr<google::longrunning::Operation> CreateLbTrafficExtension(
      NoAwaitTag,
      google::cloud::networkservices::v1::CreateLbTrafficExtensionRequest const&
          request) override;

  future<StatusOr<google::cloud::networkservices::v1::LbTrafficExtension>>
  CreateLbTrafficExtension(
      google::longrunning::Operation const& operation) override;

  future<StatusOr<google::cloud::networkservices::v1::LbTrafficExtension>>
  UpdateLbTrafficExtension(
      google::cloud::networkservices::v1::UpdateLbTrafficExtensionRequest const&
          request) override;

  StatusOr<google::longrunning::Operation> UpdateLbTrafficExtension(
      NoAwaitTag,
      google::cloud::networkservices::v1::UpdateLbTrafficExtensionRequest const&
          request) override;

  future<StatusOr<google::cloud::networkservices::v1::LbTrafficExtension>>
  UpdateLbTrafficExtension(
      google::longrunning::Operation const& operation) override;

  future<StatusOr<google::cloud::networkservices::v1::OperationMetadata>>
  DeleteLbTrafficExtension(
      google::cloud::networkservices::v1::DeleteLbTrafficExtensionRequest const&
          request) override;

  StatusOr<google::longrunning::Operation> DeleteLbTrafficExtension(
      NoAwaitTag,
      google::cloud::networkservices::v1::DeleteLbTrafficExtensionRequest const&
          request) override;

  future<StatusOr<google::cloud::networkservices::v1::OperationMetadata>>
  DeleteLbTrafficExtension(
      google::longrunning::Operation const& operation) override;

  StreamRange<google::cloud::networkservices::v1::LbRouteExtension>
  ListLbRouteExtensions(
      google::cloud::networkservices::v1::ListLbRouteExtensionsRequest request)
      override;

  StatusOr<google::cloud::networkservices::v1::LbRouteExtension>
  GetLbRouteExtension(
      google::cloud::networkservices::v1::GetLbRouteExtensionRequest const&
          request) override;

  future<StatusOr<google::cloud::networkservices::v1::LbRouteExtension>>
  CreateLbRouteExtension(
      google::cloud::networkservices::v1::CreateLbRouteExtensionRequest const&
          request) override;

  StatusOr<google::longrunning::Operation> CreateLbRouteExtension(
      NoAwaitTag,
      google::cloud::networkservices::v1::CreateLbRouteExtensionRequest const&
          request) override;

  future<StatusOr<google::cloud::networkservices::v1::LbRouteExtension>>
  CreateLbRouteExtension(
      google::longrunning::Operation const& operation) override;

  future<StatusOr<google::cloud::networkservices::v1::LbRouteExtension>>
  UpdateLbRouteExtension(
      google::cloud::networkservices::v1::UpdateLbRouteExtensionRequest const&
          request) override;

  StatusOr<google::longrunning::Operation> UpdateLbRouteExtension(
      NoAwaitTag,
      google::cloud::networkservices::v1::UpdateLbRouteExtensionRequest const&
          request) override;

  future<StatusOr<google::cloud::networkservices::v1::LbRouteExtension>>
  UpdateLbRouteExtension(
      google::longrunning::Operation const& operation) override;

  future<StatusOr<google::cloud::networkservices::v1::OperationMetadata>>
  DeleteLbRouteExtension(
      google::cloud::networkservices::v1::DeleteLbRouteExtensionRequest const&
          request) override;

  StatusOr<google::longrunning::Operation> DeleteLbRouteExtension(
      NoAwaitTag,
      google::cloud::networkservices::v1::DeleteLbRouteExtensionRequest const&
          request) override;

  future<StatusOr<google::cloud::networkservices::v1::OperationMetadata>>
  DeleteLbRouteExtension(
      google::longrunning::Operation const& operation) override;

  StreamRange<google::cloud::networkservices::v1::AuthzExtension>
  ListAuthzExtensions(
      google::cloud::networkservices::v1::ListAuthzExtensionsRequest request)
      override;

  StatusOr<google::cloud::networkservices::v1::AuthzExtension>
  GetAuthzExtension(
      google::cloud::networkservices::v1::GetAuthzExtensionRequest const&
          request) override;

  future<StatusOr<google::cloud::networkservices::v1::AuthzExtension>>
  CreateAuthzExtension(
      google::cloud::networkservices::v1::CreateAuthzExtensionRequest const&
          request) override;

  StatusOr<google::longrunning::Operation> CreateAuthzExtension(
      NoAwaitTag,
      google::cloud::networkservices::v1::CreateAuthzExtensionRequest const&
          request) override;

  future<StatusOr<google::cloud::networkservices::v1::AuthzExtension>>
  CreateAuthzExtension(
      google::longrunning::Operation const& operation) override;

  future<StatusOr<google::cloud::networkservices::v1::AuthzExtension>>
  UpdateAuthzExtension(
      google::cloud::networkservices::v1::UpdateAuthzExtensionRequest const&
          request) override;

  StatusOr<google::longrunning::Operation> UpdateAuthzExtension(
      NoAwaitTag,
      google::cloud::networkservices::v1::UpdateAuthzExtensionRequest const&
          request) override;

  future<StatusOr<google::cloud::networkservices::v1::AuthzExtension>>
  UpdateAuthzExtension(
      google::longrunning::Operation const& operation) override;

  future<StatusOr<google::cloud::networkservices::v1::OperationMetadata>>
  DeleteAuthzExtension(
      google::cloud::networkservices::v1::DeleteAuthzExtensionRequest const&
          request) override;

  StatusOr<google::longrunning::Operation> DeleteAuthzExtension(
      NoAwaitTag,
      google::cloud::networkservices::v1::DeleteAuthzExtensionRequest const&
          request) override;

  future<StatusOr<google::cloud::networkservices::v1::OperationMetadata>>
  DeleteAuthzExtension(
      google::longrunning::Operation const& operation) override;

  StreamRange<google::cloud::location::Location> ListLocations(
      google::cloud::location::ListLocationsRequest request) override;

  StatusOr<google::cloud::location::Location> GetLocation(
      google::cloud::location::GetLocationRequest const& request) override;

  StatusOr<google::iam::v1::Policy> SetIamPolicy(
      google::iam::v1::SetIamPolicyRequest const& request) override;

  StatusOr<google::iam::v1::Policy> GetIamPolicy(
      google::iam::v1::GetIamPolicyRequest const& request) override;

  StatusOr<google::iam::v1::TestIamPermissionsResponse> TestIamPermissions(
      google::iam::v1::TestIamPermissionsRequest const& request) override;

  StreamRange<google::longrunning::Operation> ListOperations(
      google::longrunning::ListOperationsRequest request) override;

  StatusOr<google::longrunning::Operation> GetOperation(
      google::longrunning::GetOperationRequest const& request) override;

  Status DeleteOperation(
      google::longrunning::DeleteOperationRequest const& request) override;

  Status CancelOperation(
      google::longrunning::CancelOperationRequest const& request) override;

 private:
  std::unique_ptr<google::cloud::BackgroundThreads> background_;
  std::shared_ptr<networkservices_v1_internal::DepServiceStub> stub_;
  Options options_;
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace networkservices_v1_internal
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_NETWORKSERVICES_V1_INTERNAL_DEP_CONNECTION_IMPL_H
