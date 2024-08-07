// Copyright 2024 Google LLC
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
// source: google/cloud/bigquery/v2/job.proto

#include "google/cloud/bigquerycontrol/v2/internal/job_tracing_connection.h"
#include "google/cloud/internal/opentelemetry.h"
#include "google/cloud/internal/traced_stream_range.h"
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace bigquerycontrol_v2_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

#ifdef GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY

JobServiceTracingConnection::JobServiceTracingConnection(
    std::shared_ptr<bigquerycontrol_v2::JobServiceConnection> child)
    : child_(std::move(child)) {}

StatusOr<google::cloud::bigquery::v2::JobCancelResponse>
JobServiceTracingConnection::CancelJob(
    google::cloud::bigquery::v2::CancelJobRequest const& request) {
  auto span =
      internal::MakeSpan("bigquerycontrol_v2::JobServiceConnection::CancelJob");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->CancelJob(request));
}

StatusOr<google::cloud::bigquery::v2::Job> JobServiceTracingConnection::GetJob(
    google::cloud::bigquery::v2::GetJobRequest const& request) {
  auto span =
      internal::MakeSpan("bigquerycontrol_v2::JobServiceConnection::GetJob");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->GetJob(request));
}

StatusOr<google::cloud::bigquery::v2::Job>
JobServiceTracingConnection::InsertJob(
    google::cloud::bigquery::v2::InsertJobRequest const& request) {
  auto span =
      internal::MakeSpan("bigquerycontrol_v2::JobServiceConnection::InsertJob");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->InsertJob(request));
}

Status JobServiceTracingConnection::DeleteJob(
    google::cloud::bigquery::v2::DeleteJobRequest const& request) {
  auto span =
      internal::MakeSpan("bigquerycontrol_v2::JobServiceConnection::DeleteJob");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->DeleteJob(request));
}

StreamRange<google::cloud::bigquery::v2::ListFormatJob>
JobServiceTracingConnection::ListJobs(
    google::cloud::bigquery::v2::ListJobsRequest request) {
  auto span =
      internal::MakeSpan("bigquerycontrol_v2::JobServiceConnection::ListJobs");
  internal::OTelScope scope(span);
  auto sr = child_->ListJobs(std::move(request));
  return internal::MakeTracedStreamRange<
      google::cloud::bigquery::v2::ListFormatJob>(std::move(span),
                                                  std::move(sr));
}

StatusOr<google::cloud::bigquery::v2::GetQueryResultsResponse>
JobServiceTracingConnection::GetQueryResults(
    google::cloud::bigquery::v2::GetQueryResultsRequest const& request) {
  auto span = internal::MakeSpan(
      "bigquerycontrol_v2::JobServiceConnection::GetQueryResults");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->GetQueryResults(request));
}

StatusOr<google::cloud::bigquery::v2::QueryResponse>
JobServiceTracingConnection::Query(
    google::cloud::bigquery::v2::PostQueryRequest const& request) {
  auto span =
      internal::MakeSpan("bigquerycontrol_v2::JobServiceConnection::Query");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->Query(request));
}

#endif  // GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY

std::shared_ptr<bigquerycontrol_v2::JobServiceConnection>
MakeJobServiceTracingConnection(
    std::shared_ptr<bigquerycontrol_v2::JobServiceConnection> conn) {
#ifdef GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY
  if (internal::TracingEnabled(conn->options())) {
    conn = std::make_shared<JobServiceTracingConnection>(std::move(conn));
  }
#endif  // GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY
  return conn;
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigquerycontrol_v2_internal
}  // namespace cloud
}  // namespace google
