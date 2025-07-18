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
// source: google/cloud/developerconnect/v1/developer_connect.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_DEVELOPERCONNECT_V1_DEVELOPER_CONNECT_CONNECTION_IDEMPOTENCY_POLICY_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_DEVELOPERCONNECT_V1_DEVELOPER_CONNECT_CONNECTION_IDEMPOTENCY_POLICY_H

#include "google/cloud/idempotency.h"
#include "google/cloud/version.h"
#include <google/cloud/developerconnect/v1/developer_connect.grpc.pb.h>
#include <google/cloud/location/locations.grpc.pb.h>
#include <google/longrunning/operations.grpc.pb.h>
#include <memory>

namespace google {
namespace cloud {
namespace developerconnect_v1 {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

class DeveloperConnectConnectionIdempotencyPolicy {
 public:
  virtual ~DeveloperConnectConnectionIdempotencyPolicy();

  /// Create a new copy of this object.
  virtual std::unique_ptr<DeveloperConnectConnectionIdempotencyPolicy> clone()
      const;

  virtual google::cloud::Idempotency ListConnections(
      google::cloud::developerconnect::v1::ListConnectionsRequest request);

  virtual google::cloud::Idempotency GetConnection(
      google::cloud::developerconnect::v1::GetConnectionRequest const& request);

  virtual google::cloud::Idempotency CreateConnection(
      google::cloud::developerconnect::v1::CreateConnectionRequest const&
          request);

  virtual google::cloud::Idempotency UpdateConnection(
      google::cloud::developerconnect::v1::UpdateConnectionRequest const&
          request);

  virtual google::cloud::Idempotency DeleteConnection(
      google::cloud::developerconnect::v1::DeleteConnectionRequest const&
          request);

  virtual google::cloud::Idempotency CreateGitRepositoryLink(
      google::cloud::developerconnect::v1::CreateGitRepositoryLinkRequest const&
          request);

  virtual google::cloud::Idempotency DeleteGitRepositoryLink(
      google::cloud::developerconnect::v1::DeleteGitRepositoryLinkRequest const&
          request);

  virtual google::cloud::Idempotency ListGitRepositoryLinks(
      google::cloud::developerconnect::v1::ListGitRepositoryLinksRequest
          request);

  virtual google::cloud::Idempotency GetGitRepositoryLink(
      google::cloud::developerconnect::v1::GetGitRepositoryLinkRequest const&
          request);

  virtual google::cloud::Idempotency FetchReadWriteToken(
      google::cloud::developerconnect::v1::FetchReadWriteTokenRequest const&
          request);

  virtual google::cloud::Idempotency FetchReadToken(
      google::cloud::developerconnect::v1::FetchReadTokenRequest const&
          request);

  virtual google::cloud::Idempotency FetchLinkableGitRepositories(
      google::cloud::developerconnect::v1::FetchLinkableGitRepositoriesRequest
          request);

  virtual google::cloud::Idempotency FetchGitHubInstallations(
      google::cloud::developerconnect::v1::
          FetchGitHubInstallationsRequest const& request);

  virtual google::cloud::Idempotency FetchGitRefs(
      google::cloud::developerconnect::v1::FetchGitRefsRequest request);

  virtual google::cloud::Idempotency ListAccountConnectors(
      google::cloud::developerconnect::v1::ListAccountConnectorsRequest
          request);

  virtual google::cloud::Idempotency GetAccountConnector(
      google::cloud::developerconnect::v1::GetAccountConnectorRequest const&
          request);

  virtual google::cloud::Idempotency CreateAccountConnector(
      google::cloud::developerconnect::v1::CreateAccountConnectorRequest const&
          request);

  virtual google::cloud::Idempotency UpdateAccountConnector(
      google::cloud::developerconnect::v1::UpdateAccountConnectorRequest const&
          request);

  virtual google::cloud::Idempotency DeleteAccountConnector(
      google::cloud::developerconnect::v1::DeleteAccountConnectorRequest const&
          request);

  virtual google::cloud::Idempotency FetchAccessToken(
      google::cloud::developerconnect::v1::FetchAccessTokenRequest const&
          request);

  virtual google::cloud::Idempotency ListUsers(
      google::cloud::developerconnect::v1::ListUsersRequest request);

  virtual google::cloud::Idempotency DeleteUser(
      google::cloud::developerconnect::v1::DeleteUserRequest const& request);

  virtual google::cloud::Idempotency FetchSelf(
      google::cloud::developerconnect::v1::FetchSelfRequest const& request);

  virtual google::cloud::Idempotency DeleteSelf(
      google::cloud::developerconnect::v1::DeleteSelfRequest const& request);

  virtual google::cloud::Idempotency ListLocations(
      google::cloud::location::ListLocationsRequest request);

  virtual google::cloud::Idempotency GetLocation(
      google::cloud::location::GetLocationRequest const& request);

  virtual google::cloud::Idempotency ListOperations(
      google::longrunning::ListOperationsRequest request);

  virtual google::cloud::Idempotency GetOperation(
      google::longrunning::GetOperationRequest const& request);

  virtual google::cloud::Idempotency DeleteOperation(
      google::longrunning::DeleteOperationRequest const& request);

  virtual google::cloud::Idempotency CancelOperation(
      google::longrunning::CancelOperationRequest const& request);
};

std::unique_ptr<DeveloperConnectConnectionIdempotencyPolicy>
MakeDefaultDeveloperConnectConnectionIdempotencyPolicy();

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace developerconnect_v1
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_DEVELOPERCONNECT_V1_DEVELOPER_CONNECT_CONNECTION_IDEMPOTENCY_POLICY_H
