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
// source: google/cloud/compute/projects/v1/projects.proto

#include "google/cloud/compute/projects/v1/internal/projects_tracing_connection.h"
#include "google/cloud/internal/opentelemetry.h"
#include "google/cloud/internal/traced_stream_range.h"
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace compute_projects_v1_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

#ifdef GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY

ProjectsTracingConnection::ProjectsTracingConnection(
    std::shared_ptr<compute_projects_v1::ProjectsConnection> child)
    : child_(std::move(child)) {}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
ProjectsTracingConnection::DisableXpnHost(
    google::cloud::cpp::compute::projects::v1::DisableXpnHostRequest const&
        request) {
  auto span = internal::MakeSpan(
      "compute_projects_v1::ProjectsConnection::DisableXpnHost");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->DisableXpnHost(request));
}

StatusOr<google::cloud::cpp::compute::v1::Operation>
ProjectsTracingConnection::DisableXpnHost(
    NoAwaitTag,
    google::cloud::cpp::compute::projects::v1::DisableXpnHostRequest const&
        request) {
  auto span = internal::MakeSpan(
      "compute_projects_v1::ProjectsConnection::DisableXpnHost");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span,
                           child_->DisableXpnHost(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
ProjectsTracingConnection::DisableXpnHost(
    google::cloud::cpp::compute::v1::Operation const& operation) {
  auto span = internal::MakeSpan(
      "compute_projects_v1::ProjectsConnection::DisableXpnHost");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->DisableXpnHost(operation));
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
ProjectsTracingConnection::DisableXpnResource(
    google::cloud::cpp::compute::projects::v1::DisableXpnResourceRequest const&
        request) {
  auto span = internal::MakeSpan(
      "compute_projects_v1::ProjectsConnection::DisableXpnResource");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->DisableXpnResource(request));
}

StatusOr<google::cloud::cpp::compute::v1::Operation>
ProjectsTracingConnection::DisableXpnResource(
    NoAwaitTag,
    google::cloud::cpp::compute::projects::v1::DisableXpnResourceRequest const&
        request) {
  auto span = internal::MakeSpan(
      "compute_projects_v1::ProjectsConnection::DisableXpnResource");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span,
                           child_->DisableXpnResource(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
ProjectsTracingConnection::DisableXpnResource(
    google::cloud::cpp::compute::v1::Operation const& operation) {
  auto span = internal::MakeSpan(
      "compute_projects_v1::ProjectsConnection::DisableXpnResource");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->DisableXpnResource(operation));
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
ProjectsTracingConnection::EnableXpnHost(
    google::cloud::cpp::compute::projects::v1::EnableXpnHostRequest const&
        request) {
  auto span = internal::MakeSpan(
      "compute_projects_v1::ProjectsConnection::EnableXpnHost");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->EnableXpnHost(request));
}

StatusOr<google::cloud::cpp::compute::v1::Operation>
ProjectsTracingConnection::EnableXpnHost(
    NoAwaitTag,
    google::cloud::cpp::compute::projects::v1::EnableXpnHostRequest const&
        request) {
  auto span = internal::MakeSpan(
      "compute_projects_v1::ProjectsConnection::EnableXpnHost");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span, child_->EnableXpnHost(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
ProjectsTracingConnection::EnableXpnHost(
    google::cloud::cpp::compute::v1::Operation const& operation) {
  auto span = internal::MakeSpan(
      "compute_projects_v1::ProjectsConnection::EnableXpnHost");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->EnableXpnHost(operation));
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
ProjectsTracingConnection::EnableXpnResource(
    google::cloud::cpp::compute::projects::v1::EnableXpnResourceRequest const&
        request) {
  auto span = internal::MakeSpan(
      "compute_projects_v1::ProjectsConnection::EnableXpnResource");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->EnableXpnResource(request));
}

StatusOr<google::cloud::cpp::compute::v1::Operation>
ProjectsTracingConnection::EnableXpnResource(
    NoAwaitTag,
    google::cloud::cpp::compute::projects::v1::EnableXpnResourceRequest const&
        request) {
  auto span = internal::MakeSpan(
      "compute_projects_v1::ProjectsConnection::EnableXpnResource");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span,
                           child_->EnableXpnResource(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
ProjectsTracingConnection::EnableXpnResource(
    google::cloud::cpp::compute::v1::Operation const& operation) {
  auto span = internal::MakeSpan(
      "compute_projects_v1::ProjectsConnection::EnableXpnResource");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->EnableXpnResource(operation));
}

StatusOr<google::cloud::cpp::compute::v1::Project>
ProjectsTracingConnection::GetProject(
    google::cloud::cpp::compute::projects::v1::GetProjectRequest const&
        request) {
  auto span =
      internal::MakeSpan("compute_projects_v1::ProjectsConnection::GetProject");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->GetProject(request));
}

StatusOr<google::cloud::cpp::compute::v1::Project>
ProjectsTracingConnection::GetXpnHost(
    google::cloud::cpp::compute::projects::v1::GetXpnHostRequest const&
        request) {
  auto span =
      internal::MakeSpan("compute_projects_v1::ProjectsConnection::GetXpnHost");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->GetXpnHost(request));
}

StatusOr<google::cloud::cpp::compute::v1::ProjectsGetXpnResources>
ProjectsTracingConnection::GetXpnResources(
    google::cloud::cpp::compute::projects::v1::GetXpnResourcesRequest const&
        request) {
  auto span = internal::MakeSpan(
      "compute_projects_v1::ProjectsConnection::GetXpnResources");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->GetXpnResources(request));
}

StreamRange<google::cloud::cpp::compute::v1::Project>
ProjectsTracingConnection::ListXpnHosts(
    google::cloud::cpp::compute::projects::v1::ListXpnHostsRequest request) {
  auto span = internal::MakeSpan(
      "compute_projects_v1::ProjectsConnection::ListXpnHosts");
  internal::OTelScope scope(span);
  auto sr = child_->ListXpnHosts(std::move(request));
  return internal::MakeTracedStreamRange<
      google::cloud::cpp::compute::v1::Project>(std::move(span), std::move(sr));
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
ProjectsTracingConnection::MoveDisk(
    google::cloud::cpp::compute::projects::v1::MoveDiskRequest const& request) {
  auto span =
      internal::MakeSpan("compute_projects_v1::ProjectsConnection::MoveDisk");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->MoveDisk(request));
}

StatusOr<google::cloud::cpp::compute::v1::Operation>
ProjectsTracingConnection::MoveDisk(
    NoAwaitTag,
    google::cloud::cpp::compute::projects::v1::MoveDiskRequest const& request) {
  auto span =
      internal::MakeSpan("compute_projects_v1::ProjectsConnection::MoveDisk");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span, child_->MoveDisk(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
ProjectsTracingConnection::MoveDisk(
    google::cloud::cpp::compute::v1::Operation const& operation) {
  auto span =
      internal::MakeSpan("compute_projects_v1::ProjectsConnection::MoveDisk");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->MoveDisk(operation));
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
ProjectsTracingConnection::MoveInstance(
    google::cloud::cpp::compute::projects::v1::MoveInstanceRequest const&
        request) {
  auto span = internal::MakeSpan(
      "compute_projects_v1::ProjectsConnection::MoveInstance");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->MoveInstance(request));
}

StatusOr<google::cloud::cpp::compute::v1::Operation>
ProjectsTracingConnection::MoveInstance(
    NoAwaitTag,
    google::cloud::cpp::compute::projects::v1::MoveInstanceRequest const&
        request) {
  auto span = internal::MakeSpan(
      "compute_projects_v1::ProjectsConnection::MoveInstance");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span, child_->MoveInstance(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
ProjectsTracingConnection::MoveInstance(
    google::cloud::cpp::compute::v1::Operation const& operation) {
  auto span = internal::MakeSpan(
      "compute_projects_v1::ProjectsConnection::MoveInstance");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->MoveInstance(operation));
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
ProjectsTracingConnection::SetCloudArmorTier(
    google::cloud::cpp::compute::projects::v1::SetCloudArmorTierRequest const&
        request) {
  auto span = internal::MakeSpan(
      "compute_projects_v1::ProjectsConnection::SetCloudArmorTier");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->SetCloudArmorTier(request));
}

StatusOr<google::cloud::cpp::compute::v1::Operation>
ProjectsTracingConnection::SetCloudArmorTier(
    NoAwaitTag,
    google::cloud::cpp::compute::projects::v1::SetCloudArmorTierRequest const&
        request) {
  auto span = internal::MakeSpan(
      "compute_projects_v1::ProjectsConnection::SetCloudArmorTier");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span,
                           child_->SetCloudArmorTier(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
ProjectsTracingConnection::SetCloudArmorTier(
    google::cloud::cpp::compute::v1::Operation const& operation) {
  auto span = internal::MakeSpan(
      "compute_projects_v1::ProjectsConnection::SetCloudArmorTier");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->SetCloudArmorTier(operation));
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
ProjectsTracingConnection::SetCommonInstanceMetadata(
    google::cloud::cpp::compute::projects::v1::
        SetCommonInstanceMetadataRequest const& request) {
  auto span = internal::MakeSpan(
      "compute_projects_v1::ProjectsConnection::SetCommonInstanceMetadata");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->SetCommonInstanceMetadata(request));
}

StatusOr<google::cloud::cpp::compute::v1::Operation>
ProjectsTracingConnection::SetCommonInstanceMetadata(
    NoAwaitTag, google::cloud::cpp::compute::projects::v1::
                    SetCommonInstanceMetadataRequest const& request) {
  auto span = internal::MakeSpan(
      "compute_projects_v1::ProjectsConnection::SetCommonInstanceMetadata");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(
      *span, child_->SetCommonInstanceMetadata(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
ProjectsTracingConnection::SetCommonInstanceMetadata(
    google::cloud::cpp::compute::v1::Operation const& operation) {
  auto span = internal::MakeSpan(
      "compute_projects_v1::ProjectsConnection::SetCommonInstanceMetadata");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->SetCommonInstanceMetadata(operation));
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
ProjectsTracingConnection::SetDefaultNetworkTier(
    google::cloud::cpp::compute::projects::v1::
        SetDefaultNetworkTierRequest const& request) {
  auto span = internal::MakeSpan(
      "compute_projects_v1::ProjectsConnection::SetDefaultNetworkTier");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->SetDefaultNetworkTier(request));
}

StatusOr<google::cloud::cpp::compute::v1::Operation>
ProjectsTracingConnection::SetDefaultNetworkTier(
    NoAwaitTag, google::cloud::cpp::compute::projects::v1::
                    SetDefaultNetworkTierRequest const& request) {
  auto span = internal::MakeSpan(
      "compute_projects_v1::ProjectsConnection::SetDefaultNetworkTier");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(
      *span, child_->SetDefaultNetworkTier(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
ProjectsTracingConnection::SetDefaultNetworkTier(
    google::cloud::cpp::compute::v1::Operation const& operation) {
  auto span = internal::MakeSpan(
      "compute_projects_v1::ProjectsConnection::SetDefaultNetworkTier");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->SetDefaultNetworkTier(operation));
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
ProjectsTracingConnection::SetUsageExportBucket(
    google::cloud::cpp::compute::projects::v1::
        SetUsageExportBucketRequest const& request) {
  auto span = internal::MakeSpan(
      "compute_projects_v1::ProjectsConnection::SetUsageExportBucket");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->SetUsageExportBucket(request));
}

StatusOr<google::cloud::cpp::compute::v1::Operation>
ProjectsTracingConnection::SetUsageExportBucket(
    NoAwaitTag, google::cloud::cpp::compute::projects::v1::
                    SetUsageExportBucketRequest const& request) {
  auto span = internal::MakeSpan(
      "compute_projects_v1::ProjectsConnection::SetUsageExportBucket");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span,
                           child_->SetUsageExportBucket(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
ProjectsTracingConnection::SetUsageExportBucket(
    google::cloud::cpp::compute::v1::Operation const& operation) {
  auto span = internal::MakeSpan(
      "compute_projects_v1::ProjectsConnection::SetUsageExportBucket");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->SetUsageExportBucket(operation));
}

#endif  // GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY

std::shared_ptr<compute_projects_v1::ProjectsConnection>
MakeProjectsTracingConnection(
    std::shared_ptr<compute_projects_v1::ProjectsConnection> conn) {
#ifdef GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY
  if (internal::TracingEnabled(conn->options())) {
    conn = std::make_shared<ProjectsTracingConnection>(std::move(conn));
  }
#endif  // GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY
  return conn;
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace compute_projects_v1_internal
}  // namespace cloud
}  // namespace google
