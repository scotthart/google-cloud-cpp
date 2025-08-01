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

#include "google/cloud/backupdr/v1/internal/backup_dr_tracing_connection.h"
#include "google/cloud/internal/opentelemetry.h"
#include "google/cloud/internal/traced_stream_range.h"
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace backupdr_v1_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

#ifdef GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY

BackupDRTracingConnection::BackupDRTracingConnection(
    std::shared_ptr<backupdr_v1::BackupDRConnection> child)
    : child_(std::move(child)) {}

StreamRange<google::cloud::backupdr::v1::ManagementServer>
BackupDRTracingConnection::ListManagementServers(
    google::cloud::backupdr::v1::ListManagementServersRequest request) {
  auto span = internal::MakeSpan(
      "backupdr_v1::BackupDRConnection::ListManagementServers");
  internal::OTelScope scope(span);
  auto sr = child_->ListManagementServers(std::move(request));
  return internal::MakeTracedStreamRange<
      google::cloud::backupdr::v1::ManagementServer>(std::move(span),
                                                     std::move(sr));
}

StatusOr<google::cloud::backupdr::v1::ManagementServer>
BackupDRTracingConnection::GetManagementServer(
    google::cloud::backupdr::v1::GetManagementServerRequest const& request) {
  auto span = internal::MakeSpan(
      "backupdr_v1::BackupDRConnection::GetManagementServer");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->GetManagementServer(request));
}

future<StatusOr<google::cloud::backupdr::v1::ManagementServer>>
BackupDRTracingConnection::CreateManagementServer(
    google::cloud::backupdr::v1::CreateManagementServerRequest const& request) {
  auto span = internal::MakeSpan(
      "backupdr_v1::BackupDRConnection::CreateManagementServer");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->CreateManagementServer(request));
}

StatusOr<google::longrunning::Operation>
BackupDRTracingConnection::CreateManagementServer(
    NoAwaitTag,
    google::cloud::backupdr::v1::CreateManagementServerRequest const& request) {
  auto span = internal::MakeSpan(
      "backupdr_v1::BackupDRConnection::CreateManagementServer");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(
      *span, child_->CreateManagementServer(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::backupdr::v1::ManagementServer>>
BackupDRTracingConnection::CreateManagementServer(
    google::longrunning::Operation const& operation) {
  auto span = internal::MakeSpan(
      "backupdr_v1::BackupDRConnection::CreateManagementServer");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->CreateManagementServer(operation));
}

future<StatusOr<google::cloud::backupdr::v1::OperationMetadata>>
BackupDRTracingConnection::DeleteManagementServer(
    google::cloud::backupdr::v1::DeleteManagementServerRequest const& request) {
  auto span = internal::MakeSpan(
      "backupdr_v1::BackupDRConnection::DeleteManagementServer");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->DeleteManagementServer(request));
}

StatusOr<google::longrunning::Operation>
BackupDRTracingConnection::DeleteManagementServer(
    NoAwaitTag,
    google::cloud::backupdr::v1::DeleteManagementServerRequest const& request) {
  auto span = internal::MakeSpan(
      "backupdr_v1::BackupDRConnection::DeleteManagementServer");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(
      *span, child_->DeleteManagementServer(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::backupdr::v1::OperationMetadata>>
BackupDRTracingConnection::DeleteManagementServer(
    google::longrunning::Operation const& operation) {
  auto span = internal::MakeSpan(
      "backupdr_v1::BackupDRConnection::DeleteManagementServer");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->DeleteManagementServer(operation));
}

future<StatusOr<google::cloud::backupdr::v1::BackupVault>>
BackupDRTracingConnection::CreateBackupVault(
    google::cloud::backupdr::v1::CreateBackupVaultRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::CreateBackupVault");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->CreateBackupVault(request));
}

StatusOr<google::longrunning::Operation>
BackupDRTracingConnection::CreateBackupVault(
    NoAwaitTag,
    google::cloud::backupdr::v1::CreateBackupVaultRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::CreateBackupVault");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span,
                           child_->CreateBackupVault(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::backupdr::v1::BackupVault>>
BackupDRTracingConnection::CreateBackupVault(
    google::longrunning::Operation const& operation) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::CreateBackupVault");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->CreateBackupVault(operation));
}

StreamRange<google::cloud::backupdr::v1::BackupVault>
BackupDRTracingConnection::ListBackupVaults(
    google::cloud::backupdr::v1::ListBackupVaultsRequest request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::ListBackupVaults");
  internal::OTelScope scope(span);
  auto sr = child_->ListBackupVaults(std::move(request));
  return internal::MakeTracedStreamRange<
      google::cloud::backupdr::v1::BackupVault>(std::move(span), std::move(sr));
}

StreamRange<google::cloud::backupdr::v1::BackupVault>
BackupDRTracingConnection::FetchUsableBackupVaults(
    google::cloud::backupdr::v1::FetchUsableBackupVaultsRequest request) {
  auto span = internal::MakeSpan(
      "backupdr_v1::BackupDRConnection::FetchUsableBackupVaults");
  internal::OTelScope scope(span);
  auto sr = child_->FetchUsableBackupVaults(std::move(request));
  return internal::MakeTracedStreamRange<
      google::cloud::backupdr::v1::BackupVault>(std::move(span), std::move(sr));
}

StatusOr<google::cloud::backupdr::v1::BackupVault>
BackupDRTracingConnection::GetBackupVault(
    google::cloud::backupdr::v1::GetBackupVaultRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::GetBackupVault");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->GetBackupVault(request));
}

future<StatusOr<google::cloud::backupdr::v1::BackupVault>>
BackupDRTracingConnection::UpdateBackupVault(
    google::cloud::backupdr::v1::UpdateBackupVaultRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::UpdateBackupVault");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->UpdateBackupVault(request));
}

StatusOr<google::longrunning::Operation>
BackupDRTracingConnection::UpdateBackupVault(
    NoAwaitTag,
    google::cloud::backupdr::v1::UpdateBackupVaultRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::UpdateBackupVault");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span,
                           child_->UpdateBackupVault(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::backupdr::v1::BackupVault>>
BackupDRTracingConnection::UpdateBackupVault(
    google::longrunning::Operation const& operation) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::UpdateBackupVault");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->UpdateBackupVault(operation));
}

future<StatusOr<google::cloud::backupdr::v1::OperationMetadata>>
BackupDRTracingConnection::DeleteBackupVault(
    google::cloud::backupdr::v1::DeleteBackupVaultRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::DeleteBackupVault");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->DeleteBackupVault(request));
}

StatusOr<google::longrunning::Operation>
BackupDRTracingConnection::DeleteBackupVault(
    NoAwaitTag,
    google::cloud::backupdr::v1::DeleteBackupVaultRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::DeleteBackupVault");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span,
                           child_->DeleteBackupVault(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::backupdr::v1::OperationMetadata>>
BackupDRTracingConnection::DeleteBackupVault(
    google::longrunning::Operation const& operation) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::DeleteBackupVault");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->DeleteBackupVault(operation));
}

StreamRange<google::cloud::backupdr::v1::DataSource>
BackupDRTracingConnection::ListDataSources(
    google::cloud::backupdr::v1::ListDataSourcesRequest request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::ListDataSources");
  internal::OTelScope scope(span);
  auto sr = child_->ListDataSources(std::move(request));
  return internal::MakeTracedStreamRange<
      google::cloud::backupdr::v1::DataSource>(std::move(span), std::move(sr));
}

StatusOr<google::cloud::backupdr::v1::DataSource>
BackupDRTracingConnection::GetDataSource(
    google::cloud::backupdr::v1::GetDataSourceRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::GetDataSource");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->GetDataSource(request));
}

future<StatusOr<google::cloud::backupdr::v1::DataSource>>
BackupDRTracingConnection::UpdateDataSource(
    google::cloud::backupdr::v1::UpdateDataSourceRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::UpdateDataSource");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->UpdateDataSource(request));
}

StatusOr<google::longrunning::Operation>
BackupDRTracingConnection::UpdateDataSource(
    NoAwaitTag,
    google::cloud::backupdr::v1::UpdateDataSourceRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::UpdateDataSource");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span,
                           child_->UpdateDataSource(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::backupdr::v1::DataSource>>
BackupDRTracingConnection::UpdateDataSource(
    google::longrunning::Operation const& operation) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::UpdateDataSource");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->UpdateDataSource(operation));
}

StreamRange<google::cloud::backupdr::v1::Backup>
BackupDRTracingConnection::ListBackups(
    google::cloud::backupdr::v1::ListBackupsRequest request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::ListBackups");
  internal::OTelScope scope(span);
  auto sr = child_->ListBackups(std::move(request));
  return internal::MakeTracedStreamRange<google::cloud::backupdr::v1::Backup>(
      std::move(span), std::move(sr));
}

StatusOr<google::cloud::backupdr::v1::Backup>
BackupDRTracingConnection::GetBackup(
    google::cloud::backupdr::v1::GetBackupRequest const& request) {
  auto span = internal::MakeSpan("backupdr_v1::BackupDRConnection::GetBackup");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->GetBackup(request));
}

future<StatusOr<google::cloud::backupdr::v1::Backup>>
BackupDRTracingConnection::UpdateBackup(
    google::cloud::backupdr::v1::UpdateBackupRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::UpdateBackup");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->UpdateBackup(request));
}

StatusOr<google::longrunning::Operation>
BackupDRTracingConnection::UpdateBackup(
    NoAwaitTag,
    google::cloud::backupdr::v1::UpdateBackupRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::UpdateBackup");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span, child_->UpdateBackup(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::backupdr::v1::Backup>>
BackupDRTracingConnection::UpdateBackup(
    google::longrunning::Operation const& operation) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::UpdateBackup");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->UpdateBackup(operation));
}

future<StatusOr<google::cloud::backupdr::v1::Backup>>
BackupDRTracingConnection::DeleteBackup(
    google::cloud::backupdr::v1::DeleteBackupRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::DeleteBackup");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->DeleteBackup(request));
}

StatusOr<google::longrunning::Operation>
BackupDRTracingConnection::DeleteBackup(
    NoAwaitTag,
    google::cloud::backupdr::v1::DeleteBackupRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::DeleteBackup");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span, child_->DeleteBackup(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::backupdr::v1::Backup>>
BackupDRTracingConnection::DeleteBackup(
    google::longrunning::Operation const& operation) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::DeleteBackup");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->DeleteBackup(operation));
}

future<StatusOr<google::cloud::backupdr::v1::RestoreBackupResponse>>
BackupDRTracingConnection::RestoreBackup(
    google::cloud::backupdr::v1::RestoreBackupRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::RestoreBackup");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->RestoreBackup(request));
}

StatusOr<google::longrunning::Operation>
BackupDRTracingConnection::RestoreBackup(
    NoAwaitTag,
    google::cloud::backupdr::v1::RestoreBackupRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::RestoreBackup");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span, child_->RestoreBackup(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::backupdr::v1::RestoreBackupResponse>>
BackupDRTracingConnection::RestoreBackup(
    google::longrunning::Operation const& operation) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::RestoreBackup");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->RestoreBackup(operation));
}

future<StatusOr<google::cloud::backupdr::v1::BackupPlan>>
BackupDRTracingConnection::CreateBackupPlan(
    google::cloud::backupdr::v1::CreateBackupPlanRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::CreateBackupPlan");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->CreateBackupPlan(request));
}

StatusOr<google::longrunning::Operation>
BackupDRTracingConnection::CreateBackupPlan(
    NoAwaitTag,
    google::cloud::backupdr::v1::CreateBackupPlanRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::CreateBackupPlan");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span,
                           child_->CreateBackupPlan(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::backupdr::v1::BackupPlan>>
BackupDRTracingConnection::CreateBackupPlan(
    google::longrunning::Operation const& operation) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::CreateBackupPlan");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->CreateBackupPlan(operation));
}

future<StatusOr<google::cloud::backupdr::v1::BackupPlan>>
BackupDRTracingConnection::UpdateBackupPlan(
    google::cloud::backupdr::v1::UpdateBackupPlanRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::UpdateBackupPlan");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->UpdateBackupPlan(request));
}

StatusOr<google::longrunning::Operation>
BackupDRTracingConnection::UpdateBackupPlan(
    NoAwaitTag,
    google::cloud::backupdr::v1::UpdateBackupPlanRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::UpdateBackupPlan");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span,
                           child_->UpdateBackupPlan(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::backupdr::v1::BackupPlan>>
BackupDRTracingConnection::UpdateBackupPlan(
    google::longrunning::Operation const& operation) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::UpdateBackupPlan");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->UpdateBackupPlan(operation));
}

StatusOr<google::cloud::backupdr::v1::BackupPlan>
BackupDRTracingConnection::GetBackupPlan(
    google::cloud::backupdr::v1::GetBackupPlanRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::GetBackupPlan");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->GetBackupPlan(request));
}

StreamRange<google::cloud::backupdr::v1::BackupPlan>
BackupDRTracingConnection::ListBackupPlans(
    google::cloud::backupdr::v1::ListBackupPlansRequest request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::ListBackupPlans");
  internal::OTelScope scope(span);
  auto sr = child_->ListBackupPlans(std::move(request));
  return internal::MakeTracedStreamRange<
      google::cloud::backupdr::v1::BackupPlan>(std::move(span), std::move(sr));
}

future<StatusOr<google::cloud::backupdr::v1::OperationMetadata>>
BackupDRTracingConnection::DeleteBackupPlan(
    google::cloud::backupdr::v1::DeleteBackupPlanRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::DeleteBackupPlan");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->DeleteBackupPlan(request));
}

StatusOr<google::longrunning::Operation>
BackupDRTracingConnection::DeleteBackupPlan(
    NoAwaitTag,
    google::cloud::backupdr::v1::DeleteBackupPlanRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::DeleteBackupPlan");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span,
                           child_->DeleteBackupPlan(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::backupdr::v1::OperationMetadata>>
BackupDRTracingConnection::DeleteBackupPlan(
    google::longrunning::Operation const& operation) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::DeleteBackupPlan");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->DeleteBackupPlan(operation));
}

StatusOr<google::cloud::backupdr::v1::BackupPlanRevision>
BackupDRTracingConnection::GetBackupPlanRevision(
    google::cloud::backupdr::v1::GetBackupPlanRevisionRequest const& request) {
  auto span = internal::MakeSpan(
      "backupdr_v1::BackupDRConnection::GetBackupPlanRevision");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->GetBackupPlanRevision(request));
}

StreamRange<google::cloud::backupdr::v1::BackupPlanRevision>
BackupDRTracingConnection::ListBackupPlanRevisions(
    google::cloud::backupdr::v1::ListBackupPlanRevisionsRequest request) {
  auto span = internal::MakeSpan(
      "backupdr_v1::BackupDRConnection::ListBackupPlanRevisions");
  internal::OTelScope scope(span);
  auto sr = child_->ListBackupPlanRevisions(std::move(request));
  return internal::MakeTracedStreamRange<
      google::cloud::backupdr::v1::BackupPlanRevision>(std::move(span),
                                                       std::move(sr));
}

future<StatusOr<google::cloud::backupdr::v1::BackupPlanAssociation>>
BackupDRTracingConnection::CreateBackupPlanAssociation(
    google::cloud::backupdr::v1::CreateBackupPlanAssociationRequest const&
        request) {
  auto span = internal::MakeSpan(
      "backupdr_v1::BackupDRConnection::CreateBackupPlanAssociation");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->CreateBackupPlanAssociation(request));
}

StatusOr<google::longrunning::Operation>
BackupDRTracingConnection::CreateBackupPlanAssociation(
    NoAwaitTag,
    google::cloud::backupdr::v1::CreateBackupPlanAssociationRequest const&
        request) {
  auto span = internal::MakeSpan(
      "backupdr_v1::BackupDRConnection::CreateBackupPlanAssociation");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(
      *span, child_->CreateBackupPlanAssociation(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::backupdr::v1::BackupPlanAssociation>>
BackupDRTracingConnection::CreateBackupPlanAssociation(
    google::longrunning::Operation const& operation) {
  auto span = internal::MakeSpan(
      "backupdr_v1::BackupDRConnection::CreateBackupPlanAssociation");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->CreateBackupPlanAssociation(operation));
}

future<StatusOr<google::cloud::backupdr::v1::BackupPlanAssociation>>
BackupDRTracingConnection::UpdateBackupPlanAssociation(
    google::cloud::backupdr::v1::UpdateBackupPlanAssociationRequest const&
        request) {
  auto span = internal::MakeSpan(
      "backupdr_v1::BackupDRConnection::UpdateBackupPlanAssociation");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->UpdateBackupPlanAssociation(request));
}

StatusOr<google::longrunning::Operation>
BackupDRTracingConnection::UpdateBackupPlanAssociation(
    NoAwaitTag,
    google::cloud::backupdr::v1::UpdateBackupPlanAssociationRequest const&
        request) {
  auto span = internal::MakeSpan(
      "backupdr_v1::BackupDRConnection::UpdateBackupPlanAssociation");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(
      *span, child_->UpdateBackupPlanAssociation(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::backupdr::v1::BackupPlanAssociation>>
BackupDRTracingConnection::UpdateBackupPlanAssociation(
    google::longrunning::Operation const& operation) {
  auto span = internal::MakeSpan(
      "backupdr_v1::BackupDRConnection::UpdateBackupPlanAssociation");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->UpdateBackupPlanAssociation(operation));
}

StatusOr<google::cloud::backupdr::v1::BackupPlanAssociation>
BackupDRTracingConnection::GetBackupPlanAssociation(
    google::cloud::backupdr::v1::GetBackupPlanAssociationRequest const&
        request) {
  auto span = internal::MakeSpan(
      "backupdr_v1::BackupDRConnection::GetBackupPlanAssociation");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->GetBackupPlanAssociation(request));
}

StreamRange<google::cloud::backupdr::v1::BackupPlanAssociation>
BackupDRTracingConnection::ListBackupPlanAssociations(
    google::cloud::backupdr::v1::ListBackupPlanAssociationsRequest request) {
  auto span = internal::MakeSpan(
      "backupdr_v1::BackupDRConnection::ListBackupPlanAssociations");
  internal::OTelScope scope(span);
  auto sr = child_->ListBackupPlanAssociations(std::move(request));
  return internal::MakeTracedStreamRange<
      google::cloud::backupdr::v1::BackupPlanAssociation>(std::move(span),
                                                          std::move(sr));
}

StreamRange<google::cloud::backupdr::v1::BackupPlanAssociation>
BackupDRTracingConnection::FetchBackupPlanAssociationsForResourceType(
    google::cloud::backupdr::v1::
        FetchBackupPlanAssociationsForResourceTypeRequest request) {
  auto span = internal::MakeSpan(
      "backupdr_v1::BackupDRConnection::"
      "FetchBackupPlanAssociationsForResourceType");
  internal::OTelScope scope(span);
  auto sr =
      child_->FetchBackupPlanAssociationsForResourceType(std::move(request));
  return internal::MakeTracedStreamRange<
      google::cloud::backupdr::v1::BackupPlanAssociation>(std::move(span),
                                                          std::move(sr));
}

future<StatusOr<google::cloud::backupdr::v1::OperationMetadata>>
BackupDRTracingConnection::DeleteBackupPlanAssociation(
    google::cloud::backupdr::v1::DeleteBackupPlanAssociationRequest const&
        request) {
  auto span = internal::MakeSpan(
      "backupdr_v1::BackupDRConnection::DeleteBackupPlanAssociation");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->DeleteBackupPlanAssociation(request));
}

StatusOr<google::longrunning::Operation>
BackupDRTracingConnection::DeleteBackupPlanAssociation(
    NoAwaitTag,
    google::cloud::backupdr::v1::DeleteBackupPlanAssociationRequest const&
        request) {
  auto span = internal::MakeSpan(
      "backupdr_v1::BackupDRConnection::DeleteBackupPlanAssociation");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(
      *span, child_->DeleteBackupPlanAssociation(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::backupdr::v1::OperationMetadata>>
BackupDRTracingConnection::DeleteBackupPlanAssociation(
    google::longrunning::Operation const& operation) {
  auto span = internal::MakeSpan(
      "backupdr_v1::BackupDRConnection::DeleteBackupPlanAssociation");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->DeleteBackupPlanAssociation(operation));
}

future<StatusOr<google::cloud::backupdr::v1::BackupPlanAssociation>>
BackupDRTracingConnection::TriggerBackup(
    google::cloud::backupdr::v1::TriggerBackupRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::TriggerBackup");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->TriggerBackup(request));
}

StatusOr<google::longrunning::Operation>
BackupDRTracingConnection::TriggerBackup(
    NoAwaitTag,
    google::cloud::backupdr::v1::TriggerBackupRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::TriggerBackup");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span, child_->TriggerBackup(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::backupdr::v1::BackupPlanAssociation>>
BackupDRTracingConnection::TriggerBackup(
    google::longrunning::Operation const& operation) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::TriggerBackup");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->TriggerBackup(operation));
}

StatusOr<google::cloud::backupdr::v1::DataSourceReference>
BackupDRTracingConnection::GetDataSourceReference(
    google::cloud::backupdr::v1::GetDataSourceReferenceRequest const& request) {
  auto span = internal::MakeSpan(
      "backupdr_v1::BackupDRConnection::GetDataSourceReference");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->GetDataSourceReference(request));
}

StreamRange<google::cloud::backupdr::v1::DataSourceReference>
BackupDRTracingConnection::FetchDataSourceReferencesForResourceType(
    google::cloud::backupdr::v1::FetchDataSourceReferencesForResourceTypeRequest
        request) {
  auto span = internal::MakeSpan(
      "backupdr_v1::BackupDRConnection::"
      "FetchDataSourceReferencesForResourceType");
  internal::OTelScope scope(span);
  auto sr =
      child_->FetchDataSourceReferencesForResourceType(std::move(request));
  return internal::MakeTracedStreamRange<
      google::cloud::backupdr::v1::DataSourceReference>(std::move(span),
                                                        std::move(sr));
}

future<StatusOr<google::cloud::backupdr::v1::InitializeServiceResponse>>
BackupDRTracingConnection::InitializeService(
    google::cloud::backupdr::v1::InitializeServiceRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::InitializeService");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->InitializeService(request));
}

StatusOr<google::longrunning::Operation>
BackupDRTracingConnection::InitializeService(
    NoAwaitTag,
    google::cloud::backupdr::v1::InitializeServiceRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::InitializeService");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span,
                           child_->InitializeService(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::backupdr::v1::InitializeServiceResponse>>
BackupDRTracingConnection::InitializeService(
    google::longrunning::Operation const& operation) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::InitializeService");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->InitializeService(operation));
}

StreamRange<google::cloud::location::Location>
BackupDRTracingConnection::ListLocations(
    google::cloud::location::ListLocationsRequest request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::ListLocations");
  internal::OTelScope scope(span);
  auto sr = child_->ListLocations(std::move(request));
  return internal::MakeTracedStreamRange<google::cloud::location::Location>(
      std::move(span), std::move(sr));
}

StatusOr<google::cloud::location::Location>
BackupDRTracingConnection::GetLocation(
    google::cloud::location::GetLocationRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::GetLocation");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->GetLocation(request));
}

StatusOr<google::iam::v1::Policy> BackupDRTracingConnection::SetIamPolicy(
    google::iam::v1::SetIamPolicyRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::SetIamPolicy");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->SetIamPolicy(request));
}

StatusOr<google::iam::v1::Policy> BackupDRTracingConnection::GetIamPolicy(
    google::iam::v1::GetIamPolicyRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::GetIamPolicy");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->GetIamPolicy(request));
}

StatusOr<google::iam::v1::TestIamPermissionsResponse>
BackupDRTracingConnection::TestIamPermissions(
    google::iam::v1::TestIamPermissionsRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::TestIamPermissions");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->TestIamPermissions(request));
}

StreamRange<google::longrunning::Operation>
BackupDRTracingConnection::ListOperations(
    google::longrunning::ListOperationsRequest request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::ListOperations");
  internal::OTelScope scope(span);
  auto sr = child_->ListOperations(std::move(request));
  return internal::MakeTracedStreamRange<google::longrunning::Operation>(
      std::move(span), std::move(sr));
}

StatusOr<google::longrunning::Operation>
BackupDRTracingConnection::GetOperation(
    google::longrunning::GetOperationRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::GetOperation");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->GetOperation(request));
}

Status BackupDRTracingConnection::DeleteOperation(
    google::longrunning::DeleteOperationRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::DeleteOperation");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->DeleteOperation(request));
}

Status BackupDRTracingConnection::CancelOperation(
    google::longrunning::CancelOperationRequest const& request) {
  auto span =
      internal::MakeSpan("backupdr_v1::BackupDRConnection::CancelOperation");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->CancelOperation(request));
}

#endif  // GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY

std::shared_ptr<backupdr_v1::BackupDRConnection> MakeBackupDRTracingConnection(
    std::shared_ptr<backupdr_v1::BackupDRConnection> conn) {
#ifdef GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY
  if (internal::TracingEnabled(conn->options())) {
    conn = std::make_shared<BackupDRTracingConnection>(std::move(conn));
  }
#endif  // GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY
  return conn;
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace backupdr_v1_internal
}  // namespace cloud
}  // namespace google
