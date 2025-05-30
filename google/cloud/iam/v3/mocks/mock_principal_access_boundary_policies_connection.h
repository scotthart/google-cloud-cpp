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
// source: google/iam/v3/principal_access_boundary_policies_service.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_IAM_V3_MOCKS_MOCK_PRINCIPAL_ACCESS_BOUNDARY_POLICIES_CONNECTION_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_IAM_V3_MOCKS_MOCK_PRINCIPAL_ACCESS_BOUNDARY_POLICIES_CONNECTION_H

#include "google/cloud/iam/v3/principal_access_boundary_policies_connection.h"
#include <gmock/gmock.h>

namespace google {
namespace cloud {
namespace iam_v3_mocks {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

/**
 * A class to mock `PrincipalAccessBoundaryPoliciesConnection`.
 *
 * Application developers may want to test their code with simulated responses,
 * including errors, from an object of type
 * `PrincipalAccessBoundaryPoliciesClient`. To do so, construct an object of
 * type `PrincipalAccessBoundaryPoliciesClient` with an instance of this class.
 * Then use the Google Test framework functions to program the behavior of this
 * mock.
 *
 * @see [This example][bq-mock] for how to test your application with GoogleTest.
 * While the example showcases types from the BigQuery library, the underlying
 * principles apply for any pair of `*Client` and `*Connection`.
 *
 * [bq-mock]: @cloud_cpp_docs_link{bigquery,bigquery-read-mock}
 */
class MockPrincipalAccessBoundaryPoliciesConnection
    : public iam_v3::PrincipalAccessBoundaryPoliciesConnection {
 public:
  MOCK_METHOD(Options, options, (), (override));

  /// To disambiguate calls, use:
  ///
  /// @code
  /// using ::testing::_;
  /// using ::testing::Matcher;
  /// EXPECT_CALL(*mock,
  /// CreatePrincipalAccessBoundaryPolicy(Matcher<google::iam::v3::CreatePrincipalAccessBoundaryPolicyRequest
  /// const&>(_)))
  /// @endcode
  MOCK_METHOD(
      future<StatusOr<google::iam::v3::PrincipalAccessBoundaryPolicy>>,
      CreatePrincipalAccessBoundaryPolicy,
      (google::iam::v3::CreatePrincipalAccessBoundaryPolicyRequest const&
           request),
      (override));

  /// To disambiguate calls, use:
  ///
  /// @code
  /// using ::testing::_;
  /// EXPECT_CALL(*mock, CreatePrincipalAccessBoundaryPolicy(_, _))
  /// @endcode
  MOCK_METHOD(
      StatusOr<google::longrunning::Operation>,
      CreatePrincipalAccessBoundaryPolicy,
      (NoAwaitTag,
       google::iam::v3::CreatePrincipalAccessBoundaryPolicyRequest const&
           request),
      (override));

  /// To disambiguate calls, use:
  ///
  /// @code
  /// using ::testing::_;
  /// using ::testing::Matcher;
  /// EXPECT_CALL(*mock,
  /// CreatePrincipalAccessBoundaryPolicy(Matcher<google::longrunning::Operation
  /// const&>(_)))
  /// @endcode
  MOCK_METHOD(future<StatusOr<google::iam::v3::PrincipalAccessBoundaryPolicy>>,
              CreatePrincipalAccessBoundaryPolicy,
              (google::longrunning::Operation const& operation), (override));

  MOCK_METHOD(
      StatusOr<google::iam::v3::PrincipalAccessBoundaryPolicy>,
      GetPrincipalAccessBoundaryPolicy,
      (google::iam::v3::GetPrincipalAccessBoundaryPolicyRequest const& request),
      (override));

  /// To disambiguate calls, use:
  ///
  /// @code
  /// using ::testing::_;
  /// using ::testing::Matcher;
  /// EXPECT_CALL(*mock,
  /// UpdatePrincipalAccessBoundaryPolicy(Matcher<google::iam::v3::UpdatePrincipalAccessBoundaryPolicyRequest
  /// const&>(_)))
  /// @endcode
  MOCK_METHOD(
      future<StatusOr<google::iam::v3::PrincipalAccessBoundaryPolicy>>,
      UpdatePrincipalAccessBoundaryPolicy,
      (google::iam::v3::UpdatePrincipalAccessBoundaryPolicyRequest const&
           request),
      (override));

  /// To disambiguate calls, use:
  ///
  /// @code
  /// using ::testing::_;
  /// EXPECT_CALL(*mock, UpdatePrincipalAccessBoundaryPolicy(_, _))
  /// @endcode
  MOCK_METHOD(
      StatusOr<google::longrunning::Operation>,
      UpdatePrincipalAccessBoundaryPolicy,
      (NoAwaitTag,
       google::iam::v3::UpdatePrincipalAccessBoundaryPolicyRequest const&
           request),
      (override));

  /// To disambiguate calls, use:
  ///
  /// @code
  /// using ::testing::_;
  /// using ::testing::Matcher;
  /// EXPECT_CALL(*mock,
  /// UpdatePrincipalAccessBoundaryPolicy(Matcher<google::longrunning::Operation
  /// const&>(_)))
  /// @endcode
  MOCK_METHOD(future<StatusOr<google::iam::v3::PrincipalAccessBoundaryPolicy>>,
              UpdatePrincipalAccessBoundaryPolicy,
              (google::longrunning::Operation const& operation), (override));

  /// To disambiguate calls, use:
  ///
  /// @code
  /// using ::testing::_;
  /// using ::testing::Matcher;
  /// EXPECT_CALL(*mock,
  /// DeletePrincipalAccessBoundaryPolicy(Matcher<google::iam::v3::DeletePrincipalAccessBoundaryPolicyRequest
  /// const&>(_)))
  /// @endcode
  MOCK_METHOD(
      future<StatusOr<google::iam::v3::OperationMetadata>>,
      DeletePrincipalAccessBoundaryPolicy,
      (google::iam::v3::DeletePrincipalAccessBoundaryPolicyRequest const&
           request),
      (override));

  /// To disambiguate calls, use:
  ///
  /// @code
  /// using ::testing::_;
  /// EXPECT_CALL(*mock, DeletePrincipalAccessBoundaryPolicy(_, _))
  /// @endcode
  MOCK_METHOD(
      StatusOr<google::longrunning::Operation>,
      DeletePrincipalAccessBoundaryPolicy,
      (NoAwaitTag,
       google::iam::v3::DeletePrincipalAccessBoundaryPolicyRequest const&
           request),
      (override));

  /// To disambiguate calls, use:
  ///
  /// @code
  /// using ::testing::_;
  /// using ::testing::Matcher;
  /// EXPECT_CALL(*mock,
  /// DeletePrincipalAccessBoundaryPolicy(Matcher<google::longrunning::Operation
  /// const&>(_)))
  /// @endcode
  MOCK_METHOD(future<StatusOr<google::iam::v3::OperationMetadata>>,
              DeletePrincipalAccessBoundaryPolicy,
              (google::longrunning::Operation const& operation), (override));

  MOCK_METHOD(
      (StreamRange<google::iam::v3::PrincipalAccessBoundaryPolicy>),
      ListPrincipalAccessBoundaryPolicies,
      (google::iam::v3::ListPrincipalAccessBoundaryPoliciesRequest request),
      (override));

  MOCK_METHOD(
      (StreamRange<google::iam::v3::PolicyBinding>),
      SearchPrincipalAccessBoundaryPolicyBindings,
      (google::iam::v3::SearchPrincipalAccessBoundaryPolicyBindingsRequest
           request),
      (override));

  MOCK_METHOD(StatusOr<google::longrunning::Operation>, GetOperation,
              (google::longrunning::GetOperationRequest const& request),
              (override));
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace iam_v3_mocks
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_IAM_V3_MOCKS_MOCK_PRINCIPAL_ACCESS_BOUNDARY_POLICIES_CONNECTION_H
