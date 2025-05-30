// Copyright 2025 Google LLC
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
// source: google/cloud/oracledatabase/v1/oracledatabase.proto

#include "google/cloud/oracledatabase/v1/oracle_database_connection_idempotency_policy.h"
#include <memory>

namespace google {
namespace cloud {
namespace oracledatabase_v1 {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

using ::google::cloud::Idempotency;

OracleDatabaseConnectionIdempotencyPolicy::
    ~OracleDatabaseConnectionIdempotencyPolicy() = default;

std::unique_ptr<OracleDatabaseConnectionIdempotencyPolicy>
OracleDatabaseConnectionIdempotencyPolicy::clone() const {
  return std::make_unique<OracleDatabaseConnectionIdempotencyPolicy>(*this);
}

Idempotency
OracleDatabaseConnectionIdempotencyPolicy::ListCloudExadataInfrastructures(
    google::cloud::oracledatabase::v1::
        ListCloudExadataInfrastructuresRequest) {  // NOLINT
  return Idempotency::kIdempotent;
}

Idempotency
OracleDatabaseConnectionIdempotencyPolicy::GetCloudExadataInfrastructure(
    google::cloud::oracledatabase::v1::
        GetCloudExadataInfrastructureRequest const&) {
  return Idempotency::kIdempotent;
}

Idempotency
OracleDatabaseConnectionIdempotencyPolicy::CreateCloudExadataInfrastructure(
    google::cloud::oracledatabase::v1::
        CreateCloudExadataInfrastructureRequest const&) {
  return Idempotency::kNonIdempotent;
}

Idempotency
OracleDatabaseConnectionIdempotencyPolicy::DeleteCloudExadataInfrastructure(
    google::cloud::oracledatabase::v1::
        DeleteCloudExadataInfrastructureRequest const&) {
  return Idempotency::kNonIdempotent;
}

Idempotency OracleDatabaseConnectionIdempotencyPolicy::ListCloudVmClusters(
    google::cloud::oracledatabase::v1::ListCloudVmClustersRequest) {  // NOLINT
  return Idempotency::kIdempotent;
}

Idempotency OracleDatabaseConnectionIdempotencyPolicy::GetCloudVmCluster(
    google::cloud::oracledatabase::v1::GetCloudVmClusterRequest const&) {
  return Idempotency::kIdempotent;
}

Idempotency OracleDatabaseConnectionIdempotencyPolicy::CreateCloudVmCluster(
    google::cloud::oracledatabase::v1::CreateCloudVmClusterRequest const&) {
  return Idempotency::kNonIdempotent;
}

Idempotency OracleDatabaseConnectionIdempotencyPolicy::DeleteCloudVmCluster(
    google::cloud::oracledatabase::v1::DeleteCloudVmClusterRequest const&) {
  return Idempotency::kNonIdempotent;
}

Idempotency OracleDatabaseConnectionIdempotencyPolicy::ListEntitlements(
    google::cloud::oracledatabase::v1::ListEntitlementsRequest) {  // NOLINT
  return Idempotency::kIdempotent;
}

Idempotency OracleDatabaseConnectionIdempotencyPolicy::ListDbServers(
    google::cloud::oracledatabase::v1::ListDbServersRequest) {  // NOLINT
  return Idempotency::kIdempotent;
}

Idempotency OracleDatabaseConnectionIdempotencyPolicy::ListDbNodes(
    google::cloud::oracledatabase::v1::ListDbNodesRequest) {  // NOLINT
  return Idempotency::kIdempotent;
}

Idempotency OracleDatabaseConnectionIdempotencyPolicy::ListGiVersions(
    google::cloud::oracledatabase::v1::ListGiVersionsRequest) {  // NOLINT
  return Idempotency::kIdempotent;
}

Idempotency OracleDatabaseConnectionIdempotencyPolicy::ListDbSystemShapes(
    google::cloud::oracledatabase::v1::ListDbSystemShapesRequest) {  // NOLINT
  return Idempotency::kIdempotent;
}

Idempotency OracleDatabaseConnectionIdempotencyPolicy::ListAutonomousDatabases(
    google::cloud::oracledatabase::v1::
        ListAutonomousDatabasesRequest) {  // NOLINT
  return Idempotency::kIdempotent;
}

Idempotency OracleDatabaseConnectionIdempotencyPolicy::GetAutonomousDatabase(
    google::cloud::oracledatabase::v1::GetAutonomousDatabaseRequest const&) {
  return Idempotency::kIdempotent;
}

Idempotency OracleDatabaseConnectionIdempotencyPolicy::CreateAutonomousDatabase(
    google::cloud::oracledatabase::v1::CreateAutonomousDatabaseRequest const&) {
  return Idempotency::kNonIdempotent;
}

Idempotency OracleDatabaseConnectionIdempotencyPolicy::DeleteAutonomousDatabase(
    google::cloud::oracledatabase::v1::DeleteAutonomousDatabaseRequest const&) {
  return Idempotency::kNonIdempotent;
}

Idempotency
OracleDatabaseConnectionIdempotencyPolicy::RestoreAutonomousDatabase(
    google::cloud::oracledatabase::v1::
        RestoreAutonomousDatabaseRequest const&) {
  return Idempotency::kNonIdempotent;
}

Idempotency
OracleDatabaseConnectionIdempotencyPolicy::GenerateAutonomousDatabaseWallet(
    google::cloud::oracledatabase::v1::
        GenerateAutonomousDatabaseWalletRequest const&) {
  return Idempotency::kNonIdempotent;
}

Idempotency OracleDatabaseConnectionIdempotencyPolicy::ListAutonomousDbVersions(
    google::cloud::oracledatabase::v1::
        ListAutonomousDbVersionsRequest) {  // NOLINT
  return Idempotency::kIdempotent;
}

Idempotency
OracleDatabaseConnectionIdempotencyPolicy::ListAutonomousDatabaseCharacterSets(
    google::cloud::oracledatabase::v1::
        ListAutonomousDatabaseCharacterSetsRequest) {  // NOLINT
  return Idempotency::kIdempotent;
}

Idempotency
OracleDatabaseConnectionIdempotencyPolicy::ListAutonomousDatabaseBackups(
    google::cloud::oracledatabase::v1::
        ListAutonomousDatabaseBackupsRequest) {  // NOLINT
  return Idempotency::kIdempotent;
}

Idempotency OracleDatabaseConnectionIdempotencyPolicy::StopAutonomousDatabase(
    google::cloud::oracledatabase::v1::StopAutonomousDatabaseRequest const&) {
  return Idempotency::kNonIdempotent;
}

Idempotency OracleDatabaseConnectionIdempotencyPolicy::StartAutonomousDatabase(
    google::cloud::oracledatabase::v1::StartAutonomousDatabaseRequest const&) {
  return Idempotency::kNonIdempotent;
}

Idempotency
OracleDatabaseConnectionIdempotencyPolicy::RestartAutonomousDatabase(
    google::cloud::oracledatabase::v1::
        RestartAutonomousDatabaseRequest const&) {
  return Idempotency::kNonIdempotent;
}

Idempotency OracleDatabaseConnectionIdempotencyPolicy::ListLocations(
    google::cloud::location::ListLocationsRequest) {  // NOLINT
  return Idempotency::kIdempotent;
}

Idempotency OracleDatabaseConnectionIdempotencyPolicy::GetLocation(
    google::cloud::location::GetLocationRequest const&) {
  return Idempotency::kIdempotent;
}

Idempotency OracleDatabaseConnectionIdempotencyPolicy::ListOperations(
    google::longrunning::ListOperationsRequest) {  // NOLINT
  return Idempotency::kIdempotent;
}

Idempotency OracleDatabaseConnectionIdempotencyPolicy::GetOperation(
    google::longrunning::GetOperationRequest const&) {
  return Idempotency::kIdempotent;
}

Idempotency OracleDatabaseConnectionIdempotencyPolicy::DeleteOperation(
    google::longrunning::DeleteOperationRequest const&) {
  return Idempotency::kNonIdempotent;
}

Idempotency OracleDatabaseConnectionIdempotencyPolicy::CancelOperation(
    google::longrunning::CancelOperationRequest const&) {
  return Idempotency::kNonIdempotent;
}

std::unique_ptr<OracleDatabaseConnectionIdempotencyPolicy>
MakeDefaultOracleDatabaseConnectionIdempotencyPolicy() {
  return std::make_unique<OracleDatabaseConnectionIdempotencyPolicy>();
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace oracledatabase_v1
}  // namespace cloud
}  // namespace google
