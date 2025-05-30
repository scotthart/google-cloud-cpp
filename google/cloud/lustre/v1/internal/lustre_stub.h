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
// source: google/cloud/lustre/v1/lustre.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_LUSTRE_V1_INTERNAL_LUSTRE_STUB_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_LUSTRE_V1_INTERNAL_LUSTRE_STUB_H

#include "google/cloud/completion_queue.h"
#include "google/cloud/future.h"
#include "google/cloud/options.h"
#include "google/cloud/status_or.h"
#include "google/cloud/version.h"
#include <google/cloud/location/locations.grpc.pb.h>
#include <google/cloud/lustre/v1/lustre.grpc.pb.h>
#include <google/longrunning/operations.grpc.pb.h>
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace lustre_v1_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

class LustreStub {
 public:
  virtual ~LustreStub() = 0;

  virtual StatusOr<google::cloud::lustre::v1::ListInstancesResponse>
  ListInstances(
      grpc::ClientContext& context, Options const& options,
      google::cloud::lustre::v1::ListInstancesRequest const& request) = 0;

  virtual StatusOr<google::cloud::lustre::v1::Instance> GetInstance(
      grpc::ClientContext& context, Options const& options,
      google::cloud::lustre::v1::GetInstanceRequest const& request) = 0;

  virtual future<StatusOr<google::longrunning::Operation>> AsyncCreateInstance(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::cloud::lustre::v1::CreateInstanceRequest const& request) = 0;

  virtual StatusOr<google::longrunning::Operation> CreateInstance(
      grpc::ClientContext& context, Options options,
      google::cloud::lustre::v1::CreateInstanceRequest const& request) = 0;

  virtual future<StatusOr<google::longrunning::Operation>> AsyncUpdateInstance(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::cloud::lustre::v1::UpdateInstanceRequest const& request) = 0;

  virtual StatusOr<google::longrunning::Operation> UpdateInstance(
      grpc::ClientContext& context, Options options,
      google::cloud::lustre::v1::UpdateInstanceRequest const& request) = 0;

  virtual future<StatusOr<google::longrunning::Operation>> AsyncDeleteInstance(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::cloud::lustre::v1::DeleteInstanceRequest const& request) = 0;

  virtual StatusOr<google::longrunning::Operation> DeleteInstance(
      grpc::ClientContext& context, Options options,
      google::cloud::lustre::v1::DeleteInstanceRequest const& request) = 0;

  virtual future<StatusOr<google::longrunning::Operation>> AsyncImportData(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::cloud::lustre::v1::ImportDataRequest const& request) = 0;

  virtual StatusOr<google::longrunning::Operation> ImportData(
      grpc::ClientContext& context, Options options,
      google::cloud::lustre::v1::ImportDataRequest const& request) = 0;

  virtual future<StatusOr<google::longrunning::Operation>> AsyncExportData(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::cloud::lustre::v1::ExportDataRequest const& request) = 0;

  virtual StatusOr<google::longrunning::Operation> ExportData(
      grpc::ClientContext& context, Options options,
      google::cloud::lustre::v1::ExportDataRequest const& request) = 0;

  virtual StatusOr<google::cloud::location::ListLocationsResponse>
  ListLocations(
      grpc::ClientContext& context, Options const& options,
      google::cloud::location::ListLocationsRequest const& request) = 0;

  virtual StatusOr<google::cloud::location::Location> GetLocation(
      grpc::ClientContext& context, Options const& options,
      google::cloud::location::GetLocationRequest const& request) = 0;

  virtual StatusOr<google::longrunning::ListOperationsResponse> ListOperations(
      grpc::ClientContext& context, Options const& options,
      google::longrunning::ListOperationsRequest const& request) = 0;

  virtual StatusOr<google::longrunning::Operation> GetOperation(
      grpc::ClientContext& context, Options const& options,
      google::longrunning::GetOperationRequest const& request) = 0;

  virtual Status DeleteOperation(
      grpc::ClientContext& context, Options const& options,
      google::longrunning::DeleteOperationRequest const& request) = 0;

  virtual Status CancelOperation(
      grpc::ClientContext& context, Options const& options,
      google::longrunning::CancelOperationRequest const& request) = 0;

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

class DefaultLustreStub : public LustreStub {
 public:
  DefaultLustreStub(
      std::unique_ptr<google::cloud::lustre::v1::Lustre::StubInterface>
          grpc_stub,
      std::unique_ptr<google::cloud::location::Locations::StubInterface>
          locations_stub,
      std::unique_ptr<google::longrunning::Operations::StubInterface>
          operations_stub)
      : grpc_stub_(std::move(grpc_stub)),
        locations_stub_(std::move(locations_stub)),
        operations_stub_(std::move(operations_stub)) {}

  StatusOr<google::cloud::lustre::v1::ListInstancesResponse> ListInstances(
      grpc::ClientContext& context, Options const& options,
      google::cloud::lustre::v1::ListInstancesRequest const& request) override;

  StatusOr<google::cloud::lustre::v1::Instance> GetInstance(
      grpc::ClientContext& context, Options const& options,
      google::cloud::lustre::v1::GetInstanceRequest const& request) override;

  future<StatusOr<google::longrunning::Operation>> AsyncCreateInstance(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::cloud::lustre::v1::CreateInstanceRequest const& request) override;

  StatusOr<google::longrunning::Operation> CreateInstance(
      grpc::ClientContext& context, Options options,
      google::cloud::lustre::v1::CreateInstanceRequest const& request) override;

  future<StatusOr<google::longrunning::Operation>> AsyncUpdateInstance(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::cloud::lustre::v1::UpdateInstanceRequest const& request) override;

  StatusOr<google::longrunning::Operation> UpdateInstance(
      grpc::ClientContext& context, Options options,
      google::cloud::lustre::v1::UpdateInstanceRequest const& request) override;

  future<StatusOr<google::longrunning::Operation>> AsyncDeleteInstance(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::cloud::lustre::v1::DeleteInstanceRequest const& request) override;

  StatusOr<google::longrunning::Operation> DeleteInstance(
      grpc::ClientContext& context, Options options,
      google::cloud::lustre::v1::DeleteInstanceRequest const& request) override;

  future<StatusOr<google::longrunning::Operation>> AsyncImportData(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::cloud::lustre::v1::ImportDataRequest const& request) override;

  StatusOr<google::longrunning::Operation> ImportData(
      grpc::ClientContext& context, Options options,
      google::cloud::lustre::v1::ImportDataRequest const& request) override;

  future<StatusOr<google::longrunning::Operation>> AsyncExportData(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::cloud::lustre::v1::ExportDataRequest const& request) override;

  StatusOr<google::longrunning::Operation> ExportData(
      grpc::ClientContext& context, Options options,
      google::cloud::lustre::v1::ExportDataRequest const& request) override;

  StatusOr<google::cloud::location::ListLocationsResponse> ListLocations(
      grpc::ClientContext& context, Options const& options,
      google::cloud::location::ListLocationsRequest const& request) override;

  StatusOr<google::cloud::location::Location> GetLocation(
      grpc::ClientContext& context, Options const& options,
      google::cloud::location::GetLocationRequest const& request) override;

  StatusOr<google::longrunning::ListOperationsResponse> ListOperations(
      grpc::ClientContext& context, Options const& options,
      google::longrunning::ListOperationsRequest const& request) override;

  StatusOr<google::longrunning::Operation> GetOperation(
      grpc::ClientContext& context, Options const& options,
      google::longrunning::GetOperationRequest const& request) override;

  Status DeleteOperation(
      grpc::ClientContext& context, Options const& options,
      google::longrunning::DeleteOperationRequest const& request) override;

  Status CancelOperation(
      grpc::ClientContext& context, Options const& options,
      google::longrunning::CancelOperationRequest const& request) override;

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
  std::unique_ptr<google::cloud::lustre::v1::Lustre::StubInterface> grpc_stub_;
  std::unique_ptr<google::cloud::location::Locations::StubInterface>
      locations_stub_;
  std::unique_ptr<google::longrunning::Operations::StubInterface>
      operations_stub_;
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace lustre_v1_internal
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_LUSTRE_V1_INTERNAL_LUSTRE_STUB_H
