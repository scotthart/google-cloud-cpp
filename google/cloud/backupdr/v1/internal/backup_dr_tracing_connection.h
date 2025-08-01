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
// source: google/cloud/backupdr/v1/backupdr.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BACKUPDR_V1_INTERNAL_BACKUP_DR_TRACING_CONNECTION_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BACKUPDR_V1_INTERNAL_BACKUP_DR_TRACING_CONNECTION_H

#include "google/cloud/backupdr/v1/backup_dr_connection.h"
#include "google/cloud/version.h"
#include <memory>

namespace google {
namespace cloud {
namespace backupdr_v1_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

#ifdef GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY

class BackupDRTracingConnection : public backupdr_v1::BackupDRConnection {
 public:
  ~BackupDRTracingConnection() override = default;

  explicit BackupDRTracingConnection(
      std::shared_ptr<backupdr_v1::BackupDRConnection> child);

  Options options() override { return child_->options(); }

  StreamRange<google::cloud::backupdr::v1::ManagementServer>
  ListManagementServers(
      google::cloud::backupdr::v1::ListManagementServersRequest request)
      override;

  StatusOr<google::cloud::backupdr::v1::ManagementServer> GetManagementServer(
      google::cloud::backupdr::v1::GetManagementServerRequest const& request)
      override;

  future<StatusOr<google::cloud::backupdr::v1::ManagementServer>>
  CreateManagementServer(
      google::cloud::backupdr::v1::CreateManagementServerRequest const& request)
      override;

  StatusOr<google::longrunning::Operation> CreateManagementServer(
      NoAwaitTag,
      google::cloud::backupdr::v1::CreateManagementServerRequest const& request)
      override;

  future<StatusOr<google::cloud::backupdr::v1::ManagementServer>>
  CreateManagementServer(
      google::longrunning::Operation const& operation) override;

  future<StatusOr<google::cloud::backupdr::v1::OperationMetadata>>
  DeleteManagementServer(
      google::cloud::backupdr::v1::DeleteManagementServerRequest const& request)
      override;

  StatusOr<google::longrunning::Operation> DeleteManagementServer(
      NoAwaitTag,
      google::cloud::backupdr::v1::DeleteManagementServerRequest const& request)
      override;

  future<StatusOr<google::cloud::backupdr::v1::OperationMetadata>>
  DeleteManagementServer(
      google::longrunning::Operation const& operation) override;

  future<StatusOr<google::cloud::backupdr::v1::BackupVault>> CreateBackupVault(
      google::cloud::backupdr::v1::CreateBackupVaultRequest const& request)
      override;

  StatusOr<google::longrunning::Operation> CreateBackupVault(
      NoAwaitTag,
      google::cloud::backupdr::v1::CreateBackupVaultRequest const& request)
      override;

  future<StatusOr<google::cloud::backupdr::v1::BackupVault>> CreateBackupVault(
      google::longrunning::Operation const& operation) override;

  StreamRange<google::cloud::backupdr::v1::BackupVault> ListBackupVaults(
      google::cloud::backupdr::v1::ListBackupVaultsRequest request) override;

  StreamRange<google::cloud::backupdr::v1::BackupVault> FetchUsableBackupVaults(
      google::cloud::backupdr::v1::FetchUsableBackupVaultsRequest request)
      override;

  StatusOr<google::cloud::backupdr::v1::BackupVault> GetBackupVault(
      google::cloud::backupdr::v1::GetBackupVaultRequest const& request)
      override;

  future<StatusOr<google::cloud::backupdr::v1::BackupVault>> UpdateBackupVault(
      google::cloud::backupdr::v1::UpdateBackupVaultRequest const& request)
      override;

  StatusOr<google::longrunning::Operation> UpdateBackupVault(
      NoAwaitTag,
      google::cloud::backupdr::v1::UpdateBackupVaultRequest const& request)
      override;

  future<StatusOr<google::cloud::backupdr::v1::BackupVault>> UpdateBackupVault(
      google::longrunning::Operation const& operation) override;

  future<StatusOr<google::cloud::backupdr::v1::OperationMetadata>>
  DeleteBackupVault(google::cloud::backupdr::v1::DeleteBackupVaultRequest const&
                        request) override;

  StatusOr<google::longrunning::Operation> DeleteBackupVault(
      NoAwaitTag,
      google::cloud::backupdr::v1::DeleteBackupVaultRequest const& request)
      override;

  future<StatusOr<google::cloud::backupdr::v1::OperationMetadata>>
  DeleteBackupVault(google::longrunning::Operation const& operation) override;

  StreamRange<google::cloud::backupdr::v1::DataSource> ListDataSources(
      google::cloud::backupdr::v1::ListDataSourcesRequest request) override;

  StatusOr<google::cloud::backupdr::v1::DataSource> GetDataSource(
      google::cloud::backupdr::v1::GetDataSourceRequest const& request)
      override;

  future<StatusOr<google::cloud::backupdr::v1::DataSource>> UpdateDataSource(
      google::cloud::backupdr::v1::UpdateDataSourceRequest const& request)
      override;

  StatusOr<google::longrunning::Operation> UpdateDataSource(
      NoAwaitTag,
      google::cloud::backupdr::v1::UpdateDataSourceRequest const& request)
      override;

  future<StatusOr<google::cloud::backupdr::v1::DataSource>> UpdateDataSource(
      google::longrunning::Operation const& operation) override;

  StreamRange<google::cloud::backupdr::v1::Backup> ListBackups(
      google::cloud::backupdr::v1::ListBackupsRequest request) override;

  StatusOr<google::cloud::backupdr::v1::Backup> GetBackup(
      google::cloud::backupdr::v1::GetBackupRequest const& request) override;

  future<StatusOr<google::cloud::backupdr::v1::Backup>> UpdateBackup(
      google::cloud::backupdr::v1::UpdateBackupRequest const& request) override;

  StatusOr<google::longrunning::Operation> UpdateBackup(
      NoAwaitTag,
      google::cloud::backupdr::v1::UpdateBackupRequest const& request) override;

  future<StatusOr<google::cloud::backupdr::v1::Backup>> UpdateBackup(
      google::longrunning::Operation const& operation) override;

  future<StatusOr<google::cloud::backupdr::v1::Backup>> DeleteBackup(
      google::cloud::backupdr::v1::DeleteBackupRequest const& request) override;

  StatusOr<google::longrunning::Operation> DeleteBackup(
      NoAwaitTag,
      google::cloud::backupdr::v1::DeleteBackupRequest const& request) override;

  future<StatusOr<google::cloud::backupdr::v1::Backup>> DeleteBackup(
      google::longrunning::Operation const& operation) override;

  future<StatusOr<google::cloud::backupdr::v1::RestoreBackupResponse>>
  RestoreBackup(google::cloud::backupdr::v1::RestoreBackupRequest const&
                    request) override;

  StatusOr<google::longrunning::Operation> RestoreBackup(
      NoAwaitTag,
      google::cloud::backupdr::v1::RestoreBackupRequest const& request)
      override;

  future<StatusOr<google::cloud::backupdr::v1::RestoreBackupResponse>>
  RestoreBackup(google::longrunning::Operation const& operation) override;

  future<StatusOr<google::cloud::backupdr::v1::BackupPlan>> CreateBackupPlan(
      google::cloud::backupdr::v1::CreateBackupPlanRequest const& request)
      override;

  StatusOr<google::longrunning::Operation> CreateBackupPlan(
      NoAwaitTag,
      google::cloud::backupdr::v1::CreateBackupPlanRequest const& request)
      override;

  future<StatusOr<google::cloud::backupdr::v1::BackupPlan>> CreateBackupPlan(
      google::longrunning::Operation const& operation) override;

  future<StatusOr<google::cloud::backupdr::v1::BackupPlan>> UpdateBackupPlan(
      google::cloud::backupdr::v1::UpdateBackupPlanRequest const& request)
      override;

  StatusOr<google::longrunning::Operation> UpdateBackupPlan(
      NoAwaitTag,
      google::cloud::backupdr::v1::UpdateBackupPlanRequest const& request)
      override;

  future<StatusOr<google::cloud::backupdr::v1::BackupPlan>> UpdateBackupPlan(
      google::longrunning::Operation const& operation) override;

  StatusOr<google::cloud::backupdr::v1::BackupPlan> GetBackupPlan(
      google::cloud::backupdr::v1::GetBackupPlanRequest const& request)
      override;

  StreamRange<google::cloud::backupdr::v1::BackupPlan> ListBackupPlans(
      google::cloud::backupdr::v1::ListBackupPlansRequest request) override;

  future<StatusOr<google::cloud::backupdr::v1::OperationMetadata>>
  DeleteBackupPlan(google::cloud::backupdr::v1::DeleteBackupPlanRequest const&
                       request) override;

  StatusOr<google::longrunning::Operation> DeleteBackupPlan(
      NoAwaitTag,
      google::cloud::backupdr::v1::DeleteBackupPlanRequest const& request)
      override;

  future<StatusOr<google::cloud::backupdr::v1::OperationMetadata>>
  DeleteBackupPlan(google::longrunning::Operation const& operation) override;

  StatusOr<google::cloud::backupdr::v1::BackupPlanRevision>
  GetBackupPlanRevision(
      google::cloud::backupdr::v1::GetBackupPlanRevisionRequest const& request)
      override;

  StreamRange<google::cloud::backupdr::v1::BackupPlanRevision>
  ListBackupPlanRevisions(
      google::cloud::backupdr::v1::ListBackupPlanRevisionsRequest request)
      override;

  future<StatusOr<google::cloud::backupdr::v1::BackupPlanAssociation>>
  CreateBackupPlanAssociation(
      google::cloud::backupdr::v1::CreateBackupPlanAssociationRequest const&
          request) override;

  StatusOr<google::longrunning::Operation> CreateBackupPlanAssociation(
      NoAwaitTag,
      google::cloud::backupdr::v1::CreateBackupPlanAssociationRequest const&
          request) override;

  future<StatusOr<google::cloud::backupdr::v1::BackupPlanAssociation>>
  CreateBackupPlanAssociation(
      google::longrunning::Operation const& operation) override;

  future<StatusOr<google::cloud::backupdr::v1::BackupPlanAssociation>>
  UpdateBackupPlanAssociation(
      google::cloud::backupdr::v1::UpdateBackupPlanAssociationRequest const&
          request) override;

  StatusOr<google::longrunning::Operation> UpdateBackupPlanAssociation(
      NoAwaitTag,
      google::cloud::backupdr::v1::UpdateBackupPlanAssociationRequest const&
          request) override;

  future<StatusOr<google::cloud::backupdr::v1::BackupPlanAssociation>>
  UpdateBackupPlanAssociation(
      google::longrunning::Operation const& operation) override;

  StatusOr<google::cloud::backupdr::v1::BackupPlanAssociation>
  GetBackupPlanAssociation(
      google::cloud::backupdr::v1::GetBackupPlanAssociationRequest const&
          request) override;

  StreamRange<google::cloud::backupdr::v1::BackupPlanAssociation>
  ListBackupPlanAssociations(
      google::cloud::backupdr::v1::ListBackupPlanAssociationsRequest request)
      override;

  StreamRange<google::cloud::backupdr::v1::BackupPlanAssociation>
  FetchBackupPlanAssociationsForResourceType(
      google::cloud::backupdr::v1::
          FetchBackupPlanAssociationsForResourceTypeRequest request) override;

  future<StatusOr<google::cloud::backupdr::v1::OperationMetadata>>
  DeleteBackupPlanAssociation(
      google::cloud::backupdr::v1::DeleteBackupPlanAssociationRequest const&
          request) override;

  StatusOr<google::longrunning::Operation> DeleteBackupPlanAssociation(
      NoAwaitTag,
      google::cloud::backupdr::v1::DeleteBackupPlanAssociationRequest const&
          request) override;

  future<StatusOr<google::cloud::backupdr::v1::OperationMetadata>>
  DeleteBackupPlanAssociation(
      google::longrunning::Operation const& operation) override;

  future<StatusOr<google::cloud::backupdr::v1::BackupPlanAssociation>>
  TriggerBackup(google::cloud::backupdr::v1::TriggerBackupRequest const&
                    request) override;

  StatusOr<google::longrunning::Operation> TriggerBackup(
      NoAwaitTag,
      google::cloud::backupdr::v1::TriggerBackupRequest const& request)
      override;

  future<StatusOr<google::cloud::backupdr::v1::BackupPlanAssociation>>
  TriggerBackup(google::longrunning::Operation const& operation) override;

  StatusOr<google::cloud::backupdr::v1::DataSourceReference>
  GetDataSourceReference(
      google::cloud::backupdr::v1::GetDataSourceReferenceRequest const& request)
      override;

  StreamRange<google::cloud::backupdr::v1::DataSourceReference>
  FetchDataSourceReferencesForResourceType(
      google::cloud::backupdr::v1::
          FetchDataSourceReferencesForResourceTypeRequest request) override;

  future<StatusOr<google::cloud::backupdr::v1::InitializeServiceResponse>>
  InitializeService(google::cloud::backupdr::v1::InitializeServiceRequest const&
                        request) override;

  StatusOr<google::longrunning::Operation> InitializeService(
      NoAwaitTag,
      google::cloud::backupdr::v1::InitializeServiceRequest const& request)
      override;

  future<StatusOr<google::cloud::backupdr::v1::InitializeServiceResponse>>
  InitializeService(google::longrunning::Operation const& operation) override;

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
  std::shared_ptr<backupdr_v1::BackupDRConnection> child_;
};

#endif  // GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY

/**
 * Conditionally applies the tracing decorator to the given connection.
 *
 * The connection is only decorated if tracing is enabled (as determined by the
 * connection's options).
 */
std::shared_ptr<backupdr_v1::BackupDRConnection> MakeBackupDRTracingConnection(
    std::shared_ptr<backupdr_v1::BackupDRConnection> conn);

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace backupdr_v1_internal
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BACKUPDR_V1_INTERNAL_BACKUP_DR_TRACING_CONNECTION_H
