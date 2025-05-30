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

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_CONTAINER_V1_MOCKS_MOCK_CLUSTER_MANAGER_CONNECTION_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_CONTAINER_V1_MOCKS_MOCK_CLUSTER_MANAGER_CONNECTION_H

#include "google/cloud/container/v1/cluster_manager_connection.h"
#include <gmock/gmock.h>

namespace google {
namespace cloud {
namespace container_v1_mocks {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

/**
 * A class to mock `ClusterManagerConnection`.
 *
 * Application developers may want to test their code with simulated responses,
 * including errors, from an object of type `ClusterManagerClient`. To do so,
 * construct an object of type `ClusterManagerClient` with an instance of this
 * class. Then use the Google Test framework functions to program the behavior
 * of this mock.
 *
 * @see [This example][bq-mock] for how to test your application with GoogleTest.
 * While the example showcases types from the BigQuery library, the underlying
 * principles apply for any pair of `*Client` and `*Connection`.
 *
 * [bq-mock]: @cloud_cpp_docs_link{bigquery,bigquery-read-mock}
 */
class MockClusterManagerConnection
    : public container_v1::ClusterManagerConnection {
 public:
  MOCK_METHOD(Options, options, (), (override));

  MOCK_METHOD(StatusOr<google::container::v1::ListClustersResponse>,
              ListClusters,
              (google::container::v1::ListClustersRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::container::v1::Cluster>, GetCluster,
              (google::container::v1::GetClusterRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::container::v1::Operation>, CreateCluster,
              (google::container::v1::CreateClusterRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::container::v1::Operation>, UpdateCluster,
              (google::container::v1::UpdateClusterRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::container::v1::Operation>, UpdateNodePool,
              (google::container::v1::UpdateNodePoolRequest const& request),
              (override));

  MOCK_METHOD(
      StatusOr<google::container::v1::Operation>, SetNodePoolAutoscaling,
      (google::container::v1::SetNodePoolAutoscalingRequest const& request),
      (override));

  MOCK_METHOD(StatusOr<google::container::v1::Operation>, SetLoggingService,
              (google::container::v1::SetLoggingServiceRequest const& request),
              (override));

  MOCK_METHOD(
      StatusOr<google::container::v1::Operation>, SetMonitoringService,
      (google::container::v1::SetMonitoringServiceRequest const& request),
      (override));

  MOCK_METHOD(StatusOr<google::container::v1::Operation>, SetAddonsConfig,
              (google::container::v1::SetAddonsConfigRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::container::v1::Operation>, SetLocations,
              (google::container::v1::SetLocationsRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::container::v1::Operation>, UpdateMaster,
              (google::container::v1::UpdateMasterRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::container::v1::Operation>, SetMasterAuth,
              (google::container::v1::SetMasterAuthRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::container::v1::Operation>, DeleteCluster,
              (google::container::v1::DeleteClusterRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::container::v1::ListOperationsResponse>,
              ListOperations,
              (google::container::v1::ListOperationsRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::container::v1::Operation>, GetOperation,
              (google::container::v1::GetOperationRequest const& request),
              (override));

  MOCK_METHOD(Status, CancelOperation,
              (google::container::v1::CancelOperationRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::container::v1::ServerConfig>, GetServerConfig,
              (google::container::v1::GetServerConfigRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::container::v1::GetJSONWebKeysResponse>,
              GetJSONWebKeys,
              (google::container::v1::GetJSONWebKeysRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::container::v1::ListNodePoolsResponse>,
              ListNodePools,
              (google::container::v1::ListNodePoolsRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::container::v1::NodePool>, GetNodePool,
              (google::container::v1::GetNodePoolRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::container::v1::Operation>, CreateNodePool,
              (google::container::v1::CreateNodePoolRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::container::v1::Operation>, DeleteNodePool,
              (google::container::v1::DeleteNodePoolRequest const& request),
              (override));

  MOCK_METHOD(
      Status, CompleteNodePoolUpgrade,
      (google::container::v1::CompleteNodePoolUpgradeRequest const& request),
      (override));

  MOCK_METHOD(
      StatusOr<google::container::v1::Operation>, RollbackNodePoolUpgrade,
      (google::container::v1::RollbackNodePoolUpgradeRequest const& request),
      (override));

  MOCK_METHOD(
      StatusOr<google::container::v1::Operation>, SetNodePoolManagement,
      (google::container::v1::SetNodePoolManagementRequest const& request),
      (override));

  MOCK_METHOD(StatusOr<google::container::v1::Operation>, SetLabels,
              (google::container::v1::SetLabelsRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::container::v1::Operation>, SetLegacyAbac,
              (google::container::v1::SetLegacyAbacRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::container::v1::Operation>, StartIPRotation,
              (google::container::v1::StartIPRotationRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::container::v1::Operation>, CompleteIPRotation,
              (google::container::v1::CompleteIPRotationRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::container::v1::Operation>, SetNodePoolSize,
              (google::container::v1::SetNodePoolSizeRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::container::v1::Operation>, SetNetworkPolicy,
              (google::container::v1::SetNetworkPolicyRequest const& request),
              (override));

  MOCK_METHOD(
      StatusOr<google::container::v1::Operation>, SetMaintenancePolicy,
      (google::container::v1::SetMaintenancePolicyRequest const& request),
      (override));

  MOCK_METHOD((StreamRange<google::container::v1::UsableSubnetwork>),
              ListUsableSubnetworks,
              (google::container::v1::ListUsableSubnetworksRequest request),
              (override));

  MOCK_METHOD(
      StatusOr<google::container::v1::CheckAutopilotCompatibilityResponse>,
      CheckAutopilotCompatibility,
      (google::container::v1::CheckAutopilotCompatibilityRequest const&
           request),
      (override));

  MOCK_METHOD(
      StatusOr<google::container::v1::ClusterUpgradeInfo>,
      FetchClusterUpgradeInfo,
      (google::container::v1::FetchClusterUpgradeInfoRequest const& request),
      (override));

  MOCK_METHOD(
      StatusOr<google::container::v1::NodePoolUpgradeInfo>,
      FetchNodePoolUpgradeInfo,
      (google::container::v1::FetchNodePoolUpgradeInfoRequest const& request),
      (override));
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace container_v1_mocks
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_CONTAINER_V1_MOCKS_MOCK_CLUSTER_MANAGER_CONNECTION_H
