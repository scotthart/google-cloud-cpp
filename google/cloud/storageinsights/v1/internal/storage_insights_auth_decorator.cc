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

#include "google/cloud/storageinsights/v1/internal/storage_insights_auth_decorator.h"
#include <google/cloud/storageinsights/v1/storageinsights.grpc.pb.h>
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace storageinsights_v1_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

StorageInsightsAuth::StorageInsightsAuth(
    std::shared_ptr<google::cloud::internal::GrpcAuthenticationStrategy> auth,
    std::shared_ptr<StorageInsightsStub> child)
    : auth_(std::move(auth)), child_(std::move(child)) {}

StatusOr<google::cloud::storageinsights::v1::ListReportConfigsResponse>
StorageInsightsAuth::ListReportConfigs(
    grpc::ClientContext& context, Options const& options,
    google::cloud::storageinsights::v1::ListReportConfigsRequest const&
        request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->ListReportConfigs(context, options, request);
}

StatusOr<google::cloud::storageinsights::v1::ReportConfig>
StorageInsightsAuth::GetReportConfig(
    grpc::ClientContext& context, Options const& options,
    google::cloud::storageinsights::v1::GetReportConfigRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->GetReportConfig(context, options, request);
}

StatusOr<google::cloud::storageinsights::v1::ReportConfig>
StorageInsightsAuth::CreateReportConfig(
    grpc::ClientContext& context, Options const& options,
    google::cloud::storageinsights::v1::CreateReportConfigRequest const&
        request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->CreateReportConfig(context, options, request);
}

StatusOr<google::cloud::storageinsights::v1::ReportConfig>
StorageInsightsAuth::UpdateReportConfig(
    grpc::ClientContext& context, Options const& options,
    google::cloud::storageinsights::v1::UpdateReportConfigRequest const&
        request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->UpdateReportConfig(context, options, request);
}

Status StorageInsightsAuth::DeleteReportConfig(
    grpc::ClientContext& context, Options const& options,
    google::cloud::storageinsights::v1::DeleteReportConfigRequest const&
        request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->DeleteReportConfig(context, options, request);
}

StatusOr<google::cloud::storageinsights::v1::ListReportDetailsResponse>
StorageInsightsAuth::ListReportDetails(
    grpc::ClientContext& context, Options const& options,
    google::cloud::storageinsights::v1::ListReportDetailsRequest const&
        request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->ListReportDetails(context, options, request);
}

StatusOr<google::cloud::storageinsights::v1::ReportDetail>
StorageInsightsAuth::GetReportDetail(
    grpc::ClientContext& context, Options const& options,
    google::cloud::storageinsights::v1::GetReportDetailRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->GetReportDetail(context, options, request);
}

StatusOr<google::cloud::storageinsights::v1::ListDatasetConfigsResponse>
StorageInsightsAuth::ListDatasetConfigs(
    grpc::ClientContext& context, Options const& options,
    google::cloud::storageinsights::v1::ListDatasetConfigsRequest const&
        request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->ListDatasetConfigs(context, options, request);
}

StatusOr<google::cloud::storageinsights::v1::DatasetConfig>
StorageInsightsAuth::GetDatasetConfig(
    grpc::ClientContext& context, Options const& options,
    google::cloud::storageinsights::v1::GetDatasetConfigRequest const&
        request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->GetDatasetConfig(context, options, request);
}

future<StatusOr<google::longrunning::Operation>>
StorageInsightsAuth::AsyncCreateDatasetConfig(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::cloud::storageinsights::v1::CreateDatasetConfigRequest const&
        request) {
  using ReturnType = StatusOr<google::longrunning::Operation>;
  return auth_->AsyncConfigureContext(std::move(context))
      .then([cq, child = child_, options = std::move(options),
             request](future<StatusOr<std::shared_ptr<grpc::ClientContext>>>
                          f) mutable {
        auto context = f.get();
        if (!context) {
          return make_ready_future(ReturnType(std::move(context).status()));
        }
        return child->AsyncCreateDatasetConfig(cq, *std::move(context),
                                               std::move(options), request);
      });
}

StatusOr<google::longrunning::Operation>
StorageInsightsAuth::CreateDatasetConfig(
    grpc::ClientContext& context, Options options,
    google::cloud::storageinsights::v1::CreateDatasetConfigRequest const&
        request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->CreateDatasetConfig(context, options, request);
}

future<StatusOr<google::longrunning::Operation>>
StorageInsightsAuth::AsyncUpdateDatasetConfig(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::cloud::storageinsights::v1::UpdateDatasetConfigRequest const&
        request) {
  using ReturnType = StatusOr<google::longrunning::Operation>;
  return auth_->AsyncConfigureContext(std::move(context))
      .then([cq, child = child_, options = std::move(options),
             request](future<StatusOr<std::shared_ptr<grpc::ClientContext>>>
                          f) mutable {
        auto context = f.get();
        if (!context) {
          return make_ready_future(ReturnType(std::move(context).status()));
        }
        return child->AsyncUpdateDatasetConfig(cq, *std::move(context),
                                               std::move(options), request);
      });
}

StatusOr<google::longrunning::Operation>
StorageInsightsAuth::UpdateDatasetConfig(
    grpc::ClientContext& context, Options options,
    google::cloud::storageinsights::v1::UpdateDatasetConfigRequest const&
        request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->UpdateDatasetConfig(context, options, request);
}

future<StatusOr<google::longrunning::Operation>>
StorageInsightsAuth::AsyncDeleteDatasetConfig(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::cloud::storageinsights::v1::DeleteDatasetConfigRequest const&
        request) {
  using ReturnType = StatusOr<google::longrunning::Operation>;
  return auth_->AsyncConfigureContext(std::move(context))
      .then([cq, child = child_, options = std::move(options),
             request](future<StatusOr<std::shared_ptr<grpc::ClientContext>>>
                          f) mutable {
        auto context = f.get();
        if (!context) {
          return make_ready_future(ReturnType(std::move(context).status()));
        }
        return child->AsyncDeleteDatasetConfig(cq, *std::move(context),
                                               std::move(options), request);
      });
}

StatusOr<google::longrunning::Operation>
StorageInsightsAuth::DeleteDatasetConfig(
    grpc::ClientContext& context, Options options,
    google::cloud::storageinsights::v1::DeleteDatasetConfigRequest const&
        request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->DeleteDatasetConfig(context, options, request);
}

future<StatusOr<google::longrunning::Operation>>
StorageInsightsAuth::AsyncLinkDataset(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::cloud::storageinsights::v1::LinkDatasetRequest const& request) {
  using ReturnType = StatusOr<google::longrunning::Operation>;
  return auth_->AsyncConfigureContext(std::move(context))
      .then([cq, child = child_, options = std::move(options),
             request](future<StatusOr<std::shared_ptr<grpc::ClientContext>>>
                          f) mutable {
        auto context = f.get();
        if (!context) {
          return make_ready_future(ReturnType(std::move(context).status()));
        }
        return child->AsyncLinkDataset(cq, *std::move(context),
                                       std::move(options), request);
      });
}

StatusOr<google::longrunning::Operation> StorageInsightsAuth::LinkDataset(
    grpc::ClientContext& context, Options options,
    google::cloud::storageinsights::v1::LinkDatasetRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->LinkDataset(context, options, request);
}

future<StatusOr<google::longrunning::Operation>>
StorageInsightsAuth::AsyncUnlinkDataset(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::cloud::storageinsights::v1::UnlinkDatasetRequest const& request) {
  using ReturnType = StatusOr<google::longrunning::Operation>;
  return auth_->AsyncConfigureContext(std::move(context))
      .then([cq, child = child_, options = std::move(options),
             request](future<StatusOr<std::shared_ptr<grpc::ClientContext>>>
                          f) mutable {
        auto context = f.get();
        if (!context) {
          return make_ready_future(ReturnType(std::move(context).status()));
        }
        return child->AsyncUnlinkDataset(cq, *std::move(context),
                                         std::move(options), request);
      });
}

StatusOr<google::longrunning::Operation> StorageInsightsAuth::UnlinkDataset(
    grpc::ClientContext& context, Options options,
    google::cloud::storageinsights::v1::UnlinkDatasetRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->UnlinkDataset(context, options, request);
}

StatusOr<google::cloud::location::ListLocationsResponse>
StorageInsightsAuth::ListLocations(
    grpc::ClientContext& context, Options const& options,
    google::cloud::location::ListLocationsRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->ListLocations(context, options, request);
}

StatusOr<google::cloud::location::Location> StorageInsightsAuth::GetLocation(
    grpc::ClientContext& context, Options const& options,
    google::cloud::location::GetLocationRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->GetLocation(context, options, request);
}

StatusOr<google::longrunning::ListOperationsResponse>
StorageInsightsAuth::ListOperations(
    grpc::ClientContext& context, Options const& options,
    google::longrunning::ListOperationsRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->ListOperations(context, options, request);
}

StatusOr<google::longrunning::Operation> StorageInsightsAuth::GetOperation(
    grpc::ClientContext& context, Options const& options,
    google::longrunning::GetOperationRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->GetOperation(context, options, request);
}

Status StorageInsightsAuth::DeleteOperation(
    grpc::ClientContext& context, Options const& options,
    google::longrunning::DeleteOperationRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->DeleteOperation(context, options, request);
}

Status StorageInsightsAuth::CancelOperation(
    grpc::ClientContext& context, Options const& options,
    google::longrunning::CancelOperationRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->CancelOperation(context, options, request);
}

future<StatusOr<google::longrunning::Operation>>
StorageInsightsAuth::AsyncGetOperation(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::longrunning::GetOperationRequest const& request) {
  using ReturnType = StatusOr<google::longrunning::Operation>;
  return auth_->AsyncConfigureContext(std::move(context))
      .then([cq, child = child_, options = std::move(options),
             request](future<StatusOr<std::shared_ptr<grpc::ClientContext>>>
                          f) mutable {
        auto context = f.get();
        if (!context) {
          return make_ready_future(ReturnType(std::move(context).status()));
        }
        return child->AsyncGetOperation(cq, *std::move(context),
                                        std::move(options), request);
      });
}

future<Status> StorageInsightsAuth::AsyncCancelOperation(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::longrunning::CancelOperationRequest const& request) {
  return auth_->AsyncConfigureContext(std::move(context))
      .then([cq, child = child_, options = std::move(options),
             request](future<StatusOr<std::shared_ptr<grpc::ClientContext>>>
                          f) mutable {
        auto context = f.get();
        if (!context) return make_ready_future(std::move(context).status());
        return child->AsyncCancelOperation(cq, *std::move(context),
                                           std::move(options), request);
      });
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace storageinsights_v1_internal
}  // namespace cloud
}  // namespace google
