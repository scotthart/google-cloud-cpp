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
// source: google/cloud/tpu/v2/cloud_tpu.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_TPU_V2_MOCKS_MOCK_TPU_CONNECTION_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_TPU_V2_MOCKS_MOCK_TPU_CONNECTION_H

#include "google/cloud/tpu/v2/tpu_connection.h"
#include <gmock/gmock.h>

namespace google {
namespace cloud {
namespace tpu_v2_mocks {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

/**
 * A class to mock `TpuConnection`.
 *
 * Application developers may want to test their code with simulated responses,
 * including errors, from an object of type `TpuClient`. To do so,
 * construct an object of type `TpuClient` with an instance of this
 * class. Then use the Google Test framework functions to program the behavior
 * of this mock.
 *
 * @see [This example][bq-mock] for how to test your application with GoogleTest.
 * While the example showcases types from the BigQuery library, the underlying
 * principles apply for any pair of `*Client` and `*Connection`.
 *
 * [bq-mock]: @cloud_cpp_docs_link{bigquery,bigquery-read-mock}
 */
class MockTpuConnection : public tpu_v2::TpuConnection {
 public:
  MOCK_METHOD(Options, options, (), (override));

  MOCK_METHOD((StreamRange<google::cloud::tpu::v2::Node>), ListNodes,
              (google::cloud::tpu::v2::ListNodesRequest request), (override));

  MOCK_METHOD(StatusOr<google::cloud::tpu::v2::Node>, GetNode,
              (google::cloud::tpu::v2::GetNodeRequest const& request),
              (override));

  /// Due to additional overloads for this method
  /// `EXPECT_CALL(*mock, CreateNode)` is now ambiguous. Use
  /// `EXPECT_CALL(*mock, CreateNode(::testing::_))` instead.
  MOCK_METHOD(future<StatusOr<google::cloud::tpu::v2::Node>>, CreateNode,
              (google::cloud::tpu::v2::CreateNodeRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::longrunning::Operation>, CreateNode,
              (ExperimentalTag, NoAwaitTag,
               google::cloud::tpu::v2::CreateNodeRequest const& request),
              (override));

  MOCK_METHOD(future<StatusOr<google::cloud::tpu::v2::Node>>, CreateNode,
              (ExperimentalTag,
               google::longrunning::Operation const& operation),
              (override));

  /// Due to additional overloads for this method
  /// `EXPECT_CALL(*mock, DeleteNode)` is now ambiguous. Use
  /// `EXPECT_CALL(*mock, DeleteNode(::testing::_))` instead.
  MOCK_METHOD(future<StatusOr<google::cloud::tpu::v2::OperationMetadata>>,
              DeleteNode,
              (google::cloud::tpu::v2::DeleteNodeRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::longrunning::Operation>, DeleteNode,
              (ExperimentalTag, NoAwaitTag,
               google::cloud::tpu::v2::DeleteNodeRequest const& request),
              (override));

  MOCK_METHOD(future<StatusOr<google::cloud::tpu::v2::OperationMetadata>>,
              DeleteNode,
              (ExperimentalTag,
               google::longrunning::Operation const& operation),
              (override));

  /// Due to additional overloads for this method
  /// `EXPECT_CALL(*mock, StopNode)` is now ambiguous. Use
  /// `EXPECT_CALL(*mock, StopNode(::testing::_))` instead.
  MOCK_METHOD(future<StatusOr<google::cloud::tpu::v2::Node>>, StopNode,
              (google::cloud::tpu::v2::StopNodeRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::longrunning::Operation>, StopNode,
              (ExperimentalTag, NoAwaitTag,
               google::cloud::tpu::v2::StopNodeRequest const& request),
              (override));

  MOCK_METHOD(future<StatusOr<google::cloud::tpu::v2::Node>>, StopNode,
              (ExperimentalTag,
               google::longrunning::Operation const& operation),
              (override));

  /// Due to additional overloads for this method
  /// `EXPECT_CALL(*mock, StartNode)` is now ambiguous. Use
  /// `EXPECT_CALL(*mock, StartNode(::testing::_))` instead.
  MOCK_METHOD(future<StatusOr<google::cloud::tpu::v2::Node>>, StartNode,
              (google::cloud::tpu::v2::StartNodeRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::longrunning::Operation>, StartNode,
              (ExperimentalTag, NoAwaitTag,
               google::cloud::tpu::v2::StartNodeRequest const& request),
              (override));

  MOCK_METHOD(future<StatusOr<google::cloud::tpu::v2::Node>>, StartNode,
              (ExperimentalTag,
               google::longrunning::Operation const& operation),
              (override));

  /// Due to additional overloads for this method
  /// `EXPECT_CALL(*mock, UpdateNode)` is now ambiguous. Use
  /// `EXPECT_CALL(*mock, UpdateNode(::testing::_))` instead.
  MOCK_METHOD(future<StatusOr<google::cloud::tpu::v2::Node>>, UpdateNode,
              (google::cloud::tpu::v2::UpdateNodeRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::longrunning::Operation>, UpdateNode,
              (ExperimentalTag, NoAwaitTag,
               google::cloud::tpu::v2::UpdateNodeRequest const& request),
              (override));

  MOCK_METHOD(future<StatusOr<google::cloud::tpu::v2::Node>>, UpdateNode,
              (ExperimentalTag,
               google::longrunning::Operation const& operation),
              (override));

  MOCK_METHOD(
      StatusOr<google::cloud::tpu::v2::GenerateServiceIdentityResponse>,
      GenerateServiceIdentity,
      (google::cloud::tpu::v2::GenerateServiceIdentityRequest const& request),
      (override));

  MOCK_METHOD((StreamRange<google::cloud::tpu::v2::AcceleratorType>),
              ListAcceleratorTypes,
              (google::cloud::tpu::v2::ListAcceleratorTypesRequest request),
              (override));

  MOCK_METHOD(
      StatusOr<google::cloud::tpu::v2::AcceleratorType>, GetAcceleratorType,
      (google::cloud::tpu::v2::GetAcceleratorTypeRequest const& request),
      (override));

  MOCK_METHOD((StreamRange<google::cloud::tpu::v2::RuntimeVersion>),
              ListRuntimeVersions,
              (google::cloud::tpu::v2::ListRuntimeVersionsRequest request),
              (override));

  MOCK_METHOD(StatusOr<google::cloud::tpu::v2::RuntimeVersion>,
              GetRuntimeVersion,
              (google::cloud::tpu::v2::GetRuntimeVersionRequest const& request),
              (override));

  MOCK_METHOD(
      StatusOr<google::cloud::tpu::v2::GetGuestAttributesResponse>,
      GetGuestAttributes,
      (google::cloud::tpu::v2::GetGuestAttributesRequest const& request),
      (override));
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace tpu_v2_mocks
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_TPU_V2_MOCKS_MOCK_TPU_CONNECTION_H
