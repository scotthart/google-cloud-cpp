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
// source: google/cloud/storageinsights/v1/storageinsights.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_STORAGEINSIGHTS_V1_INTERNAL_STORAGE_INSIGHTS_AUTH_DECORATOR_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_STORAGEINSIGHTS_V1_INTERNAL_STORAGE_INSIGHTS_AUTH_DECORATOR_H

#include "google/cloud/storageinsights/v1/internal/storage_insights_stub.h"
#include "google/cloud/internal/unified_grpc_credentials.h"
#include "google/cloud/version.h"
#include <google/longrunning/operations.grpc.pb.h>
#include <memory>
#include <set>
#include <string>

namespace google {
namespace cloud {
namespace storageinsights_v1_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

class StorageInsightsAuth : public StorageInsightsStub {
 public:
  ~StorageInsightsAuth() override = default;
  StorageInsightsAuth(
      std::shared_ptr<google::cloud::internal::GrpcAuthenticationStrategy> auth,
      std::shared_ptr<StorageInsightsStub> child);

  StatusOr<google::cloud::storageinsights::v1::ListReportConfigsResponse>
  ListReportConfigs(
      grpc::ClientContext& context, Options const& options,
      google::cloud::storageinsights::v1::ListReportConfigsRequest const&
          request) override;

  StatusOr<google::cloud::storageinsights::v1::ReportConfig> GetReportConfig(
      grpc::ClientContext& context, Options const& options,
      google::cloud::storageinsights::v1::GetReportConfigRequest const& request)
      override;

  StatusOr<google::cloud::storageinsights::v1::ReportConfig> CreateReportConfig(
      grpc::ClientContext& context, Options const& options,
      google::cloud::storageinsights::v1::CreateReportConfigRequest const&
          request) override;

  StatusOr<google::cloud::storageinsights::v1::ReportConfig> UpdateReportConfig(
      grpc::ClientContext& context, Options const& options,
      google::cloud::storageinsights::v1::UpdateReportConfigRequest const&
          request) override;

  Status DeleteReportConfig(
      grpc::ClientContext& context, Options const& options,
      google::cloud::storageinsights::v1::DeleteReportConfigRequest const&
          request) override;

  StatusOr<google::cloud::storageinsights::v1::ListReportDetailsResponse>
  ListReportDetails(
      grpc::ClientContext& context, Options const& options,
      google::cloud::storageinsights::v1::ListReportDetailsRequest const&
          request) override;

  StatusOr<google::cloud::storageinsights::v1::ReportDetail> GetReportDetail(
      grpc::ClientContext& context, Options const& options,
      google::cloud::storageinsights::v1::GetReportDetailRequest const& request)
      override;

  StatusOr<google::cloud::storageinsights::v1::ListDatasetConfigsResponse>
  ListDatasetConfigs(
      grpc::ClientContext& context, Options const& options,
      google::cloud::storageinsights::v1::ListDatasetConfigsRequest const&
          request) override;

  StatusOr<google::cloud::storageinsights::v1::DatasetConfig> GetDatasetConfig(
      grpc::ClientContext& context, Options const& options,
      google::cloud::storageinsights::v1::GetDatasetConfigRequest const&
          request) override;

  future<StatusOr<google::longrunning::Operation>> AsyncCreateDatasetConfig(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::cloud::storageinsights::v1::CreateDatasetConfigRequest const&
          request) override;

  StatusOr<google::longrunning::Operation> CreateDatasetConfig(
      grpc::ClientContext& context, Options options,
      google::cloud::storageinsights::v1::CreateDatasetConfigRequest const&
          request) override;

  future<StatusOr<google::longrunning::Operation>> AsyncUpdateDatasetConfig(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::cloud::storageinsights::v1::UpdateDatasetConfigRequest const&
          request) override;

  StatusOr<google::longrunning::Operation> UpdateDatasetConfig(
      grpc::ClientContext& context, Options options,
      google::cloud::storageinsights::v1::UpdateDatasetConfigRequest const&
          request) override;

  future<StatusOr<google::longrunning::Operation>> AsyncDeleteDatasetConfig(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::cloud::storageinsights::v1::DeleteDatasetConfigRequest const&
          request) override;

  StatusOr<google::longrunning::Operation> DeleteDatasetConfig(
      grpc::ClientContext& context, Options options,
      google::cloud::storageinsights::v1::DeleteDatasetConfigRequest const&
          request) override;

  future<StatusOr<google::longrunning::Operation>> AsyncLinkDataset(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::cloud::storageinsights::v1::LinkDatasetRequest const& request)
      override;

  StatusOr<google::longrunning::Operation> LinkDataset(
      grpc::ClientContext& context, Options options,
      google::cloud::storageinsights::v1::LinkDatasetRequest const& request)
      override;

  future<StatusOr<google::longrunning::Operation>> AsyncUnlinkDataset(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::cloud::storageinsights::v1::UnlinkDatasetRequest const& request)
      override;

  StatusOr<google::longrunning::Operation> UnlinkDataset(
      grpc::ClientContext& context, Options options,
      google::cloud::storageinsights::v1::UnlinkDatasetRequest const& request)
      override;

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
  std::shared_ptr<google::cloud::internal::GrpcAuthenticationStrategy> auth_;
  std::shared_ptr<StorageInsightsStub> child_;
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace storageinsights_v1_internal
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_STORAGEINSIGHTS_V1_INTERNAL_STORAGE_INSIGHTS_AUTH_DECORATOR_H
