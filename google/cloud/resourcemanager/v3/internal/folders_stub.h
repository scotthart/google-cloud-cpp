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
// source: google/cloud/resourcemanager/v3/folders.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_RESOURCEMANAGER_V3_INTERNAL_FOLDERS_STUB_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_RESOURCEMANAGER_V3_INTERNAL_FOLDERS_STUB_H

#include "google/cloud/completion_queue.h"
#include "google/cloud/future.h"
#include "google/cloud/options.h"
#include "google/cloud/status_or.h"
#include "google/cloud/version.h"
#include <google/cloud/resourcemanager/v3/folders.grpc.pb.h>
#include <google/longrunning/operations.grpc.pb.h>
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace resourcemanager_v3_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

class FoldersStub {
 public:
  virtual ~FoldersStub() = 0;

  virtual StatusOr<google::cloud::resourcemanager::v3::Folder> GetFolder(
      grpc::ClientContext& context, Options const& options,
      google::cloud::resourcemanager::v3::GetFolderRequest const& request) = 0;

  virtual StatusOr<google::cloud::resourcemanager::v3::ListFoldersResponse>
  ListFolders(grpc::ClientContext& context, Options const& options,
              google::cloud::resourcemanager::v3::ListFoldersRequest const&
                  request) = 0;

  virtual StatusOr<google::cloud::resourcemanager::v3::SearchFoldersResponse>
  SearchFolders(grpc::ClientContext& context, Options const& options,
                google::cloud::resourcemanager::v3::SearchFoldersRequest const&
                    request) = 0;

  virtual future<StatusOr<google::longrunning::Operation>> AsyncCreateFolder(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::cloud::resourcemanager::v3::CreateFolderRequest const&
          request) = 0;

  virtual StatusOr<google::longrunning::Operation> CreateFolder(
      grpc::ClientContext& context, Options options,
      google::cloud::resourcemanager::v3::CreateFolderRequest const&
          request) = 0;

  virtual future<StatusOr<google::longrunning::Operation>> AsyncUpdateFolder(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::cloud::resourcemanager::v3::UpdateFolderRequest const&
          request) = 0;

  virtual StatusOr<google::longrunning::Operation> UpdateFolder(
      grpc::ClientContext& context, Options options,
      google::cloud::resourcemanager::v3::UpdateFolderRequest const&
          request) = 0;

  virtual future<StatusOr<google::longrunning::Operation>> AsyncMoveFolder(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::cloud::resourcemanager::v3::MoveFolderRequest const& request) = 0;

  virtual StatusOr<google::longrunning::Operation> MoveFolder(
      grpc::ClientContext& context, Options options,
      google::cloud::resourcemanager::v3::MoveFolderRequest const& request) = 0;

  virtual future<StatusOr<google::longrunning::Operation>> AsyncDeleteFolder(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::cloud::resourcemanager::v3::DeleteFolderRequest const&
          request) = 0;

  virtual StatusOr<google::longrunning::Operation> DeleteFolder(
      grpc::ClientContext& context, Options options,
      google::cloud::resourcemanager::v3::DeleteFolderRequest const&
          request) = 0;

  virtual future<StatusOr<google::longrunning::Operation>> AsyncUndeleteFolder(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::cloud::resourcemanager::v3::UndeleteFolderRequest const&
          request) = 0;

  virtual StatusOr<google::longrunning::Operation> UndeleteFolder(
      grpc::ClientContext& context, Options options,
      google::cloud::resourcemanager::v3::UndeleteFolderRequest const&
          request) = 0;

  virtual StatusOr<google::iam::v1::Policy> GetIamPolicy(
      grpc::ClientContext& context, Options const& options,
      google::iam::v1::GetIamPolicyRequest const& request) = 0;

  virtual StatusOr<google::iam::v1::Policy> SetIamPolicy(
      grpc::ClientContext& context, Options const& options,
      google::iam::v1::SetIamPolicyRequest const& request) = 0;

  virtual StatusOr<google::iam::v1::TestIamPermissionsResponse>
  TestIamPermissions(
      grpc::ClientContext& context, Options const& options,
      google::iam::v1::TestIamPermissionsRequest const& request) = 0;

  virtual StatusOr<google::longrunning::Operation> GetOperation(
      grpc::ClientContext& context, Options const& options,
      google::longrunning::GetOperationRequest const& request) = 0;

  virtual future<StatusOr<google::longrunning::Operation>> AsyncGetOperation(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::longrunning::GetOperationRequest const& request) = 0;

  virtual future<Status> AsyncCancelOperation(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::longrunning::CancelOperationRequest const& request) = 0;
};

class DefaultFoldersStub : public FoldersStub {
 public:
  DefaultFoldersStub(
      std::unique_ptr<
          google::cloud::resourcemanager::v3::Folders::StubInterface>
          grpc_stub,
      std::unique_ptr<google::longrunning::Operations::StubInterface>
          operations_stub)
      : grpc_stub_(std::move(grpc_stub)),
        operations_stub_(std::move(operations_stub)) {}

  StatusOr<google::cloud::resourcemanager::v3::Folder> GetFolder(
      grpc::ClientContext& context, Options const& options,
      google::cloud::resourcemanager::v3::GetFolderRequest const& request)
      override;

  StatusOr<google::cloud::resourcemanager::v3::ListFoldersResponse> ListFolders(
      grpc::ClientContext& context, Options const& options,
      google::cloud::resourcemanager::v3::ListFoldersRequest const& request)
      override;

  StatusOr<google::cloud::resourcemanager::v3::SearchFoldersResponse>
  SearchFolders(grpc::ClientContext& context, Options const& options,
                google::cloud::resourcemanager::v3::SearchFoldersRequest const&
                    request) override;

  future<StatusOr<google::longrunning::Operation>> AsyncCreateFolder(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::cloud::resourcemanager::v3::CreateFolderRequest const& request)
      override;

  StatusOr<google::longrunning::Operation> CreateFolder(
      grpc::ClientContext& context, Options options,
      google::cloud::resourcemanager::v3::CreateFolderRequest const& request)
      override;

  future<StatusOr<google::longrunning::Operation>> AsyncUpdateFolder(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::cloud::resourcemanager::v3::UpdateFolderRequest const& request)
      override;

  StatusOr<google::longrunning::Operation> UpdateFolder(
      grpc::ClientContext& context, Options options,
      google::cloud::resourcemanager::v3::UpdateFolderRequest const& request)
      override;

  future<StatusOr<google::longrunning::Operation>> AsyncMoveFolder(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::cloud::resourcemanager::v3::MoveFolderRequest const& request)
      override;

  StatusOr<google::longrunning::Operation> MoveFolder(
      grpc::ClientContext& context, Options options,
      google::cloud::resourcemanager::v3::MoveFolderRequest const& request)
      override;

  future<StatusOr<google::longrunning::Operation>> AsyncDeleteFolder(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::cloud::resourcemanager::v3::DeleteFolderRequest const& request)
      override;

  StatusOr<google::longrunning::Operation> DeleteFolder(
      grpc::ClientContext& context, Options options,
      google::cloud::resourcemanager::v3::DeleteFolderRequest const& request)
      override;

  future<StatusOr<google::longrunning::Operation>> AsyncUndeleteFolder(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::cloud::resourcemanager::v3::UndeleteFolderRequest const& request)
      override;

  StatusOr<google::longrunning::Operation> UndeleteFolder(
      grpc::ClientContext& context, Options options,
      google::cloud::resourcemanager::v3::UndeleteFolderRequest const& request)
      override;

  StatusOr<google::iam::v1::Policy> GetIamPolicy(
      grpc::ClientContext& context, Options const& options,
      google::iam::v1::GetIamPolicyRequest const& request) override;

  StatusOr<google::iam::v1::Policy> SetIamPolicy(
      grpc::ClientContext& context, Options const& options,
      google::iam::v1::SetIamPolicyRequest const& request) override;

  StatusOr<google::iam::v1::TestIamPermissionsResponse> TestIamPermissions(
      grpc::ClientContext& context, Options const& options,
      google::iam::v1::TestIamPermissionsRequest const& request) override;

  StatusOr<google::longrunning::Operation> GetOperation(
      grpc::ClientContext& context, Options const& options,
      google::longrunning::GetOperationRequest const& request) override;

  future<StatusOr<google::longrunning::Operation>> AsyncGetOperation(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::longrunning::GetOperationRequest const& request) override;

  future<Status> AsyncCancelOperation(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::longrunning::CancelOperationRequest const& request) override;

 private:
  std::unique_ptr<google::cloud::resourcemanager::v3::Folders::StubInterface>
      grpc_stub_;
  std::unique_ptr<google::longrunning::Operations::StubInterface>
      operations_stub_;
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace resourcemanager_v3_internal
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_RESOURCEMANAGER_V3_INTERNAL_FOLDERS_STUB_H
