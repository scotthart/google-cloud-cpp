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

#include "google/cloud/backupdr/v1/backup_dr_connection.h"
#include "google/cloud/backupdr/v1/backup_dr_options.h"
#include "google/cloud/backupdr/v1/internal/backup_dr_connection_impl.h"
#include "google/cloud/backupdr/v1/internal/backup_dr_option_defaults.h"
#include "google/cloud/backupdr/v1/internal/backup_dr_stub_factory.h"
#include "google/cloud/backupdr/v1/internal/backup_dr_tracing_connection.h"
#include "google/cloud/background_threads.h"
#include "google/cloud/common_options.h"
#include "google/cloud/credentials.h"
#include "google/cloud/grpc_options.h"
#include "google/cloud/internal/pagination_range.h"
#include "google/cloud/internal/unified_grpc_credentials.h"
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace backupdr_v1 {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

BackupDRConnection::~BackupDRConnection() = default;

StreamRange<google::cloud::backupdr::v1::ManagementServer>
BackupDRConnection::ListManagementServers(
    google::cloud::backupdr::v1::
        ListManagementServersRequest) {  // NOLINT(performance-unnecessary-value-param)
  return google::cloud::internal::MakeUnimplementedPaginationRange<
      StreamRange<google::cloud::backupdr::v1::ManagementServer>>();
}

StatusOr<google::cloud::backupdr::v1::ManagementServer>
BackupDRConnection::GetManagementServer(
    google::cloud::backupdr::v1::GetManagementServerRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

future<StatusOr<google::cloud::backupdr::v1::ManagementServer>>
BackupDRConnection::CreateManagementServer(
    google::cloud::backupdr::v1::CreateManagementServerRequest const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::ManagementServer>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

StatusOr<google::longrunning::Operation>
BackupDRConnection::CreateManagementServer(
    NoAwaitTag,
    google::cloud::backupdr::v1::CreateManagementServerRequest const&) {
  return StatusOr<google::longrunning::Operation>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

future<StatusOr<google::cloud::backupdr::v1::ManagementServer>>
BackupDRConnection::CreateManagementServer(
    google::longrunning::Operation const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::ManagementServer>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

future<StatusOr<google::cloud::backupdr::v1::OperationMetadata>>
BackupDRConnection::DeleteManagementServer(
    google::cloud::backupdr::v1::DeleteManagementServerRequest const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::OperationMetadata>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

StatusOr<google::longrunning::Operation>
BackupDRConnection::DeleteManagementServer(
    NoAwaitTag,
    google::cloud::backupdr::v1::DeleteManagementServerRequest const&) {
  return StatusOr<google::longrunning::Operation>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

future<StatusOr<google::cloud::backupdr::v1::OperationMetadata>>
BackupDRConnection::DeleteManagementServer(
    google::longrunning::Operation const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::OperationMetadata>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

future<StatusOr<google::cloud::backupdr::v1::BackupVault>>
BackupDRConnection::CreateBackupVault(
    google::cloud::backupdr::v1::CreateBackupVaultRequest const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::BackupVault>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

StatusOr<google::longrunning::Operation> BackupDRConnection::CreateBackupVault(
    NoAwaitTag, google::cloud::backupdr::v1::CreateBackupVaultRequest const&) {
  return StatusOr<google::longrunning::Operation>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

future<StatusOr<google::cloud::backupdr::v1::BackupVault>>
BackupDRConnection::CreateBackupVault(google::longrunning::Operation const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::BackupVault>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

StreamRange<google::cloud::backupdr::v1::BackupVault>
BackupDRConnection::ListBackupVaults(
    google::cloud::backupdr::v1::
        ListBackupVaultsRequest) {  // NOLINT(performance-unnecessary-value-param)
  return google::cloud::internal::MakeUnimplementedPaginationRange<
      StreamRange<google::cloud::backupdr::v1::BackupVault>>();
}

StreamRange<google::cloud::backupdr::v1::BackupVault>
BackupDRConnection::FetchUsableBackupVaults(
    google::cloud::backupdr::v1::
        FetchUsableBackupVaultsRequest) {  // NOLINT(performance-unnecessary-value-param)
  return google::cloud::internal::MakeUnimplementedPaginationRange<
      StreamRange<google::cloud::backupdr::v1::BackupVault>>();
}

StatusOr<google::cloud::backupdr::v1::BackupVault>
BackupDRConnection::GetBackupVault(
    google::cloud::backupdr::v1::GetBackupVaultRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

future<StatusOr<google::cloud::backupdr::v1::BackupVault>>
BackupDRConnection::UpdateBackupVault(
    google::cloud::backupdr::v1::UpdateBackupVaultRequest const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::BackupVault>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

StatusOr<google::longrunning::Operation> BackupDRConnection::UpdateBackupVault(
    NoAwaitTag, google::cloud::backupdr::v1::UpdateBackupVaultRequest const&) {
  return StatusOr<google::longrunning::Operation>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

future<StatusOr<google::cloud::backupdr::v1::BackupVault>>
BackupDRConnection::UpdateBackupVault(google::longrunning::Operation const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::BackupVault>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

future<StatusOr<google::cloud::backupdr::v1::OperationMetadata>>
BackupDRConnection::DeleteBackupVault(
    google::cloud::backupdr::v1::DeleteBackupVaultRequest const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::OperationMetadata>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

StatusOr<google::longrunning::Operation> BackupDRConnection::DeleteBackupVault(
    NoAwaitTag, google::cloud::backupdr::v1::DeleteBackupVaultRequest const&) {
  return StatusOr<google::longrunning::Operation>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

future<StatusOr<google::cloud::backupdr::v1::OperationMetadata>>
BackupDRConnection::DeleteBackupVault(google::longrunning::Operation const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::OperationMetadata>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

StreamRange<google::cloud::backupdr::v1::DataSource>
BackupDRConnection::ListDataSources(
    google::cloud::backupdr::v1::
        ListDataSourcesRequest) {  // NOLINT(performance-unnecessary-value-param)
  return google::cloud::internal::MakeUnimplementedPaginationRange<
      StreamRange<google::cloud::backupdr::v1::DataSource>>();
}

StatusOr<google::cloud::backupdr::v1::DataSource>
BackupDRConnection::GetDataSource(
    google::cloud::backupdr::v1::GetDataSourceRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

future<StatusOr<google::cloud::backupdr::v1::DataSource>>
BackupDRConnection::UpdateDataSource(
    google::cloud::backupdr::v1::UpdateDataSourceRequest const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::DataSource>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

StatusOr<google::longrunning::Operation> BackupDRConnection::UpdateDataSource(
    NoAwaitTag, google::cloud::backupdr::v1::UpdateDataSourceRequest const&) {
  return StatusOr<google::longrunning::Operation>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

future<StatusOr<google::cloud::backupdr::v1::DataSource>>
BackupDRConnection::UpdateDataSource(google::longrunning::Operation const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::DataSource>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

StreamRange<google::cloud::backupdr::v1::Backup>
BackupDRConnection::ListBackups(
    google::cloud::backupdr::v1::
        ListBackupsRequest) {  // NOLINT(performance-unnecessary-value-param)
  return google::cloud::internal::MakeUnimplementedPaginationRange<
      StreamRange<google::cloud::backupdr::v1::Backup>>();
}

StatusOr<google::cloud::backupdr::v1::Backup> BackupDRConnection::GetBackup(
    google::cloud::backupdr::v1::GetBackupRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

future<StatusOr<google::cloud::backupdr::v1::Backup>>
BackupDRConnection::UpdateBackup(
    google::cloud::backupdr::v1::UpdateBackupRequest const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::Backup>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

StatusOr<google::longrunning::Operation> BackupDRConnection::UpdateBackup(
    NoAwaitTag, google::cloud::backupdr::v1::UpdateBackupRequest const&) {
  return StatusOr<google::longrunning::Operation>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

future<StatusOr<google::cloud::backupdr::v1::Backup>>
BackupDRConnection::UpdateBackup(google::longrunning::Operation const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::Backup>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

future<StatusOr<google::cloud::backupdr::v1::Backup>>
BackupDRConnection::DeleteBackup(
    google::cloud::backupdr::v1::DeleteBackupRequest const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::Backup>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

StatusOr<google::longrunning::Operation> BackupDRConnection::DeleteBackup(
    NoAwaitTag, google::cloud::backupdr::v1::DeleteBackupRequest const&) {
  return StatusOr<google::longrunning::Operation>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

future<StatusOr<google::cloud::backupdr::v1::Backup>>
BackupDRConnection::DeleteBackup(google::longrunning::Operation const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::Backup>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

future<StatusOr<google::cloud::backupdr::v1::RestoreBackupResponse>>
BackupDRConnection::RestoreBackup(
    google::cloud::backupdr::v1::RestoreBackupRequest const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::RestoreBackupResponse>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

StatusOr<google::longrunning::Operation> BackupDRConnection::RestoreBackup(
    NoAwaitTag, google::cloud::backupdr::v1::RestoreBackupRequest const&) {
  return StatusOr<google::longrunning::Operation>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

future<StatusOr<google::cloud::backupdr::v1::RestoreBackupResponse>>
BackupDRConnection::RestoreBackup(google::longrunning::Operation const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::RestoreBackupResponse>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

future<StatusOr<google::cloud::backupdr::v1::BackupPlan>>
BackupDRConnection::CreateBackupPlan(
    google::cloud::backupdr::v1::CreateBackupPlanRequest const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::BackupPlan>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

StatusOr<google::longrunning::Operation> BackupDRConnection::CreateBackupPlan(
    NoAwaitTag, google::cloud::backupdr::v1::CreateBackupPlanRequest const&) {
  return StatusOr<google::longrunning::Operation>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

future<StatusOr<google::cloud::backupdr::v1::BackupPlan>>
BackupDRConnection::CreateBackupPlan(google::longrunning::Operation const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::BackupPlan>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

future<StatusOr<google::cloud::backupdr::v1::BackupPlan>>
BackupDRConnection::UpdateBackupPlan(
    google::cloud::backupdr::v1::UpdateBackupPlanRequest const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::BackupPlan>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

StatusOr<google::longrunning::Operation> BackupDRConnection::UpdateBackupPlan(
    NoAwaitTag, google::cloud::backupdr::v1::UpdateBackupPlanRequest const&) {
  return StatusOr<google::longrunning::Operation>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

future<StatusOr<google::cloud::backupdr::v1::BackupPlan>>
BackupDRConnection::UpdateBackupPlan(google::longrunning::Operation const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::BackupPlan>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

StatusOr<google::cloud::backupdr::v1::BackupPlan>
BackupDRConnection::GetBackupPlan(
    google::cloud::backupdr::v1::GetBackupPlanRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StreamRange<google::cloud::backupdr::v1::BackupPlan>
BackupDRConnection::ListBackupPlans(
    google::cloud::backupdr::v1::
        ListBackupPlansRequest) {  // NOLINT(performance-unnecessary-value-param)
  return google::cloud::internal::MakeUnimplementedPaginationRange<
      StreamRange<google::cloud::backupdr::v1::BackupPlan>>();
}

future<StatusOr<google::cloud::backupdr::v1::OperationMetadata>>
BackupDRConnection::DeleteBackupPlan(
    google::cloud::backupdr::v1::DeleteBackupPlanRequest const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::OperationMetadata>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

StatusOr<google::longrunning::Operation> BackupDRConnection::DeleteBackupPlan(
    NoAwaitTag, google::cloud::backupdr::v1::DeleteBackupPlanRequest const&) {
  return StatusOr<google::longrunning::Operation>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

future<StatusOr<google::cloud::backupdr::v1::OperationMetadata>>
BackupDRConnection::DeleteBackupPlan(google::longrunning::Operation const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::OperationMetadata>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

StatusOr<google::cloud::backupdr::v1::BackupPlanRevision>
BackupDRConnection::GetBackupPlanRevision(
    google::cloud::backupdr::v1::GetBackupPlanRevisionRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StreamRange<google::cloud::backupdr::v1::BackupPlanRevision>
BackupDRConnection::ListBackupPlanRevisions(
    google::cloud::backupdr::v1::
        ListBackupPlanRevisionsRequest) {  // NOLINT(performance-unnecessary-value-param)
  return google::cloud::internal::MakeUnimplementedPaginationRange<
      StreamRange<google::cloud::backupdr::v1::BackupPlanRevision>>();
}

future<StatusOr<google::cloud::backupdr::v1::BackupPlanAssociation>>
BackupDRConnection::CreateBackupPlanAssociation(
    google::cloud::backupdr::v1::CreateBackupPlanAssociationRequest const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::BackupPlanAssociation>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

StatusOr<google::longrunning::Operation>
BackupDRConnection::CreateBackupPlanAssociation(
    NoAwaitTag,
    google::cloud::backupdr::v1::CreateBackupPlanAssociationRequest const&) {
  return StatusOr<google::longrunning::Operation>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

future<StatusOr<google::cloud::backupdr::v1::BackupPlanAssociation>>
BackupDRConnection::CreateBackupPlanAssociation(
    google::longrunning::Operation const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::BackupPlanAssociation>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

future<StatusOr<google::cloud::backupdr::v1::BackupPlanAssociation>>
BackupDRConnection::UpdateBackupPlanAssociation(
    google::cloud::backupdr::v1::UpdateBackupPlanAssociationRequest const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::BackupPlanAssociation>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

StatusOr<google::longrunning::Operation>
BackupDRConnection::UpdateBackupPlanAssociation(
    NoAwaitTag,
    google::cloud::backupdr::v1::UpdateBackupPlanAssociationRequest const&) {
  return StatusOr<google::longrunning::Operation>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

future<StatusOr<google::cloud::backupdr::v1::BackupPlanAssociation>>
BackupDRConnection::UpdateBackupPlanAssociation(
    google::longrunning::Operation const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::BackupPlanAssociation>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

StatusOr<google::cloud::backupdr::v1::BackupPlanAssociation>
BackupDRConnection::GetBackupPlanAssociation(
    google::cloud::backupdr::v1::GetBackupPlanAssociationRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StreamRange<google::cloud::backupdr::v1::BackupPlanAssociation>
BackupDRConnection::ListBackupPlanAssociations(
    google::cloud::backupdr::v1::
        ListBackupPlanAssociationsRequest) {  // NOLINT(performance-unnecessary-value-param)
  return google::cloud::internal::MakeUnimplementedPaginationRange<
      StreamRange<google::cloud::backupdr::v1::BackupPlanAssociation>>();
}

StreamRange<google::cloud::backupdr::v1::BackupPlanAssociation>
BackupDRConnection::FetchBackupPlanAssociationsForResourceType(
    google::cloud::backupdr::v1::
        FetchBackupPlanAssociationsForResourceTypeRequest) {  // NOLINT(performance-unnecessary-value-param)
  return google::cloud::internal::MakeUnimplementedPaginationRange<
      StreamRange<google::cloud::backupdr::v1::BackupPlanAssociation>>();
}

future<StatusOr<google::cloud::backupdr::v1::OperationMetadata>>
BackupDRConnection::DeleteBackupPlanAssociation(
    google::cloud::backupdr::v1::DeleteBackupPlanAssociationRequest const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::OperationMetadata>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

StatusOr<google::longrunning::Operation>
BackupDRConnection::DeleteBackupPlanAssociation(
    NoAwaitTag,
    google::cloud::backupdr::v1::DeleteBackupPlanAssociationRequest const&) {
  return StatusOr<google::longrunning::Operation>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

future<StatusOr<google::cloud::backupdr::v1::OperationMetadata>>
BackupDRConnection::DeleteBackupPlanAssociation(
    google::longrunning::Operation const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::OperationMetadata>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

future<StatusOr<google::cloud::backupdr::v1::BackupPlanAssociation>>
BackupDRConnection::TriggerBackup(
    google::cloud::backupdr::v1::TriggerBackupRequest const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::BackupPlanAssociation>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

StatusOr<google::longrunning::Operation> BackupDRConnection::TriggerBackup(
    NoAwaitTag, google::cloud::backupdr::v1::TriggerBackupRequest const&) {
  return StatusOr<google::longrunning::Operation>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

future<StatusOr<google::cloud::backupdr::v1::BackupPlanAssociation>>
BackupDRConnection::TriggerBackup(google::longrunning::Operation const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::BackupPlanAssociation>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

StatusOr<google::cloud::backupdr::v1::DataSourceReference>
BackupDRConnection::GetDataSourceReference(
    google::cloud::backupdr::v1::GetDataSourceReferenceRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StreamRange<google::cloud::backupdr::v1::DataSourceReference>
BackupDRConnection::FetchDataSourceReferencesForResourceType(
    google::cloud::backupdr::v1::
        FetchDataSourceReferencesForResourceTypeRequest) {  // NOLINT(performance-unnecessary-value-param)
  return google::cloud::internal::MakeUnimplementedPaginationRange<
      StreamRange<google::cloud::backupdr::v1::DataSourceReference>>();
}

future<StatusOr<google::cloud::backupdr::v1::InitializeServiceResponse>>
BackupDRConnection::InitializeService(
    google::cloud::backupdr::v1::InitializeServiceRequest const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::InitializeServiceResponse>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

StatusOr<google::longrunning::Operation> BackupDRConnection::InitializeService(
    NoAwaitTag, google::cloud::backupdr::v1::InitializeServiceRequest const&) {
  return StatusOr<google::longrunning::Operation>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

future<StatusOr<google::cloud::backupdr::v1::InitializeServiceResponse>>
BackupDRConnection::InitializeService(google::longrunning::Operation const&) {
  return google::cloud::make_ready_future<
      StatusOr<google::cloud::backupdr::v1::InitializeServiceResponse>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

StreamRange<google::cloud::location::Location>
BackupDRConnection::ListLocations(
    google::cloud::location::
        ListLocationsRequest) {  // NOLINT(performance-unnecessary-value-param)
  return google::cloud::internal::MakeUnimplementedPaginationRange<
      StreamRange<google::cloud::location::Location>>();
}

StatusOr<google::cloud::location::Location> BackupDRConnection::GetLocation(
    google::cloud::location::GetLocationRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StatusOr<google::iam::v1::Policy> BackupDRConnection::SetIamPolicy(
    google::iam::v1::SetIamPolicyRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StatusOr<google::iam::v1::Policy> BackupDRConnection::GetIamPolicy(
    google::iam::v1::GetIamPolicyRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StatusOr<google::iam::v1::TestIamPermissionsResponse>
BackupDRConnection::TestIamPermissions(
    google::iam::v1::TestIamPermissionsRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StreamRange<google::longrunning::Operation> BackupDRConnection::ListOperations(
    google::longrunning::
        ListOperationsRequest) {  // NOLINT(performance-unnecessary-value-param)
  return google::cloud::internal::MakeUnimplementedPaginationRange<
      StreamRange<google::longrunning::Operation>>();
}

StatusOr<google::longrunning::Operation> BackupDRConnection::GetOperation(
    google::longrunning::GetOperationRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

Status BackupDRConnection::DeleteOperation(
    google::longrunning::DeleteOperationRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

Status BackupDRConnection::CancelOperation(
    google::longrunning::CancelOperationRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

std::shared_ptr<BackupDRConnection> MakeBackupDRConnection(Options options) {
  internal::CheckExpectedOptions<CommonOptionList, GrpcOptionList,
                                 UnifiedCredentialsOptionList,
                                 BackupDRPolicyOptionList>(options, __func__);
  options = backupdr_v1_internal::BackupDRDefaultOptions(std::move(options));
  auto background = internal::MakeBackgroundThreadsFactory(options)();
  auto auth = internal::CreateAuthenticationStrategy(background->cq(), options);
  auto stub =
      backupdr_v1_internal::CreateDefaultBackupDRStub(std::move(auth), options);
  return backupdr_v1_internal::MakeBackupDRTracingConnection(
      std::make_shared<backupdr_v1_internal::BackupDRConnectionImpl>(
          std::move(background), std::move(stub), std::move(options)));
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace backupdr_v1
}  // namespace cloud
}  // namespace google
