// Copyright 2023 Google LLC
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
// source: google/cloud/gkebackup/v1/gkebackup.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_GKEBACKUP_V1_BACKUP_FOR_GKE_CONNECTION_IDEMPOTENCY_POLICY_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_GKEBACKUP_V1_BACKUP_FOR_GKE_CONNECTION_IDEMPOTENCY_POLICY_H

#include "google/cloud/idempotency.h"
#include "google/cloud/version.h"
#include <google/cloud/gkebackup/v1/gkebackup.grpc.pb.h>
#include <google/cloud/location/locations.grpc.pb.h>
#include <google/iam/v1/iam_policy.grpc.pb.h>
#include <google/longrunning/operations.grpc.pb.h>
#include <memory>

namespace google {
namespace cloud {
namespace gkebackup_v1 {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

class BackupForGKEConnectionIdempotencyPolicy {
 public:
  virtual ~BackupForGKEConnectionIdempotencyPolicy();

  /// Create a new copy of this object.
  virtual std::unique_ptr<BackupForGKEConnectionIdempotencyPolicy> clone()
      const;

  virtual google::cloud::Idempotency CreateBackupPlan(
      google::cloud::gkebackup::v1::CreateBackupPlanRequest const& request);

  virtual google::cloud::Idempotency ListBackupPlans(
      google::cloud::gkebackup::v1::ListBackupPlansRequest request);

  virtual google::cloud::Idempotency GetBackupPlan(
      google::cloud::gkebackup::v1::GetBackupPlanRequest const& request);

  virtual google::cloud::Idempotency UpdateBackupPlan(
      google::cloud::gkebackup::v1::UpdateBackupPlanRequest const& request);

  virtual google::cloud::Idempotency DeleteBackupPlan(
      google::cloud::gkebackup::v1::DeleteBackupPlanRequest const& request);

  virtual google::cloud::Idempotency CreateBackupChannel(
      google::cloud::gkebackup::v1::CreateBackupChannelRequest const& request);

  virtual google::cloud::Idempotency ListBackupChannels(
      google::cloud::gkebackup::v1::ListBackupChannelsRequest request);

  virtual google::cloud::Idempotency GetBackupChannel(
      google::cloud::gkebackup::v1::GetBackupChannelRequest const& request);

  virtual google::cloud::Idempotency UpdateBackupChannel(
      google::cloud::gkebackup::v1::UpdateBackupChannelRequest const& request);

  virtual google::cloud::Idempotency DeleteBackupChannel(
      google::cloud::gkebackup::v1::DeleteBackupChannelRequest const& request);

  virtual google::cloud::Idempotency ListBackupPlanBindings(
      google::cloud::gkebackup::v1::ListBackupPlanBindingsRequest request);

  virtual google::cloud::Idempotency GetBackupPlanBinding(
      google::cloud::gkebackup::v1::GetBackupPlanBindingRequest const& request);

  virtual google::cloud::Idempotency CreateBackup(
      google::cloud::gkebackup::v1::CreateBackupRequest const& request);

  virtual google::cloud::Idempotency ListBackups(
      google::cloud::gkebackup::v1::ListBackupsRequest request);

  virtual google::cloud::Idempotency GetBackup(
      google::cloud::gkebackup::v1::GetBackupRequest const& request);

  virtual google::cloud::Idempotency UpdateBackup(
      google::cloud::gkebackup::v1::UpdateBackupRequest const& request);

  virtual google::cloud::Idempotency DeleteBackup(
      google::cloud::gkebackup::v1::DeleteBackupRequest const& request);

  virtual google::cloud::Idempotency ListVolumeBackups(
      google::cloud::gkebackup::v1::ListVolumeBackupsRequest request);

  virtual google::cloud::Idempotency GetVolumeBackup(
      google::cloud::gkebackup::v1::GetVolumeBackupRequest const& request);

  virtual google::cloud::Idempotency CreateRestorePlan(
      google::cloud::gkebackup::v1::CreateRestorePlanRequest const& request);

  virtual google::cloud::Idempotency ListRestorePlans(
      google::cloud::gkebackup::v1::ListRestorePlansRequest request);

  virtual google::cloud::Idempotency GetRestorePlan(
      google::cloud::gkebackup::v1::GetRestorePlanRequest const& request);

  virtual google::cloud::Idempotency UpdateRestorePlan(
      google::cloud::gkebackup::v1::UpdateRestorePlanRequest const& request);

  virtual google::cloud::Idempotency DeleteRestorePlan(
      google::cloud::gkebackup::v1::DeleteRestorePlanRequest const& request);

  virtual google::cloud::Idempotency CreateRestoreChannel(
      google::cloud::gkebackup::v1::CreateRestoreChannelRequest const& request);

  virtual google::cloud::Idempotency ListRestoreChannels(
      google::cloud::gkebackup::v1::ListRestoreChannelsRequest request);

  virtual google::cloud::Idempotency GetRestoreChannel(
      google::cloud::gkebackup::v1::GetRestoreChannelRequest const& request);

  virtual google::cloud::Idempotency UpdateRestoreChannel(
      google::cloud::gkebackup::v1::UpdateRestoreChannelRequest const& request);

  virtual google::cloud::Idempotency DeleteRestoreChannel(
      google::cloud::gkebackup::v1::DeleteRestoreChannelRequest const& request);

  virtual google::cloud::Idempotency ListRestorePlanBindings(
      google::cloud::gkebackup::v1::ListRestorePlanBindingsRequest request);

  virtual google::cloud::Idempotency GetRestorePlanBinding(
      google::cloud::gkebackup::v1::GetRestorePlanBindingRequest const&
          request);

  virtual google::cloud::Idempotency CreateRestore(
      google::cloud::gkebackup::v1::CreateRestoreRequest const& request);

  virtual google::cloud::Idempotency ListRestores(
      google::cloud::gkebackup::v1::ListRestoresRequest request);

  virtual google::cloud::Idempotency GetRestore(
      google::cloud::gkebackup::v1::GetRestoreRequest const& request);

  virtual google::cloud::Idempotency UpdateRestore(
      google::cloud::gkebackup::v1::UpdateRestoreRequest const& request);

  virtual google::cloud::Idempotency DeleteRestore(
      google::cloud::gkebackup::v1::DeleteRestoreRequest const& request);

  virtual google::cloud::Idempotency ListVolumeRestores(
      google::cloud::gkebackup::v1::ListVolumeRestoresRequest request);

  virtual google::cloud::Idempotency GetVolumeRestore(
      google::cloud::gkebackup::v1::GetVolumeRestoreRequest const& request);

  virtual google::cloud::Idempotency GetBackupIndexDownloadUrl(
      google::cloud::gkebackup::v1::GetBackupIndexDownloadUrlRequest const&
          request);

  virtual google::cloud::Idempotency ListLocations(
      google::cloud::location::ListLocationsRequest request);

  virtual google::cloud::Idempotency GetLocation(
      google::cloud::location::GetLocationRequest const& request);

  virtual google::cloud::Idempotency SetIamPolicy(
      google::iam::v1::SetIamPolicyRequest const& request);

  virtual google::cloud::Idempotency GetIamPolicy(
      google::iam::v1::GetIamPolicyRequest const& request);

  virtual google::cloud::Idempotency TestIamPermissions(
      google::iam::v1::TestIamPermissionsRequest const& request);

  virtual google::cloud::Idempotency ListOperations(
      google::longrunning::ListOperationsRequest request);

  virtual google::cloud::Idempotency GetOperation(
      google::longrunning::GetOperationRequest const& request);

  virtual google::cloud::Idempotency DeleteOperation(
      google::longrunning::DeleteOperationRequest const& request);

  virtual google::cloud::Idempotency CancelOperation(
      google::longrunning::CancelOperationRequest const& request);
};

std::unique_ptr<BackupForGKEConnectionIdempotencyPolicy>
MakeDefaultBackupForGKEConnectionIdempotencyPolicy();

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace gkebackup_v1
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_GKEBACKUP_V1_BACKUP_FOR_GKE_CONNECTION_IDEMPOTENCY_POLICY_H
