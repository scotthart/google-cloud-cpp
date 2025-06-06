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

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_CONTAINER_V1_CLUSTER_MANAGER_CONNECTION_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_CONTAINER_V1_CLUSTER_MANAGER_CONNECTION_H

#include "google/cloud/container/v1/cluster_manager_connection_idempotency_policy.h"
#include "google/cloud/container/v1/internal/cluster_manager_retry_traits.h"
#include "google/cloud/backoff_policy.h"
#include "google/cloud/internal/retry_policy_impl.h"
#include "google/cloud/options.h"
#include "google/cloud/status_or.h"
#include "google/cloud/stream_range.h"
#include "google/cloud/version.h"
#include <google/container/v1/cluster_service.pb.h>
#include <memory>

namespace google {
namespace cloud {
namespace container_v1 {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

/// The retry policy for `ClusterManagerConnection`.
class ClusterManagerRetryPolicy : public ::google::cloud::RetryPolicy {
 public:
  /// Creates a new instance of the policy, reset to the initial state.
  virtual std::unique_ptr<ClusterManagerRetryPolicy> clone() const = 0;
};

/**
 * A retry policy for `ClusterManagerConnection` based on counting errors.
 *
 * This policy stops retrying if:
 * - An RPC returns a non-transient error.
 * - More than a prescribed number of transient failures is detected.
 *
 * In this class the following status codes are treated as transient errors:
 * - [`kUnavailable`](@ref google::cloud::StatusCode)
 */
class ClusterManagerLimitedErrorCountRetryPolicy
    : public ClusterManagerRetryPolicy {
 public:
  /**
   * Create an instance that tolerates up to @p maximum_failures transient
   * errors.
   *
   * @note Disable the retry loop by providing an instance of this policy with
   *     @p maximum_failures == 0.
   */
  explicit ClusterManagerLimitedErrorCountRetryPolicy(int maximum_failures)
      : impl_(maximum_failures) {}

  ClusterManagerLimitedErrorCountRetryPolicy(
      ClusterManagerLimitedErrorCountRetryPolicy&& rhs) noexcept
      : ClusterManagerLimitedErrorCountRetryPolicy(rhs.maximum_failures()) {}
  ClusterManagerLimitedErrorCountRetryPolicy(
      ClusterManagerLimitedErrorCountRetryPolicy const& rhs) noexcept
      : ClusterManagerLimitedErrorCountRetryPolicy(rhs.maximum_failures()) {}

  int maximum_failures() const { return impl_.maximum_failures(); }

  bool OnFailure(Status const& status) override {
    return impl_.OnFailure(status);
  }
  bool IsExhausted() const override { return impl_.IsExhausted(); }
  bool IsPermanentFailure(Status const& status) const override {
    return impl_.IsPermanentFailure(status);
  }
  std::unique_ptr<ClusterManagerRetryPolicy> clone() const override {
    return std::make_unique<ClusterManagerLimitedErrorCountRetryPolicy>(
        maximum_failures());
  }

  // This is provided only for backwards compatibility.
  using BaseType = ClusterManagerRetryPolicy;

 private:
  google::cloud::internal::LimitedErrorCountRetryPolicy<
      container_v1_internal::ClusterManagerRetryTraits>
      impl_;
};

/**
 * A retry policy for `ClusterManagerConnection` based on elapsed time.
 *
 * This policy stops retrying if:
 * - An RPC returns a non-transient error.
 * - The elapsed time in the retry loop exceeds a prescribed duration.
 *
 * In this class the following status codes are treated as transient errors:
 * - [`kUnavailable`](@ref google::cloud::StatusCode)
 */
class ClusterManagerLimitedTimeRetryPolicy : public ClusterManagerRetryPolicy {
 public:
  /**
   * Constructor given a `std::chrono::duration<>` object.
   *
   * @tparam DurationRep a placeholder to match the `Rep` tparam for @p
   *     duration's type. The semantics of this template parameter are
   *     documented in `std::chrono::duration<>`. In brief, the underlying
   *     arithmetic type used to store the number of ticks. For our purposes it
   *     is simply a formal parameter.
   * @tparam DurationPeriod a placeholder to match the `Period` tparam for @p
   *     duration's type. The semantics of this template parameter are
   *     documented in `std::chrono::duration<>`. In brief, the length of the
   *     tick in seconds, expressed as a `std::ratio<>`. For our purposes it is
   *     simply a formal parameter.
   * @param maximum_duration the maximum time allowed before the policy expires.
   *     While the application can express this time in any units they desire,
   *     the class truncates to milliseconds.
   *
   * @see https://en.cppreference.com/w/cpp/chrono/duration for more information
   *     about `std::chrono::duration`.
   */
  template <typename DurationRep, typename DurationPeriod>
  explicit ClusterManagerLimitedTimeRetryPolicy(
      std::chrono::duration<DurationRep, DurationPeriod> maximum_duration)
      : impl_(maximum_duration) {}

  ClusterManagerLimitedTimeRetryPolicy(
      ClusterManagerLimitedTimeRetryPolicy&& rhs) noexcept
      : ClusterManagerLimitedTimeRetryPolicy(rhs.maximum_duration()) {}
  ClusterManagerLimitedTimeRetryPolicy(
      ClusterManagerLimitedTimeRetryPolicy const& rhs) noexcept
      : ClusterManagerLimitedTimeRetryPolicy(rhs.maximum_duration()) {}

  std::chrono::milliseconds maximum_duration() const {
    return impl_.maximum_duration();
  }

  bool OnFailure(Status const& status) override {
    return impl_.OnFailure(status);
  }
  bool IsExhausted() const override { return impl_.IsExhausted(); }
  bool IsPermanentFailure(Status const& status) const override {
    return impl_.IsPermanentFailure(status);
  }
  std::unique_ptr<ClusterManagerRetryPolicy> clone() const override {
    return std::make_unique<ClusterManagerLimitedTimeRetryPolicy>(
        maximum_duration());
  }

  // This is provided only for backwards compatibility.
  using BaseType = ClusterManagerRetryPolicy;

 private:
  google::cloud::internal::LimitedTimeRetryPolicy<
      container_v1_internal::ClusterManagerRetryTraits>
      impl_;
};

/**
 * The `ClusterManagerConnection` object for `ClusterManagerClient`.
 *
 * This interface defines virtual methods for each of the user-facing overload
 * sets in `ClusterManagerClient`. This allows users to inject custom behavior
 * (e.g., with a Google Mock object) when writing tests that use objects of type
 * `ClusterManagerClient`.
 *
 * To create a concrete instance, see `MakeClusterManagerConnection()`.
 *
 * For mocking, see `container_v1_mocks::MockClusterManagerConnection`.
 */
class ClusterManagerConnection {
 public:
  virtual ~ClusterManagerConnection() = 0;

  virtual Options options() { return Options{}; }

  virtual StatusOr<google::container::v1::ListClustersResponse> ListClusters(
      google::container::v1::ListClustersRequest const& request);

  virtual StatusOr<google::container::v1::Cluster> GetCluster(
      google::container::v1::GetClusterRequest const& request);

  virtual StatusOr<google::container::v1::Operation> CreateCluster(
      google::container::v1::CreateClusterRequest const& request);

  virtual StatusOr<google::container::v1::Operation> UpdateCluster(
      google::container::v1::UpdateClusterRequest const& request);

  virtual StatusOr<google::container::v1::Operation> UpdateNodePool(
      google::container::v1::UpdateNodePoolRequest const& request);

  virtual StatusOr<google::container::v1::Operation> SetNodePoolAutoscaling(
      google::container::v1::SetNodePoolAutoscalingRequest const& request);

  virtual StatusOr<google::container::v1::Operation> SetLoggingService(
      google::container::v1::SetLoggingServiceRequest const& request);

  virtual StatusOr<google::container::v1::Operation> SetMonitoringService(
      google::container::v1::SetMonitoringServiceRequest const& request);

  virtual StatusOr<google::container::v1::Operation> SetAddonsConfig(
      google::container::v1::SetAddonsConfigRequest const& request);

  virtual StatusOr<google::container::v1::Operation> SetLocations(
      google::container::v1::SetLocationsRequest const& request);

  virtual StatusOr<google::container::v1::Operation> UpdateMaster(
      google::container::v1::UpdateMasterRequest const& request);

  virtual StatusOr<google::container::v1::Operation> SetMasterAuth(
      google::container::v1::SetMasterAuthRequest const& request);

  virtual StatusOr<google::container::v1::Operation> DeleteCluster(
      google::container::v1::DeleteClusterRequest const& request);

  virtual StatusOr<google::container::v1::ListOperationsResponse>
  ListOperations(google::container::v1::ListOperationsRequest const& request);

  virtual StatusOr<google::container::v1::Operation> GetOperation(
      google::container::v1::GetOperationRequest const& request);

  virtual Status CancelOperation(
      google::container::v1::CancelOperationRequest const& request);

  virtual StatusOr<google::container::v1::ServerConfig> GetServerConfig(
      google::container::v1::GetServerConfigRequest const& request);

  virtual StatusOr<google::container::v1::GetJSONWebKeysResponse>
  GetJSONWebKeys(google::container::v1::GetJSONWebKeysRequest const& request);

  virtual StatusOr<google::container::v1::ListNodePoolsResponse> ListNodePools(
      google::container::v1::ListNodePoolsRequest const& request);

  virtual StatusOr<google::container::v1::NodePool> GetNodePool(
      google::container::v1::GetNodePoolRequest const& request);

  virtual StatusOr<google::container::v1::Operation> CreateNodePool(
      google::container::v1::CreateNodePoolRequest const& request);

  virtual StatusOr<google::container::v1::Operation> DeleteNodePool(
      google::container::v1::DeleteNodePoolRequest const& request);

  virtual Status CompleteNodePoolUpgrade(
      google::container::v1::CompleteNodePoolUpgradeRequest const& request);

  virtual StatusOr<google::container::v1::Operation> RollbackNodePoolUpgrade(
      google::container::v1::RollbackNodePoolUpgradeRequest const& request);

  virtual StatusOr<google::container::v1::Operation> SetNodePoolManagement(
      google::container::v1::SetNodePoolManagementRequest const& request);

  virtual StatusOr<google::container::v1::Operation> SetLabels(
      google::container::v1::SetLabelsRequest const& request);

  virtual StatusOr<google::container::v1::Operation> SetLegacyAbac(
      google::container::v1::SetLegacyAbacRequest const& request);

  virtual StatusOr<google::container::v1::Operation> StartIPRotation(
      google::container::v1::StartIPRotationRequest const& request);

  virtual StatusOr<google::container::v1::Operation> CompleteIPRotation(
      google::container::v1::CompleteIPRotationRequest const& request);

  virtual StatusOr<google::container::v1::Operation> SetNodePoolSize(
      google::container::v1::SetNodePoolSizeRequest const& request);

  virtual StatusOr<google::container::v1::Operation> SetNetworkPolicy(
      google::container::v1::SetNetworkPolicyRequest const& request);

  virtual StatusOr<google::container::v1::Operation> SetMaintenancePolicy(
      google::container::v1::SetMaintenancePolicyRequest const& request);

  virtual StreamRange<google::container::v1::UsableSubnetwork>
  ListUsableSubnetworks(
      google::container::v1::ListUsableSubnetworksRequest request);

  virtual StatusOr<google::container::v1::CheckAutopilotCompatibilityResponse>
  CheckAutopilotCompatibility(
      google::container::v1::CheckAutopilotCompatibilityRequest const& request);

  virtual StatusOr<google::container::v1::ClusterUpgradeInfo>
  FetchClusterUpgradeInfo(
      google::container::v1::FetchClusterUpgradeInfoRequest const& request);

  virtual StatusOr<google::container::v1::NodePoolUpgradeInfo>
  FetchNodePoolUpgradeInfo(
      google::container::v1::FetchNodePoolUpgradeInfoRequest const& request);
};

/**
 * A factory function to construct an object of type `ClusterManagerConnection`.
 *
 * The returned connection object should not be used directly; instead it
 * should be passed as an argument to the constructor of ClusterManagerClient.
 *
 * The optional @p options argument may be used to configure aspects of the
 * returned `ClusterManagerConnection`. Expected options are any of the types in
 * the following option lists:
 *
 * - `google::cloud::CommonOptionList`
 * - `google::cloud::GrpcOptionList`
 * - `google::cloud::UnifiedCredentialsOptionList`
 * - `google::cloud::container_v1::ClusterManagerPolicyOptionList`
 *
 * @note Unexpected options will be ignored. To log unexpected options instead,
 *     set `GOOGLE_CLOUD_CPP_ENABLE_CLOG=yes` in the environment.
 *
 * @param options (optional) Configure the `ClusterManagerConnection` created by
 * this function.
 */
std::shared_ptr<ClusterManagerConnection> MakeClusterManagerConnection(
    Options options = {});

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace container_v1
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_CONTAINER_V1_CLUSTER_MANAGER_CONNECTION_H
