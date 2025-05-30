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
// source: google/cloud/parametermanager/v1/service.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_PARAMETERMANAGER_V1_INTERNAL_PARAMETER_MANAGER_TRACING_CONNECTION_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_PARAMETERMANAGER_V1_INTERNAL_PARAMETER_MANAGER_TRACING_CONNECTION_H

#include "google/cloud/parametermanager/v1/parameter_manager_connection.h"
#include "google/cloud/version.h"
#include <memory>

namespace google {
namespace cloud {
namespace parametermanager_v1_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

#ifdef GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY

class ParameterManagerTracingConnection
    : public parametermanager_v1::ParameterManagerConnection {
 public:
  ~ParameterManagerTracingConnection() override = default;

  explicit ParameterManagerTracingConnection(
      std::shared_ptr<parametermanager_v1::ParameterManagerConnection> child);

  Options options() override { return child_->options(); }

  StreamRange<google::cloud::parametermanager::v1::Parameter> ListParameters(
      google::cloud::parametermanager::v1::ListParametersRequest request)
      override;

  StatusOr<google::cloud::parametermanager::v1::Parameter> GetParameter(
      google::cloud::parametermanager::v1::GetParameterRequest const& request)
      override;

  StatusOr<google::cloud::parametermanager::v1::Parameter> CreateParameter(
      google::cloud::parametermanager::v1::CreateParameterRequest const&
          request) override;

  StatusOr<google::cloud::parametermanager::v1::Parameter> UpdateParameter(
      google::cloud::parametermanager::v1::UpdateParameterRequest const&
          request) override;

  Status DeleteParameter(
      google::cloud::parametermanager::v1::DeleteParameterRequest const&
          request) override;

  StreamRange<google::cloud::parametermanager::v1::ParameterVersion>
  ListParameterVersions(
      google::cloud::parametermanager::v1::ListParameterVersionsRequest request)
      override;

  StatusOr<google::cloud::parametermanager::v1::ParameterVersion>
  GetParameterVersion(
      google::cloud::parametermanager::v1::GetParameterVersionRequest const&
          request) override;

  StatusOr<google::cloud::parametermanager::v1::RenderParameterVersionResponse>
  RenderParameterVersion(
      google::cloud::parametermanager::v1::RenderParameterVersionRequest const&
          request) override;

  StatusOr<google::cloud::parametermanager::v1::ParameterVersion>
  CreateParameterVersion(
      google::cloud::parametermanager::v1::CreateParameterVersionRequest const&
          request) override;

  StatusOr<google::cloud::parametermanager::v1::ParameterVersion>
  UpdateParameterVersion(
      google::cloud::parametermanager::v1::UpdateParameterVersionRequest const&
          request) override;

  Status DeleteParameterVersion(
      google::cloud::parametermanager::v1::DeleteParameterVersionRequest const&
          request) override;

  StreamRange<google::cloud::location::Location> ListLocations(
      google::cloud::location::ListLocationsRequest request) override;

  StatusOr<google::cloud::location::Location> GetLocation(
      google::cloud::location::GetLocationRequest const& request) override;

 private:
  std::shared_ptr<parametermanager_v1::ParameterManagerConnection> child_;
};

#endif  // GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY

/**
 * Conditionally applies the tracing decorator to the given connection.
 *
 * The connection is only decorated if tracing is enabled (as determined by the
 * connection's options).
 */
std::shared_ptr<parametermanager_v1::ParameterManagerConnection>
MakeParameterManagerTracingConnection(
    std::shared_ptr<parametermanager_v1::ParameterManagerConnection> conn);

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace parametermanager_v1_internal
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_PARAMETERMANAGER_V1_INTERNAL_PARAMETER_MANAGER_TRACING_CONNECTION_H
