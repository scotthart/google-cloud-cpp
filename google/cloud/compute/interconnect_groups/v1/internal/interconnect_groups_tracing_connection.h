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
// source: google/cloud/compute/interconnect_groups/v1/interconnect_groups.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_COMPUTE_INTERCONNECT_GROUPS_V1_INTERNAL_INTERCONNECT_GROUPS_TRACING_CONNECTION_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_COMPUTE_INTERCONNECT_GROUPS_V1_INTERNAL_INTERCONNECT_GROUPS_TRACING_CONNECTION_H

#include "google/cloud/compute/interconnect_groups/v1/interconnect_groups_connection.h"
#include "google/cloud/version.h"
#include <memory>

namespace google {
namespace cloud {
namespace compute_interconnect_groups_v1_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

#ifdef GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY

class InterconnectGroupsTracingConnection
    : public compute_interconnect_groups_v1::InterconnectGroupsConnection {
 public:
  ~InterconnectGroupsTracingConnection() override = default;

  explicit InterconnectGroupsTracingConnection(
      std::shared_ptr<
          compute_interconnect_groups_v1::InterconnectGroupsConnection>
          child);

  Options options() override { return child_->options(); }

  future<StatusOr<google::cloud::cpp::compute::v1::Operation>> CreateMembers(
      google::cloud::cpp::compute::interconnect_groups::v1::
          CreateMembersRequest const& request) override;

  StatusOr<google::cloud::cpp::compute::v1::Operation> CreateMembers(
      NoAwaitTag, google::cloud::cpp::compute::interconnect_groups::v1::
                      CreateMembersRequest const& request) override;

  future<StatusOr<google::cloud::cpp::compute::v1::Operation>> CreateMembers(
      google::cloud::cpp::compute::v1::Operation const& operation) override;

  future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
  DeleteInterconnectGroup(
      google::cloud::cpp::compute::interconnect_groups::v1::
          DeleteInterconnectGroupRequest const& request) override;

  StatusOr<google::cloud::cpp::compute::v1::Operation> DeleteInterconnectGroup(
      NoAwaitTag, google::cloud::cpp::compute::interconnect_groups::v1::
                      DeleteInterconnectGroupRequest const& request) override;

  future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
  DeleteInterconnectGroup(
      google::cloud::cpp::compute::v1::Operation const& operation) override;

  StatusOr<google::cloud::cpp::compute::v1::InterconnectGroup>
  GetInterconnectGroup(google::cloud::cpp::compute::interconnect_groups::v1::
                           GetInterconnectGroupRequest const& request) override;

  StatusOr<google::cloud::cpp::compute::v1::Policy> GetIamPolicy(
      google::cloud::cpp::compute::interconnect_groups::v1::
          GetIamPolicyRequest const& request) override;

  StatusOr<google::cloud::cpp::compute::v1::
               InterconnectGroupsGetOperationalStatusResponse>
  GetOperationalStatus(google::cloud::cpp::compute::interconnect_groups::v1::
                           GetOperationalStatusRequest const& request) override;

  future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
  InsertInterconnectGroup(
      google::cloud::cpp::compute::interconnect_groups::v1::
          InsertInterconnectGroupRequest const& request) override;

  StatusOr<google::cloud::cpp::compute::v1::Operation> InsertInterconnectGroup(
      NoAwaitTag, google::cloud::cpp::compute::interconnect_groups::v1::
                      InsertInterconnectGroupRequest const& request) override;

  future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
  InsertInterconnectGroup(
      google::cloud::cpp::compute::v1::Operation const& operation) override;

  StreamRange<google::cloud::cpp::compute::v1::InterconnectGroup>
  ListInterconnectGroups(google::cloud::cpp::compute::interconnect_groups::v1::
                             ListInterconnectGroupsRequest request) override;

  future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
  PatchInterconnectGroup(
      google::cloud::cpp::compute::interconnect_groups::v1::
          PatchInterconnectGroupRequest const& request) override;

  StatusOr<google::cloud::cpp::compute::v1::Operation> PatchInterconnectGroup(
      NoAwaitTag, google::cloud::cpp::compute::interconnect_groups::v1::
                      PatchInterconnectGroupRequest const& request) override;

  future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
  PatchInterconnectGroup(
      google::cloud::cpp::compute::v1::Operation const& operation) override;

  StatusOr<google::cloud::cpp::compute::v1::Policy> SetIamPolicy(
      google::cloud::cpp::compute::interconnect_groups::v1::
          SetIamPolicyRequest const& request) override;

  StatusOr<google::cloud::cpp::compute::v1::TestPermissionsResponse>
  TestIamPermissions(google::cloud::cpp::compute::interconnect_groups::v1::
                         TestIamPermissionsRequest const& request) override;

 private:
  std::shared_ptr<compute_interconnect_groups_v1::InterconnectGroupsConnection>
      child_;
};

#endif  // GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY

/**
 * Conditionally applies the tracing decorator to the given connection.
 *
 * The connection is only decorated if tracing is enabled (as determined by the
 * connection's options).
 */
std::shared_ptr<compute_interconnect_groups_v1::InterconnectGroupsConnection>
MakeInterconnectGroupsTracingConnection(
    std::shared_ptr<
        compute_interconnect_groups_v1::InterconnectGroupsConnection>
        conn);

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace compute_interconnect_groups_v1_internal
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_COMPUTE_INTERCONNECT_GROUPS_V1_INTERNAL_INTERCONNECT_GROUPS_TRACING_CONNECTION_H
