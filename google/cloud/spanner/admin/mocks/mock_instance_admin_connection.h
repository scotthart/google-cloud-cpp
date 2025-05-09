// Copyright 2021 Google LLC
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
// source: google/spanner/admin/instance/v1/spanner_instance_admin.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_SPANNER_ADMIN_MOCKS_MOCK_INSTANCE_ADMIN_CONNECTION_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_SPANNER_ADMIN_MOCKS_MOCK_INSTANCE_ADMIN_CONNECTION_H

#include "google/cloud/spanner/admin/instance_admin_connection.h"
#include <gmock/gmock.h>

namespace google {
namespace cloud {
namespace spanner_admin_mocks {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

/**
 * A class to mock `InstanceAdminConnection`.
 *
 * Application developers may want to test their code with simulated responses,
 * including errors, from an object of type `InstanceAdminClient`. To do so,
 * construct an object of type `InstanceAdminClient` with an instance of this
 * class. Then use the Google Test framework functions to program the behavior
 * of this mock.
 *
 * @see [This example][bq-mock] for how to test your application with GoogleTest.
 * While the example showcases types from the BigQuery library, the underlying
 * principles apply for any pair of `*Client` and `*Connection`.
 *
 * [bq-mock]: @cloud_cpp_docs_link{bigquery,bigquery-read-mock}
 */
class MockInstanceAdminConnection
    : public spanner_admin::InstanceAdminConnection {
 public:
  MOCK_METHOD(Options, options, (), (override));

  MOCK_METHOD(
      (StreamRange<google::spanner::admin::instance::v1::InstanceConfig>),
      ListInstanceConfigs,
      (google::spanner::admin::instance::v1::ListInstanceConfigsRequest
           request),
      (override));

  MOCK_METHOD(
      StatusOr<google::spanner::admin::instance::v1::InstanceConfig>,
      GetInstanceConfig,
      (google::spanner::admin::instance::v1::GetInstanceConfigRequest const&
           request),
      (override));

  /// To disambiguate calls, use:
  ///
  /// @code
  /// using ::testing::_;
  /// using ::testing::Matcher;
  /// EXPECT_CALL(*mock,
  /// CreateInstanceConfig(Matcher<google::spanner::admin::instance::v1::CreateInstanceConfigRequest
  /// const&>(_)))
  /// @endcode
  MOCK_METHOD(
      future<StatusOr<google::spanner::admin::instance::v1::InstanceConfig>>,
      CreateInstanceConfig,
      (google::spanner::admin::instance::v1::CreateInstanceConfigRequest const&
           request),
      (override));

  /// To disambiguate calls, use:
  ///
  /// @code
  /// using ::testing::_;
  /// EXPECT_CALL(*mock, CreateInstanceConfig(_, _))
  /// @endcode
  MOCK_METHOD(
      StatusOr<google::longrunning::Operation>, CreateInstanceConfig,
      (NoAwaitTag,
       google::spanner::admin::instance::v1::CreateInstanceConfigRequest const&
           request),
      (override));

  /// To disambiguate calls, use:
  ///
  /// @code
  /// using ::testing::_;
  /// using ::testing::Matcher;
  /// EXPECT_CALL(*mock,
  /// CreateInstanceConfig(Matcher<google::longrunning::Operation const&>(_)))
  /// @endcode
  MOCK_METHOD(
      future<StatusOr<google::spanner::admin::instance::v1::InstanceConfig>>,
      CreateInstanceConfig, (google::longrunning::Operation const& operation),
      (override));

  /// To disambiguate calls, use:
  ///
  /// @code
  /// using ::testing::_;
  /// using ::testing::Matcher;
  /// EXPECT_CALL(*mock,
  /// UpdateInstanceConfig(Matcher<google::spanner::admin::instance::v1::UpdateInstanceConfigRequest
  /// const&>(_)))
  /// @endcode
  MOCK_METHOD(
      future<StatusOr<google::spanner::admin::instance::v1::InstanceConfig>>,
      UpdateInstanceConfig,
      (google::spanner::admin::instance::v1::UpdateInstanceConfigRequest const&
           request),
      (override));

  /// To disambiguate calls, use:
  ///
  /// @code
  /// using ::testing::_;
  /// EXPECT_CALL(*mock, UpdateInstanceConfig(_, _))
  /// @endcode
  MOCK_METHOD(
      StatusOr<google::longrunning::Operation>, UpdateInstanceConfig,
      (NoAwaitTag,
       google::spanner::admin::instance::v1::UpdateInstanceConfigRequest const&
           request),
      (override));

  /// To disambiguate calls, use:
  ///
  /// @code
  /// using ::testing::_;
  /// using ::testing::Matcher;
  /// EXPECT_CALL(*mock,
  /// UpdateInstanceConfig(Matcher<google::longrunning::Operation const&>(_)))
  /// @endcode
  MOCK_METHOD(
      future<StatusOr<google::spanner::admin::instance::v1::InstanceConfig>>,
      UpdateInstanceConfig, (google::longrunning::Operation const& operation),
      (override));

  MOCK_METHOD(
      Status, DeleteInstanceConfig,
      (google::spanner::admin::instance::v1::DeleteInstanceConfigRequest const&
           request),
      (override));

  MOCK_METHOD(
      (StreamRange<google::longrunning::Operation>),
      ListInstanceConfigOperations,
      (google::spanner::admin::instance::v1::ListInstanceConfigOperationsRequest
           request),
      (override));

  MOCK_METHOD(
      (StreamRange<google::spanner::admin::instance::v1::Instance>),
      ListInstances,
      (google::spanner::admin::instance::v1::ListInstancesRequest request),
      (override));

  MOCK_METHOD(
      (StreamRange<google::spanner::admin::instance::v1::InstancePartition>),
      ListInstancePartitions,
      (google::spanner::admin::instance::v1::ListInstancePartitionsRequest
           request),
      (override));

  MOCK_METHOD(
      StatusOr<google::spanner::admin::instance::v1::Instance>, GetInstance,
      (google::spanner::admin::instance::v1::GetInstanceRequest const& request),
      (override));

  /// To disambiguate calls, use:
  ///
  /// @code
  /// using ::testing::_;
  /// using ::testing::Matcher;
  /// EXPECT_CALL(*mock,
  /// CreateInstance(Matcher<google::spanner::admin::instance::v1::CreateInstanceRequest
  /// const&>(_)))
  /// @endcode
  MOCK_METHOD(
      future<StatusOr<google::spanner::admin::instance::v1::Instance>>,
      CreateInstance,
      (google::spanner::admin::instance::v1::CreateInstanceRequest const&
           request),
      (override));

  /// To disambiguate calls, use:
  ///
  /// @code
  /// using ::testing::_;
  /// EXPECT_CALL(*mock, CreateInstance(_, _))
  /// @endcode
  MOCK_METHOD(
      StatusOr<google::longrunning::Operation>, CreateInstance,
      (NoAwaitTag,
       google::spanner::admin::instance::v1::CreateInstanceRequest const&
           request),
      (override));

  /// To disambiguate calls, use:
  ///
  /// @code
  /// using ::testing::_;
  /// using ::testing::Matcher;
  /// EXPECT_CALL(*mock, CreateInstance(Matcher<google::longrunning::Operation
  /// const&>(_)))
  /// @endcode
  MOCK_METHOD(future<StatusOr<google::spanner::admin::instance::v1::Instance>>,
              CreateInstance, (google::longrunning::Operation const& operation),
              (override));

  /// To disambiguate calls, use:
  ///
  /// @code
  /// using ::testing::_;
  /// using ::testing::Matcher;
  /// EXPECT_CALL(*mock,
  /// UpdateInstance(Matcher<google::spanner::admin::instance::v1::UpdateInstanceRequest
  /// const&>(_)))
  /// @endcode
  MOCK_METHOD(
      future<StatusOr<google::spanner::admin::instance::v1::Instance>>,
      UpdateInstance,
      (google::spanner::admin::instance::v1::UpdateInstanceRequest const&
           request),
      (override));

  /// To disambiguate calls, use:
  ///
  /// @code
  /// using ::testing::_;
  /// EXPECT_CALL(*mock, UpdateInstance(_, _))
  /// @endcode
  MOCK_METHOD(
      StatusOr<google::longrunning::Operation>, UpdateInstance,
      (NoAwaitTag,
       google::spanner::admin::instance::v1::UpdateInstanceRequest const&
           request),
      (override));

  /// To disambiguate calls, use:
  ///
  /// @code
  /// using ::testing::_;
  /// using ::testing::Matcher;
  /// EXPECT_CALL(*mock, UpdateInstance(Matcher<google::longrunning::Operation
  /// const&>(_)))
  /// @endcode
  MOCK_METHOD(future<StatusOr<google::spanner::admin::instance::v1::Instance>>,
              UpdateInstance, (google::longrunning::Operation const& operation),
              (override));

  MOCK_METHOD(
      Status, DeleteInstance,
      (google::spanner::admin::instance::v1::DeleteInstanceRequest const&
           request),
      (override));

  MOCK_METHOD(StatusOr<google::iam::v1::Policy>, SetIamPolicy,
              (google::iam::v1::SetIamPolicyRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::iam::v1::Policy>, GetIamPolicy,
              (google::iam::v1::GetIamPolicyRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::iam::v1::TestIamPermissionsResponse>,
              TestIamPermissions,
              (google::iam::v1::TestIamPermissionsRequest const& request),
              (override));

  MOCK_METHOD(
      StatusOr<google::spanner::admin::instance::v1::InstancePartition>,
      GetInstancePartition,
      (google::spanner::admin::instance::v1::GetInstancePartitionRequest const&
           request),
      (override));

  /// To disambiguate calls, use:
  ///
  /// @code
  /// using ::testing::_;
  /// using ::testing::Matcher;
  /// EXPECT_CALL(*mock,
  /// CreateInstancePartition(Matcher<google::spanner::admin::instance::v1::CreateInstancePartitionRequest
  /// const&>(_)))
  /// @endcode
  MOCK_METHOD(
      future<StatusOr<google::spanner::admin::instance::v1::InstancePartition>>,
      CreateInstancePartition,
      (google::spanner::admin::instance::v1::
           CreateInstancePartitionRequest const& request),
      (override));

  /// To disambiguate calls, use:
  ///
  /// @code
  /// using ::testing::_;
  /// EXPECT_CALL(*mock, CreateInstancePartition(_, _))
  /// @endcode
  MOCK_METHOD(StatusOr<google::longrunning::Operation>, CreateInstancePartition,
              (NoAwaitTag, google::spanner::admin::instance::v1::
                               CreateInstancePartitionRequest const& request),
              (override));

  /// To disambiguate calls, use:
  ///
  /// @code
  /// using ::testing::_;
  /// using ::testing::Matcher;
  /// EXPECT_CALL(*mock,
  /// CreateInstancePartition(Matcher<google::longrunning::Operation
  /// const&>(_)))
  /// @endcode
  MOCK_METHOD(
      future<StatusOr<google::spanner::admin::instance::v1::InstancePartition>>,
      CreateInstancePartition,
      (google::longrunning::Operation const& operation), (override));

  MOCK_METHOD(Status, DeleteInstancePartition,
              (google::spanner::admin::instance::v1::
                   DeleteInstancePartitionRequest const& request),
              (override));

  /// To disambiguate calls, use:
  ///
  /// @code
  /// using ::testing::_;
  /// using ::testing::Matcher;
  /// EXPECT_CALL(*mock,
  /// UpdateInstancePartition(Matcher<google::spanner::admin::instance::v1::UpdateInstancePartitionRequest
  /// const&>(_)))
  /// @endcode
  MOCK_METHOD(
      future<StatusOr<google::spanner::admin::instance::v1::InstancePartition>>,
      UpdateInstancePartition,
      (google::spanner::admin::instance::v1::
           UpdateInstancePartitionRequest const& request),
      (override));

  /// To disambiguate calls, use:
  ///
  /// @code
  /// using ::testing::_;
  /// EXPECT_CALL(*mock, UpdateInstancePartition(_, _))
  /// @endcode
  MOCK_METHOD(StatusOr<google::longrunning::Operation>, UpdateInstancePartition,
              (NoAwaitTag, google::spanner::admin::instance::v1::
                               UpdateInstancePartitionRequest const& request),
              (override));

  /// To disambiguate calls, use:
  ///
  /// @code
  /// using ::testing::_;
  /// using ::testing::Matcher;
  /// EXPECT_CALL(*mock,
  /// UpdateInstancePartition(Matcher<google::longrunning::Operation
  /// const&>(_)))
  /// @endcode
  MOCK_METHOD(
      future<StatusOr<google::spanner::admin::instance::v1::InstancePartition>>,
      UpdateInstancePartition,
      (google::longrunning::Operation const& operation), (override));

  MOCK_METHOD((StreamRange<google::longrunning::Operation>),
              ListInstancePartitionOperations,
              (google::spanner::admin::instance::v1::
                   ListInstancePartitionOperationsRequest request),
              (override));

  /// To disambiguate calls, use:
  ///
  /// @code
  /// using ::testing::_;
  /// using ::testing::Matcher;
  /// EXPECT_CALL(*mock,
  /// MoveInstance(Matcher<google::spanner::admin::instance::v1::MoveInstanceRequest
  /// const&>(_)))
  /// @endcode
  MOCK_METHOD(
      future<
          StatusOr<google::spanner::admin::instance::v1::MoveInstanceResponse>>,
      MoveInstance,
      (google::spanner::admin::instance::v1::MoveInstanceRequest const&
           request),
      (override));

  /// To disambiguate calls, use:
  ///
  /// @code
  /// using ::testing::_;
  /// EXPECT_CALL(*mock, MoveInstance(_, _))
  /// @endcode
  MOCK_METHOD(StatusOr<google::longrunning::Operation>, MoveInstance,
              (NoAwaitTag,
               google::spanner::admin::instance::v1::MoveInstanceRequest const&
                   request),
              (override));

  /// To disambiguate calls, use:
  ///
  /// @code
  /// using ::testing::_;
  /// using ::testing::Matcher;
  /// EXPECT_CALL(*mock, MoveInstance(Matcher<google::longrunning::Operation
  /// const&>(_)))
  /// @endcode
  MOCK_METHOD(
      future<
          StatusOr<google::spanner::admin::instance::v1::MoveInstanceResponse>>,
      MoveInstance, (google::longrunning::Operation const& operation),
      (override));

  MOCK_METHOD((StreamRange<google::longrunning::Operation>), ListOperations,
              (google::longrunning::ListOperationsRequest request), (override));

  MOCK_METHOD(StatusOr<google::longrunning::Operation>, GetOperation,
              (google::longrunning::GetOperationRequest const& request),
              (override));

  MOCK_METHOD(Status, DeleteOperation,
              (google::longrunning::DeleteOperationRequest const& request),
              (override));

  MOCK_METHOD(Status, CancelOperation,
              (google::longrunning::CancelOperationRequest const& request),
              (override));
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace spanner_admin_mocks
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_SPANNER_ADMIN_MOCKS_MOCK_INSTANCE_ADMIN_CONNECTION_H
