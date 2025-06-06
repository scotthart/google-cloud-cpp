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

#include "google/cloud/container/v1/internal/cluster_manager_tracing_connection.h"
#include "google/cloud/internal/opentelemetry.h"
#include "google/cloud/internal/traced_stream_range.h"
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace container_v1_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

#ifdef GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY

ClusterManagerTracingConnection::ClusterManagerTracingConnection(
    std::shared_ptr<container_v1::ClusterManagerConnection> child)
    : child_(std::move(child)) {}

StatusOr<google::container::v1::ListClustersResponse>
ClusterManagerTracingConnection::ListClusters(
    google::container::v1::ListClustersRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::ListClusters");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->ListClusters(request));
}

StatusOr<google::container::v1::Cluster>
ClusterManagerTracingConnection::GetCluster(
    google::container::v1::GetClusterRequest const& request) {
  auto span =
      internal::MakeSpan("container_v1::ClusterManagerConnection::GetCluster");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->GetCluster(request));
}

StatusOr<google::container::v1::Operation>
ClusterManagerTracingConnection::CreateCluster(
    google::container::v1::CreateClusterRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::CreateCluster");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->CreateCluster(request));
}

StatusOr<google::container::v1::Operation>
ClusterManagerTracingConnection::UpdateCluster(
    google::container::v1::UpdateClusterRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::UpdateCluster");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->UpdateCluster(request));
}

StatusOr<google::container::v1::Operation>
ClusterManagerTracingConnection::UpdateNodePool(
    google::container::v1::UpdateNodePoolRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::UpdateNodePool");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->UpdateNodePool(request));
}

StatusOr<google::container::v1::Operation>
ClusterManagerTracingConnection::SetNodePoolAutoscaling(
    google::container::v1::SetNodePoolAutoscalingRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::SetNodePoolAutoscaling");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->SetNodePoolAutoscaling(request));
}

StatusOr<google::container::v1::Operation>
ClusterManagerTracingConnection::SetLoggingService(
    google::container::v1::SetLoggingServiceRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::SetLoggingService");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->SetLoggingService(request));
}

StatusOr<google::container::v1::Operation>
ClusterManagerTracingConnection::SetMonitoringService(
    google::container::v1::SetMonitoringServiceRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::SetMonitoringService");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->SetMonitoringService(request));
}

StatusOr<google::container::v1::Operation>
ClusterManagerTracingConnection::SetAddonsConfig(
    google::container::v1::SetAddonsConfigRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::SetAddonsConfig");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->SetAddonsConfig(request));
}

StatusOr<google::container::v1::Operation>
ClusterManagerTracingConnection::SetLocations(
    google::container::v1::SetLocationsRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::SetLocations");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->SetLocations(request));
}

StatusOr<google::container::v1::Operation>
ClusterManagerTracingConnection::UpdateMaster(
    google::container::v1::UpdateMasterRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::UpdateMaster");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->UpdateMaster(request));
}

StatusOr<google::container::v1::Operation>
ClusterManagerTracingConnection::SetMasterAuth(
    google::container::v1::SetMasterAuthRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::SetMasterAuth");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->SetMasterAuth(request));
}

StatusOr<google::container::v1::Operation>
ClusterManagerTracingConnection::DeleteCluster(
    google::container::v1::DeleteClusterRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::DeleteCluster");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->DeleteCluster(request));
}

StatusOr<google::container::v1::ListOperationsResponse>
ClusterManagerTracingConnection::ListOperations(
    google::container::v1::ListOperationsRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::ListOperations");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->ListOperations(request));
}

StatusOr<google::container::v1::Operation>
ClusterManagerTracingConnection::GetOperation(
    google::container::v1::GetOperationRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::GetOperation");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->GetOperation(request));
}

Status ClusterManagerTracingConnection::CancelOperation(
    google::container::v1::CancelOperationRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::CancelOperation");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->CancelOperation(request));
}

StatusOr<google::container::v1::ServerConfig>
ClusterManagerTracingConnection::GetServerConfig(
    google::container::v1::GetServerConfigRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::GetServerConfig");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->GetServerConfig(request));
}

StatusOr<google::container::v1::GetJSONWebKeysResponse>
ClusterManagerTracingConnection::GetJSONWebKeys(
    google::container::v1::GetJSONWebKeysRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::GetJSONWebKeys");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->GetJSONWebKeys(request));
}

StatusOr<google::container::v1::ListNodePoolsResponse>
ClusterManagerTracingConnection::ListNodePools(
    google::container::v1::ListNodePoolsRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::ListNodePools");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->ListNodePools(request));
}

StatusOr<google::container::v1::NodePool>
ClusterManagerTracingConnection::GetNodePool(
    google::container::v1::GetNodePoolRequest const& request) {
  auto span =
      internal::MakeSpan("container_v1::ClusterManagerConnection::GetNodePool");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->GetNodePool(request));
}

StatusOr<google::container::v1::Operation>
ClusterManagerTracingConnection::CreateNodePool(
    google::container::v1::CreateNodePoolRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::CreateNodePool");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->CreateNodePool(request));
}

StatusOr<google::container::v1::Operation>
ClusterManagerTracingConnection::DeleteNodePool(
    google::container::v1::DeleteNodePoolRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::DeleteNodePool");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->DeleteNodePool(request));
}

Status ClusterManagerTracingConnection::CompleteNodePoolUpgrade(
    google::container::v1::CompleteNodePoolUpgradeRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::CompleteNodePoolUpgrade");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->CompleteNodePoolUpgrade(request));
}

StatusOr<google::container::v1::Operation>
ClusterManagerTracingConnection::RollbackNodePoolUpgrade(
    google::container::v1::RollbackNodePoolUpgradeRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::RollbackNodePoolUpgrade");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->RollbackNodePoolUpgrade(request));
}

StatusOr<google::container::v1::Operation>
ClusterManagerTracingConnection::SetNodePoolManagement(
    google::container::v1::SetNodePoolManagementRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::SetNodePoolManagement");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->SetNodePoolManagement(request));
}

StatusOr<google::container::v1::Operation>
ClusterManagerTracingConnection::SetLabels(
    google::container::v1::SetLabelsRequest const& request) {
  auto span =
      internal::MakeSpan("container_v1::ClusterManagerConnection::SetLabels");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->SetLabels(request));
}

StatusOr<google::container::v1::Operation>
ClusterManagerTracingConnection::SetLegacyAbac(
    google::container::v1::SetLegacyAbacRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::SetLegacyAbac");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->SetLegacyAbac(request));
}

StatusOr<google::container::v1::Operation>
ClusterManagerTracingConnection::StartIPRotation(
    google::container::v1::StartIPRotationRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::StartIPRotation");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->StartIPRotation(request));
}

StatusOr<google::container::v1::Operation>
ClusterManagerTracingConnection::CompleteIPRotation(
    google::container::v1::CompleteIPRotationRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::CompleteIPRotation");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->CompleteIPRotation(request));
}

StatusOr<google::container::v1::Operation>
ClusterManagerTracingConnection::SetNodePoolSize(
    google::container::v1::SetNodePoolSizeRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::SetNodePoolSize");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->SetNodePoolSize(request));
}

StatusOr<google::container::v1::Operation>
ClusterManagerTracingConnection::SetNetworkPolicy(
    google::container::v1::SetNetworkPolicyRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::SetNetworkPolicy");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->SetNetworkPolicy(request));
}

StatusOr<google::container::v1::Operation>
ClusterManagerTracingConnection::SetMaintenancePolicy(
    google::container::v1::SetMaintenancePolicyRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::SetMaintenancePolicy");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->SetMaintenancePolicy(request));
}

StreamRange<google::container::v1::UsableSubnetwork>
ClusterManagerTracingConnection::ListUsableSubnetworks(
    google::container::v1::ListUsableSubnetworksRequest request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::ListUsableSubnetworks");
  internal::OTelScope scope(span);
  auto sr = child_->ListUsableSubnetworks(std::move(request));
  return internal::MakeTracedStreamRange<
      google::container::v1::UsableSubnetwork>(std::move(span), std::move(sr));
}

StatusOr<google::container::v1::CheckAutopilotCompatibilityResponse>
ClusterManagerTracingConnection::CheckAutopilotCompatibility(
    google::container::v1::CheckAutopilotCompatibilityRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::CheckAutopilotCompatibility");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->CheckAutopilotCompatibility(request));
}

StatusOr<google::container::v1::ClusterUpgradeInfo>
ClusterManagerTracingConnection::FetchClusterUpgradeInfo(
    google::container::v1::FetchClusterUpgradeInfoRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::FetchClusterUpgradeInfo");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->FetchClusterUpgradeInfo(request));
}

StatusOr<google::container::v1::NodePoolUpgradeInfo>
ClusterManagerTracingConnection::FetchNodePoolUpgradeInfo(
    google::container::v1::FetchNodePoolUpgradeInfoRequest const& request) {
  auto span = internal::MakeSpan(
      "container_v1::ClusterManagerConnection::FetchNodePoolUpgradeInfo");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->FetchNodePoolUpgradeInfo(request));
}

#endif  // GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY

std::shared_ptr<container_v1::ClusterManagerConnection>
MakeClusterManagerTracingConnection(
    std::shared_ptr<container_v1::ClusterManagerConnection> conn) {
#ifdef GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY
  if (internal::TracingEnabled(conn->options())) {
    conn = std::make_shared<ClusterManagerTracingConnection>(std::move(conn));
  }
#endif  // GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY
  return conn;
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace container_v1_internal
}  // namespace cloud
}  // namespace google
