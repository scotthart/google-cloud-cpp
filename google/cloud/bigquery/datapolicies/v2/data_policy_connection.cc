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
// source: google/cloud/bigquery/datapolicies/v2/datapolicy.proto

#include "google/cloud/bigquery/datapolicies/v2/data_policy_connection.h"
#include "google/cloud/bigquery/datapolicies/v2/data_policy_options.h"
#include "google/cloud/bigquery/datapolicies/v2/internal/data_policy_connection_impl.h"
#include "google/cloud/bigquery/datapolicies/v2/internal/data_policy_option_defaults.h"
#include "google/cloud/bigquery/datapolicies/v2/internal/data_policy_stub_factory.h"
#include "google/cloud/bigquery/datapolicies/v2/internal/data_policy_tracing_connection.h"
#include "google/cloud/background_threads.h"
#include "google/cloud/common_options.h"
#include "google/cloud/credentials.h"
#include "google/cloud/grpc_options.h"
#include "google/cloud/internal/pagination_range.h"
#include "google/cloud/internal/unified_grpc_credentials.h"
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace bigquery_datapolicies_v2 {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

DataPolicyServiceConnection::~DataPolicyServiceConnection() = default;

StatusOr<google::cloud::bigquery::datapolicies::v2::DataPolicy>
DataPolicyServiceConnection::CreateDataPolicy(
    google::cloud::bigquery::datapolicies::v2::CreateDataPolicyRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StatusOr<google::cloud::bigquery::datapolicies::v2::DataPolicy>
DataPolicyServiceConnection::AddGrantees(
    google::cloud::bigquery::datapolicies::v2::AddGranteesRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StatusOr<google::cloud::bigquery::datapolicies::v2::DataPolicy>
DataPolicyServiceConnection::RemoveGrantees(
    google::cloud::bigquery::datapolicies::v2::RemoveGranteesRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StatusOr<google::cloud::bigquery::datapolicies::v2::DataPolicy>
DataPolicyServiceConnection::UpdateDataPolicy(
    google::cloud::bigquery::datapolicies::v2::UpdateDataPolicyRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

Status DataPolicyServiceConnection::DeleteDataPolicy(
    google::cloud::bigquery::datapolicies::v2::DeleteDataPolicyRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StatusOr<google::cloud::bigquery::datapolicies::v2::DataPolicy>
DataPolicyServiceConnection::GetDataPolicy(
    google::cloud::bigquery::datapolicies::v2::GetDataPolicyRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StreamRange<google::cloud::bigquery::datapolicies::v2::DataPolicy>
DataPolicyServiceConnection::ListDataPolicies(
    google::cloud::bigquery::datapolicies::v2::
        ListDataPoliciesRequest) {  // NOLINT(performance-unnecessary-value-param)
  return google::cloud::internal::MakeUnimplementedPaginationRange<
      StreamRange<google::cloud::bigquery::datapolicies::v2::DataPolicy>>();
}

StatusOr<google::iam::v1::Policy> DataPolicyServiceConnection::GetIamPolicy(
    google::iam::v1::GetIamPolicyRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StatusOr<google::iam::v1::Policy> DataPolicyServiceConnection::SetIamPolicy(
    google::iam::v1::SetIamPolicyRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StatusOr<google::iam::v1::TestIamPermissionsResponse>
DataPolicyServiceConnection::TestIamPermissions(
    google::iam::v1::TestIamPermissionsRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

std::shared_ptr<DataPolicyServiceConnection> MakeDataPolicyServiceConnection(
    Options options) {
  internal::CheckExpectedOptions<CommonOptionList, GrpcOptionList,
                                 UnifiedCredentialsOptionList,
                                 DataPolicyServicePolicyOptionList>(options,
                                                                    __func__);
  options = bigquery_datapolicies_v2_internal::DataPolicyServiceDefaultOptions(
      std::move(options));
  auto background = internal::MakeBackgroundThreadsFactory(options)();
  auto auth = internal::CreateAuthenticationStrategy(background->cq(), options);
  auto stub =
      bigquery_datapolicies_v2_internal::CreateDefaultDataPolicyServiceStub(
          std::move(auth), options);
  return bigquery_datapolicies_v2_internal::
      MakeDataPolicyServiceTracingConnection(
          std::make_shared<bigquery_datapolicies_v2_internal::
                               DataPolicyServiceConnectionImpl>(
              std::move(background), std::move(stub), std::move(options)));
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigquery_datapolicies_v2
}  // namespace cloud
}  // namespace google
