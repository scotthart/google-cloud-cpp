// Copyright 2021 Google LLC
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
// source: google/spanner/admin/database/v1/spanner_database_admin.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_SPANNER_ADMIN_DATABASE_ADMIN_CONNECTION_IDEMPOTENCY_POLICY_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_SPANNER_ADMIN_DATABASE_ADMIN_CONNECTION_IDEMPOTENCY_POLICY_H

#include "google/cloud/idempotency.h"
#include "google/cloud/version.h"
#include <google/longrunning/operations.grpc.pb.h>
#include <google/spanner/admin/database/v1/spanner_database_admin.grpc.pb.h>
#include <memory>

namespace google {
namespace cloud {
namespace spanner_admin {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

class DatabaseAdminConnectionIdempotencyPolicy {
 public:
  virtual ~DatabaseAdminConnectionIdempotencyPolicy();

  /// Create a new copy of this object.
  virtual std::unique_ptr<DatabaseAdminConnectionIdempotencyPolicy> clone()
      const;

  virtual google::cloud::Idempotency ListDatabases(
      google::spanner::admin::database::v1::ListDatabasesRequest request);

  virtual google::cloud::Idempotency CreateDatabase(
      google::spanner::admin::database::v1::CreateDatabaseRequest const&
          request);

  virtual google::cloud::Idempotency GetDatabase(
      google::spanner::admin::database::v1::GetDatabaseRequest const& request);

  virtual google::cloud::Idempotency UpdateDatabase(
      google::spanner::admin::database::v1::UpdateDatabaseRequest const&
          request);

  virtual google::cloud::Idempotency UpdateDatabaseDdl(
      google::spanner::admin::database::v1::UpdateDatabaseDdlRequest const&
          request);

  virtual google::cloud::Idempotency DropDatabase(
      google::spanner::admin::database::v1::DropDatabaseRequest const& request);

  virtual google::cloud::Idempotency GetDatabaseDdl(
      google::spanner::admin::database::v1::GetDatabaseDdlRequest const&
          request);

  virtual google::cloud::Idempotency SetIamPolicy(
      google::iam::v1::SetIamPolicyRequest const& request);

  virtual google::cloud::Idempotency GetIamPolicy(
      google::iam::v1::GetIamPolicyRequest const& request);

  virtual google::cloud::Idempotency TestIamPermissions(
      google::iam::v1::TestIamPermissionsRequest const& request);

  virtual google::cloud::Idempotency CreateBackup(
      google::spanner::admin::database::v1::CreateBackupRequest const& request);

  virtual google::cloud::Idempotency CopyBackup(
      google::spanner::admin::database::v1::CopyBackupRequest const& request);

  virtual google::cloud::Idempotency GetBackup(
      google::spanner::admin::database::v1::GetBackupRequest const& request);

  virtual google::cloud::Idempotency UpdateBackup(
      google::spanner::admin::database::v1::UpdateBackupRequest const& request);

  virtual google::cloud::Idempotency DeleteBackup(
      google::spanner::admin::database::v1::DeleteBackupRequest const& request);

  virtual google::cloud::Idempotency ListBackups(
      google::spanner::admin::database::v1::ListBackupsRequest request);

  virtual google::cloud::Idempotency RestoreDatabase(
      google::spanner::admin::database::v1::RestoreDatabaseRequest const&
          request);

  virtual google::cloud::Idempotency ListDatabaseOperations(
      google::spanner::admin::database::v1::ListDatabaseOperationsRequest
          request);

  virtual google::cloud::Idempotency ListBackupOperations(
      google::spanner::admin::database::v1::ListBackupOperationsRequest
          request);

  virtual google::cloud::Idempotency ListDatabaseRoles(
      google::spanner::admin::database::v1::ListDatabaseRolesRequest request);

  virtual google::cloud::Idempotency AddSplitPoints(
      google::spanner::admin::database::v1::AddSplitPointsRequest const&
          request);

  virtual google::cloud::Idempotency CreateBackupSchedule(
      google::spanner::admin::database::v1::CreateBackupScheduleRequest const&
          request);

  virtual google::cloud::Idempotency GetBackupSchedule(
      google::spanner::admin::database::v1::GetBackupScheduleRequest const&
          request);

  virtual google::cloud::Idempotency UpdateBackupSchedule(
      google::spanner::admin::database::v1::UpdateBackupScheduleRequest const&
          request);

  virtual google::cloud::Idempotency DeleteBackupSchedule(
      google::spanner::admin::database::v1::DeleteBackupScheduleRequest const&
          request);

  virtual google::cloud::Idempotency ListBackupSchedules(
      google::spanner::admin::database::v1::ListBackupSchedulesRequest request);

  virtual google::cloud::Idempotency InternalUpdateGraphOperation(
      google::spanner::admin::database::v1::
          InternalUpdateGraphOperationRequest const& request);

  virtual google::cloud::Idempotency ListOperations(
      google::longrunning::ListOperationsRequest request);

  virtual google::cloud::Idempotency GetOperation(
      google::longrunning::GetOperationRequest const& request);

  virtual google::cloud::Idempotency DeleteOperation(
      google::longrunning::DeleteOperationRequest const& request);

  virtual google::cloud::Idempotency CancelOperation(
      google::longrunning::CancelOperationRequest const& request);
};

std::unique_ptr<DatabaseAdminConnectionIdempotencyPolicy>
MakeDefaultDatabaseAdminConnectionIdempotencyPolicy();

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
namespace gcpcxxV1 = GOOGLE_CLOUD_CPP_NS;  // NOLINT(misc-unused-alias-decls)
}  // namespace spanner_admin
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_SPANNER_ADMIN_DATABASE_ADMIN_CONNECTION_IDEMPOTENCY_POLICY_H
