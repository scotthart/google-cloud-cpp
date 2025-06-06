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
// source: google/storage/control/v2/storage_control.proto

#include "google/cloud/storagecontrol/v2/internal/storage_control_stub.h"
#include "google/cloud/grpc_error_delegate.h"
#include "google/cloud/status_or.h"
#include <google/longrunning/operations.grpc.pb.h>
#include <google/storage/control/v2/storage_control.grpc.pb.h>
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace storagecontrol_v2_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

StorageControlStub::~StorageControlStub() = default;

StatusOr<google::storage::control::v2::Folder>
DefaultStorageControlStub::CreateFolder(
    grpc::ClientContext& context, Options const&,
    google::storage::control::v2::CreateFolderRequest const& request) {
  google::storage::control::v2::Folder response;
  auto status = grpc_stub_->CreateFolder(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

Status DefaultStorageControlStub::DeleteFolder(
    grpc::ClientContext& context, Options const&,
    google::storage::control::v2::DeleteFolderRequest const& request) {
  google::protobuf::Empty response;
  auto status = grpc_stub_->DeleteFolder(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return google::cloud::Status();
}

StatusOr<google::storage::control::v2::Folder>
DefaultStorageControlStub::GetFolder(
    grpc::ClientContext& context, Options const&,
    google::storage::control::v2::GetFolderRequest const& request) {
  google::storage::control::v2::Folder response;
  auto status = grpc_stub_->GetFolder(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::storage::control::v2::ListFoldersResponse>
DefaultStorageControlStub::ListFolders(
    grpc::ClientContext& context, Options const&,
    google::storage::control::v2::ListFoldersRequest const& request) {
  google::storage::control::v2::ListFoldersResponse response;
  auto status = grpc_stub_->ListFolders(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

future<StatusOr<google::longrunning::Operation>>
DefaultStorageControlStub::AsyncRenameFolder(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions,
    google::storage::control::v2::RenameFolderRequest const& request) {
  return internal::MakeUnaryRpcImpl<
      google::storage::control::v2::RenameFolderRequest,
      google::longrunning::Operation>(
      cq,
      [this](grpc::ClientContext* context,
             google::storage::control::v2::RenameFolderRequest const& request,
             grpc::CompletionQueue* cq) {
        return grpc_stub_->AsyncRenameFolder(context, request, cq);
      },
      request, std::move(context));
}

StatusOr<google::longrunning::Operation>
DefaultStorageControlStub::RenameFolder(
    grpc::ClientContext& context, Options,
    google::storage::control::v2::RenameFolderRequest const& request) {
  google::longrunning::Operation response;
  auto status = grpc_stub_->RenameFolder(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::storage::control::v2::StorageLayout>
DefaultStorageControlStub::GetStorageLayout(
    grpc::ClientContext& context, Options const&,
    google::storage::control::v2::GetStorageLayoutRequest const& request) {
  google::storage::control::v2::StorageLayout response;
  auto status = grpc_stub_->GetStorageLayout(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::storage::control::v2::ManagedFolder>
DefaultStorageControlStub::CreateManagedFolder(
    grpc::ClientContext& context, Options const&,
    google::storage::control::v2::CreateManagedFolderRequest const& request) {
  google::storage::control::v2::ManagedFolder response;
  auto status = grpc_stub_->CreateManagedFolder(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

Status DefaultStorageControlStub::DeleteManagedFolder(
    grpc::ClientContext& context, Options const&,
    google::storage::control::v2::DeleteManagedFolderRequest const& request) {
  google::protobuf::Empty response;
  auto status = grpc_stub_->DeleteManagedFolder(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return google::cloud::Status();
}

StatusOr<google::storage::control::v2::ManagedFolder>
DefaultStorageControlStub::GetManagedFolder(
    grpc::ClientContext& context, Options const&,
    google::storage::control::v2::GetManagedFolderRequest const& request) {
  google::storage::control::v2::ManagedFolder response;
  auto status = grpc_stub_->GetManagedFolder(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::storage::control::v2::ListManagedFoldersResponse>
DefaultStorageControlStub::ListManagedFolders(
    grpc::ClientContext& context, Options const&,
    google::storage::control::v2::ListManagedFoldersRequest const& request) {
  google::storage::control::v2::ListManagedFoldersResponse response;
  auto status = grpc_stub_->ListManagedFolders(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

future<StatusOr<google::longrunning::Operation>>
DefaultStorageControlStub::AsyncCreateAnywhereCache(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions,
    google::storage::control::v2::CreateAnywhereCacheRequest const& request) {
  return internal::MakeUnaryRpcImpl<
      google::storage::control::v2::CreateAnywhereCacheRequest,
      google::longrunning::Operation>(
      cq,
      [this](grpc::ClientContext* context,
             google::storage::control::v2::CreateAnywhereCacheRequest const&
                 request,
             grpc::CompletionQueue* cq) {
        return grpc_stub_->AsyncCreateAnywhereCache(context, request, cq);
      },
      request, std::move(context));
}

StatusOr<google::longrunning::Operation>
DefaultStorageControlStub::CreateAnywhereCache(
    grpc::ClientContext& context, Options,
    google::storage::control::v2::CreateAnywhereCacheRequest const& request) {
  google::longrunning::Operation response;
  auto status = grpc_stub_->CreateAnywhereCache(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

future<StatusOr<google::longrunning::Operation>>
DefaultStorageControlStub::AsyncUpdateAnywhereCache(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions,
    google::storage::control::v2::UpdateAnywhereCacheRequest const& request) {
  return internal::MakeUnaryRpcImpl<
      google::storage::control::v2::UpdateAnywhereCacheRequest,
      google::longrunning::Operation>(
      cq,
      [this](grpc::ClientContext* context,
             google::storage::control::v2::UpdateAnywhereCacheRequest const&
                 request,
             grpc::CompletionQueue* cq) {
        return grpc_stub_->AsyncUpdateAnywhereCache(context, request, cq);
      },
      request, std::move(context));
}

StatusOr<google::longrunning::Operation>
DefaultStorageControlStub::UpdateAnywhereCache(
    grpc::ClientContext& context, Options,
    google::storage::control::v2::UpdateAnywhereCacheRequest const& request) {
  google::longrunning::Operation response;
  auto status = grpc_stub_->UpdateAnywhereCache(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::storage::control::v2::AnywhereCache>
DefaultStorageControlStub::DisableAnywhereCache(
    grpc::ClientContext& context, Options const&,
    google::storage::control::v2::DisableAnywhereCacheRequest const& request) {
  google::storage::control::v2::AnywhereCache response;
  auto status = grpc_stub_->DisableAnywhereCache(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::storage::control::v2::AnywhereCache>
DefaultStorageControlStub::PauseAnywhereCache(
    grpc::ClientContext& context, Options const&,
    google::storage::control::v2::PauseAnywhereCacheRequest const& request) {
  google::storage::control::v2::AnywhereCache response;
  auto status = grpc_stub_->PauseAnywhereCache(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::storage::control::v2::AnywhereCache>
DefaultStorageControlStub::ResumeAnywhereCache(
    grpc::ClientContext& context, Options const&,
    google::storage::control::v2::ResumeAnywhereCacheRequest const& request) {
  google::storage::control::v2::AnywhereCache response;
  auto status = grpc_stub_->ResumeAnywhereCache(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::storage::control::v2::AnywhereCache>
DefaultStorageControlStub::GetAnywhereCache(
    grpc::ClientContext& context, Options const&,
    google::storage::control::v2::GetAnywhereCacheRequest const& request) {
  google::storage::control::v2::AnywhereCache response;
  auto status = grpc_stub_->GetAnywhereCache(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::storage::control::v2::ListAnywhereCachesResponse>
DefaultStorageControlStub::ListAnywhereCaches(
    grpc::ClientContext& context, Options const&,
    google::storage::control::v2::ListAnywhereCachesRequest const& request) {
  google::storage::control::v2::ListAnywhereCachesResponse response;
  auto status = grpc_stub_->ListAnywhereCaches(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::storage::control::v2::IntelligenceConfig>
DefaultStorageControlStub::GetProjectIntelligenceConfig(
    grpc::ClientContext& context, Options const&,
    google::storage::control::v2::GetProjectIntelligenceConfigRequest const&
        request) {
  google::storage::control::v2::IntelligenceConfig response;
  auto status =
      grpc_stub_->GetProjectIntelligenceConfig(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::storage::control::v2::IntelligenceConfig>
DefaultStorageControlStub::UpdateProjectIntelligenceConfig(
    grpc::ClientContext& context, Options const&,
    google::storage::control::v2::UpdateProjectIntelligenceConfigRequest const&
        request) {
  google::storage::control::v2::IntelligenceConfig response;
  auto status =
      grpc_stub_->UpdateProjectIntelligenceConfig(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::storage::control::v2::IntelligenceConfig>
DefaultStorageControlStub::GetFolderIntelligenceConfig(
    grpc::ClientContext& context, Options const&,
    google::storage::control::v2::GetFolderIntelligenceConfigRequest const&
        request) {
  google::storage::control::v2::IntelligenceConfig response;
  auto status =
      grpc_stub_->GetFolderIntelligenceConfig(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::storage::control::v2::IntelligenceConfig>
DefaultStorageControlStub::UpdateFolderIntelligenceConfig(
    grpc::ClientContext& context, Options const&,
    google::storage::control::v2::UpdateFolderIntelligenceConfigRequest const&
        request) {
  google::storage::control::v2::IntelligenceConfig response;
  auto status =
      grpc_stub_->UpdateFolderIntelligenceConfig(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::storage::control::v2::IntelligenceConfig>
DefaultStorageControlStub::GetOrganizationIntelligenceConfig(
    grpc::ClientContext& context, Options const&,
    google::storage::control::v2::
        GetOrganizationIntelligenceConfigRequest const& request) {
  google::storage::control::v2::IntelligenceConfig response;
  auto status = grpc_stub_->GetOrganizationIntelligenceConfig(&context, request,
                                                              &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::storage::control::v2::IntelligenceConfig>
DefaultStorageControlStub::UpdateOrganizationIntelligenceConfig(
    grpc::ClientContext& context, Options const&,
    google::storage::control::v2::
        UpdateOrganizationIntelligenceConfigRequest const& request) {
  google::storage::control::v2::IntelligenceConfig response;
  auto status = grpc_stub_->UpdateOrganizationIntelligenceConfig(
      &context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

future<StatusOr<google::longrunning::Operation>>
DefaultStorageControlStub::AsyncGetOperation(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    google::cloud::internal::ImmutableOptions,
    google::longrunning::GetOperationRequest const& request) {
  return internal::MakeUnaryRpcImpl<google::longrunning::GetOperationRequest,
                                    google::longrunning::Operation>(
      cq,
      [this](grpc::ClientContext* context,
             google::longrunning::GetOperationRequest const& request,
             grpc::CompletionQueue* cq) {
        return operations_stub_->AsyncGetOperation(context, request, cq);
      },
      request, std::move(context));
}

future<Status> DefaultStorageControlStub::AsyncCancelOperation(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    google::cloud::internal::ImmutableOptions,
    google::longrunning::CancelOperationRequest const& request) {
  return internal::MakeUnaryRpcImpl<google::longrunning::CancelOperationRequest,
                                    google::protobuf::Empty>(
             cq,
             [this](grpc::ClientContext* context,
                    google::longrunning::CancelOperationRequest const& request,
                    grpc::CompletionQueue* cq) {
               return operations_stub_->AsyncCancelOperation(context, request,
                                                             cq);
             },
             request, std::move(context))
      .then([](future<StatusOr<google::protobuf::Empty>> f) {
        return f.get().status();
      });
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace storagecontrol_v2_internal
}  // namespace cloud
}  // namespace google
