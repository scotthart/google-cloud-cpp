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
// source: google/container/v1/cluster_service.proto

#include "google/cloud/container/v1/internal/cluster_manager_connection_impl.h"
#include "google/cloud/container/v1/internal/cluster_manager_option_defaults.h"
#include "google/cloud/background_threads.h"
#include "google/cloud/common_options.h"
#include "google/cloud/grpc_options.h"
#include "google/cloud/internal/pagination_range.h"
#include "google/cloud/internal/retry_loop.h"
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace container_v1_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN
namespace {

std::unique_ptr<container_v1::ClusterManagerRetryPolicy> retry_policy(
    Options const& options) {
  return options.get<container_v1::ClusterManagerRetryPolicyOption>()->clone();
}

std::unique_ptr<BackoffPolicy> backoff_policy(Options const& options) {
  return options.get<container_v1::ClusterManagerBackoffPolicyOption>()
      ->clone();
}

std::unique_ptr<container_v1::ClusterManagerConnectionIdempotencyPolicy>
idempotency_policy(Options const& options) {
  return options
      .get<container_v1::ClusterManagerConnectionIdempotencyPolicyOption>()
      ->clone();
}

}  // namespace

ClusterManagerConnectionImpl::ClusterManagerConnectionImpl(
    std::unique_ptr<google::cloud::BackgroundThreads> background,
    std::shared_ptr<container_v1_internal::ClusterManagerStub> stub,
    Options options)
    : background_(std::move(background)),
      stub_(std::move(stub)),
      options_(internal::MergeOptions(std::move(options),
                                      ClusterManagerConnection::options())) {}

StatusOr<google::container::v1::ListClustersResponse>
ClusterManagerConnectionImpl::ListClusters(
    google::container::v1::ListClustersRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->ListClusters(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::ListClustersRequest const& request) {
        return stub_->ListClusters(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::Cluster>
ClusterManagerConnectionImpl::GetCluster(
    google::container::v1::GetClusterRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->GetCluster(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::GetClusterRequest const& request) {
        return stub_->GetCluster(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::Operation>
ClusterManagerConnectionImpl::CreateCluster(
    google::container::v1::CreateClusterRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->CreateCluster(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::CreateClusterRequest const& request) {
        return stub_->CreateCluster(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::Operation>
ClusterManagerConnectionImpl::UpdateCluster(
    google::container::v1::UpdateClusterRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->UpdateCluster(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::UpdateClusterRequest const& request) {
        return stub_->UpdateCluster(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::Operation>
ClusterManagerConnectionImpl::UpdateNodePool(
    google::container::v1::UpdateNodePoolRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->UpdateNodePool(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::UpdateNodePoolRequest const& request) {
        return stub_->UpdateNodePool(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::Operation>
ClusterManagerConnectionImpl::SetNodePoolAutoscaling(
    google::container::v1::SetNodePoolAutoscalingRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->SetNodePoolAutoscaling(request),
      [this](
          grpc::ClientContext& context, Options const& options,
          google::container::v1::SetNodePoolAutoscalingRequest const& request) {
        return stub_->SetNodePoolAutoscaling(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::Operation>
ClusterManagerConnectionImpl::SetLoggingService(
    google::container::v1::SetLoggingServiceRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->SetLoggingService(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::SetLoggingServiceRequest const& request) {
        return stub_->SetLoggingService(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::Operation>
ClusterManagerConnectionImpl::SetMonitoringService(
    google::container::v1::SetMonitoringServiceRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->SetMonitoringService(request),
      [this](
          grpc::ClientContext& context, Options const& options,
          google::container::v1::SetMonitoringServiceRequest const& request) {
        return stub_->SetMonitoringService(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::Operation>
ClusterManagerConnectionImpl::SetAddonsConfig(
    google::container::v1::SetAddonsConfigRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->SetAddonsConfig(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::SetAddonsConfigRequest const& request) {
        return stub_->SetAddonsConfig(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::Operation>
ClusterManagerConnectionImpl::SetLocations(
    google::container::v1::SetLocationsRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->SetLocations(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::SetLocationsRequest const& request) {
        return stub_->SetLocations(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::Operation>
ClusterManagerConnectionImpl::UpdateMaster(
    google::container::v1::UpdateMasterRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->UpdateMaster(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::UpdateMasterRequest const& request) {
        return stub_->UpdateMaster(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::Operation>
ClusterManagerConnectionImpl::SetMasterAuth(
    google::container::v1::SetMasterAuthRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->SetMasterAuth(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::SetMasterAuthRequest const& request) {
        return stub_->SetMasterAuth(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::Operation>
ClusterManagerConnectionImpl::DeleteCluster(
    google::container::v1::DeleteClusterRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->DeleteCluster(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::DeleteClusterRequest const& request) {
        return stub_->DeleteCluster(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::ListOperationsResponse>
ClusterManagerConnectionImpl::ListOperations(
    google::container::v1::ListOperationsRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->ListOperations(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::ListOperationsRequest const& request) {
        return stub_->ListOperations(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::Operation>
ClusterManagerConnectionImpl::GetOperation(
    google::container::v1::GetOperationRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->GetOperation(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::GetOperationRequest const& request) {
        return stub_->GetOperation(context, options, request);
      },
      *current, request, __func__);
}

Status ClusterManagerConnectionImpl::CancelOperation(
    google::container::v1::CancelOperationRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->CancelOperation(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::CancelOperationRequest const& request) {
        return stub_->CancelOperation(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::ServerConfig>
ClusterManagerConnectionImpl::GetServerConfig(
    google::container::v1::GetServerConfigRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->GetServerConfig(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::GetServerConfigRequest const& request) {
        return stub_->GetServerConfig(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::GetJSONWebKeysResponse>
ClusterManagerConnectionImpl::GetJSONWebKeys(
    google::container::v1::GetJSONWebKeysRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->GetJSONWebKeys(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::GetJSONWebKeysRequest const& request) {
        return stub_->GetJSONWebKeys(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::ListNodePoolsResponse>
ClusterManagerConnectionImpl::ListNodePools(
    google::container::v1::ListNodePoolsRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->ListNodePools(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::ListNodePoolsRequest const& request) {
        return stub_->ListNodePools(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::NodePool>
ClusterManagerConnectionImpl::GetNodePool(
    google::container::v1::GetNodePoolRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->GetNodePool(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::GetNodePoolRequest const& request) {
        return stub_->GetNodePool(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::Operation>
ClusterManagerConnectionImpl::CreateNodePool(
    google::container::v1::CreateNodePoolRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->CreateNodePool(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::CreateNodePoolRequest const& request) {
        return stub_->CreateNodePool(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::Operation>
ClusterManagerConnectionImpl::DeleteNodePool(
    google::container::v1::DeleteNodePoolRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->DeleteNodePool(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::DeleteNodePoolRequest const& request) {
        return stub_->DeleteNodePool(context, options, request);
      },
      *current, request, __func__);
}

Status ClusterManagerConnectionImpl::CompleteNodePoolUpgrade(
    google::container::v1::CompleteNodePoolUpgradeRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->CompleteNodePoolUpgrade(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::CompleteNodePoolUpgradeRequest const&
                 request) {
        return stub_->CompleteNodePoolUpgrade(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::Operation>
ClusterManagerConnectionImpl::RollbackNodePoolUpgrade(
    google::container::v1::RollbackNodePoolUpgradeRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->RollbackNodePoolUpgrade(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::RollbackNodePoolUpgradeRequest const&
                 request) {
        return stub_->RollbackNodePoolUpgrade(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::Operation>
ClusterManagerConnectionImpl::SetNodePoolManagement(
    google::container::v1::SetNodePoolManagementRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->SetNodePoolManagement(request),
      [this](
          grpc::ClientContext& context, Options const& options,
          google::container::v1::SetNodePoolManagementRequest const& request) {
        return stub_->SetNodePoolManagement(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::Operation>
ClusterManagerConnectionImpl::SetLabels(
    google::container::v1::SetLabelsRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->SetLabels(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::SetLabelsRequest const& request) {
        return stub_->SetLabels(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::Operation>
ClusterManagerConnectionImpl::SetLegacyAbac(
    google::container::v1::SetLegacyAbacRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->SetLegacyAbac(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::SetLegacyAbacRequest const& request) {
        return stub_->SetLegacyAbac(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::Operation>
ClusterManagerConnectionImpl::StartIPRotation(
    google::container::v1::StartIPRotationRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->StartIPRotation(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::StartIPRotationRequest const& request) {
        return stub_->StartIPRotation(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::Operation>
ClusterManagerConnectionImpl::CompleteIPRotation(
    google::container::v1::CompleteIPRotationRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->CompleteIPRotation(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::CompleteIPRotationRequest const& request) {
        return stub_->CompleteIPRotation(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::Operation>
ClusterManagerConnectionImpl::SetNodePoolSize(
    google::container::v1::SetNodePoolSizeRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->SetNodePoolSize(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::SetNodePoolSizeRequest const& request) {
        return stub_->SetNodePoolSize(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::Operation>
ClusterManagerConnectionImpl::SetNetworkPolicy(
    google::container::v1::SetNetworkPolicyRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->SetNetworkPolicy(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::SetNetworkPolicyRequest const& request) {
        return stub_->SetNetworkPolicy(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::Operation>
ClusterManagerConnectionImpl::SetMaintenancePolicy(
    google::container::v1::SetMaintenancePolicyRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->SetMaintenancePolicy(request),
      [this](
          grpc::ClientContext& context, Options const& options,
          google::container::v1::SetMaintenancePolicyRequest const& request) {
        return stub_->SetMaintenancePolicy(context, options, request);
      },
      *current, request, __func__);
}

StreamRange<google::container::v1::UsableSubnetwork>
ClusterManagerConnectionImpl::ListUsableSubnetworks(
    google::container::v1::ListUsableSubnetworksRequest request) {
  request.clear_page_token();
  auto current = google::cloud::internal::SaveCurrentOptions();
  auto idempotency =
      idempotency_policy(*current)->ListUsableSubnetworks(request);
  char const* function_name = __func__;
  return google::cloud::internal::MakePaginationRange<
      StreamRange<google::container::v1::UsableSubnetwork>>(
      current, std::move(request),
      [idempotency, function_name, stub = stub_,
       retry = std::shared_ptr<container_v1::ClusterManagerRetryPolicy>(
           retry_policy(*current)),
       backoff = std::shared_ptr<BackoffPolicy>(backoff_policy(*current))](
          Options const& options,
          google::container::v1::ListUsableSubnetworksRequest const& r) {
        return google::cloud::internal::RetryLoop(
            retry->clone(), backoff->clone(), idempotency,
            [stub](grpc::ClientContext& context, Options const& options,
                   google::container::v1::ListUsableSubnetworksRequest const&
                       request) {
              return stub->ListUsableSubnetworks(context, options, request);
            },
            options, r, function_name);
      },
      [](google::container::v1::ListUsableSubnetworksResponse r) {
        std::vector<google::container::v1::UsableSubnetwork> result(
            r.subnetworks().size());
        auto& messages = *r.mutable_subnetworks();
        std::move(messages.begin(), messages.end(), result.begin());
        return result;
      });
}

StatusOr<google::container::v1::CheckAutopilotCompatibilityResponse>
ClusterManagerConnectionImpl::CheckAutopilotCompatibility(
    google::container::v1::CheckAutopilotCompatibilityRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->CheckAutopilotCompatibility(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::CheckAutopilotCompatibilityRequest const&
                 request) {
        return stub_->CheckAutopilotCompatibility(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::ClusterUpgradeInfo>
ClusterManagerConnectionImpl::FetchClusterUpgradeInfo(
    google::container::v1::FetchClusterUpgradeInfoRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->FetchClusterUpgradeInfo(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::FetchClusterUpgradeInfoRequest const&
                 request) {
        return stub_->FetchClusterUpgradeInfo(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::container::v1::NodePoolUpgradeInfo>
ClusterManagerConnectionImpl::FetchNodePoolUpgradeInfo(
    google::container::v1::FetchNodePoolUpgradeInfoRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->FetchNodePoolUpgradeInfo(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::container::v1::FetchNodePoolUpgradeInfoRequest const&
                 request) {
        return stub_->FetchNodePoolUpgradeInfo(context, options, request);
      },
      *current, request, __func__);
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace container_v1_internal
}  // namespace cloud
}  // namespace google
