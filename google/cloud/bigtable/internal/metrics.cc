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

#ifdef GOOGLE_CLOUD_CPP_BIGTABLE_WITH_OTEL_METRICS

#include "google/cloud/bigtable/internal/metrics.h"
#include "google/cloud/bigtable/version.h"
#include <algorithm>
#include <map>
#include <set>

namespace google {
namespace cloud {
namespace bigtable_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN
namespace {
auto constexpr kMeterInstrumentationScopeVersion = "v1";
}  // namespace

// TODO(#15329): Refactor how we're handling different data labels for
// the various RPCs. Adding a function to each metric type to add its DataLabels
// to the map should be more performant than performing a set_difference every
// time.
LabelMap IntoLabelMap(ResourceLabels const& r, DataLabels const& d,
                      std::set<std::string> const& filtered_data_labels) {
  LabelMap labels = {{"project_id", r.project_id},
                     {"instance", r.instance},
                     {"table", r.table},
                     {"cluster", r.cluster},
                     {"zone", r.zone}};
  std::map<std::string, std::string> data = {{
      {"method", d.method},
      {"streaming", d.streaming},
      {"client_name", d.client_name},
      {"client_uid", d.client_uid},
      {"app_profile", d.app_profile},
      {"status", d.status},
  }};

  if (filtered_data_labels.empty()) {
    labels.insert(data.begin(), data.end());
    return labels;
  }

  struct Compare {
    bool operator()(std::pair<std::string const, std::string> const& a,
                    std::string const& b) {
      return a.first < b;
    }

    bool operator()(std::string const& a,
                    std::pair<std::string const, std::string> const& b) {
      return a < b.first;
    }
  };

  std::set_difference(data.begin(), data.end(), filtered_data_labels.begin(),
                      filtered_data_labels.end(),
                      std::inserter(labels, labels.begin()), Compare());
  return labels;
}

absl::optional<google::bigtable::v2::ResponseParams>
GetResponseParamsFromTrailingMetadata(
    grpc::ClientContext const& client_context) {
  auto metadata = client_context.GetServerTrailingMetadata();
  auto iter = metadata.find("x-goog-ext-425905942-bin");
  if (iter == metadata.end()) return absl::nullopt;
  google::bigtable::v2::ResponseParams p;
  // The value for this key should always be the same in a response, so we
  // return the first value we find.
  std::string value{iter->second.data(), iter->second.size()};
  if (p.ParseFromString(value)) return p;
  return absl::nullopt;
}

Metric::~Metric() = default;

OperationLatency::OperationLatency(
    std::string const& instrumentation_scope,
    opentelemetry::nostd::shared_ptr<
        opentelemetry::metrics::MeterProvider> const& provider)
    : operation_latencies_(provider
                               ->GetMeter(instrumentation_scope,
                                          kMeterInstrumentationScopeVersion)
                               ->CreateDoubleHistogram("operation_latencies")
                               .release()) {}

void OperationLatency::PreCall(opentelemetry::context::Context const&,
                               PreCallParams const& p) {
  if (p.first_attempt) {
    operation_start_ = p.attempt_start;
  }
}

void OperationLatency::PostCall(opentelemetry::context::Context const&,
                                grpc::ClientContext const& client_context,
                                PostCallParams const&) {
  auto response_params = GetResponseParamsFromTrailingMetadata(client_context);
  if (response_params) {
    resource_labels_.cluster = response_params->cluster_id();
    resource_labels_.zone = response_params->zone_id();
  }
}

void OperationLatency::OnDone(opentelemetry::context::Context const& context,
                              OnDoneParams const& p) {
  data_labels_.status = StatusCodeToString(p.operation_status.code());
  auto operation_elapsed = std::chrono::duration_cast<LatencyDuration>(
      p.operation_end - operation_start_);
  operation_latencies_->Record(operation_elapsed.count(),
                               IntoLabelMap(resource_labels_, data_labels_),
                               context);
}

std::unique_ptr<Metric> OperationLatency::clone(ResourceLabels resource_labels,
                                                DataLabels data_labels) const {
  auto m = std::make_unique<OperationLatency>(*this);
  m->resource_labels_ = std::move(resource_labels);
  m->data_labels_ = std::move(data_labels);
  return m;
}

AttemptLatency::AttemptLatency(
    std::string const& instrumentation_scope,
    opentelemetry::nostd::shared_ptr<
        opentelemetry::metrics::MeterProvider> const& provider)
    : attempt_latencies_(provider
                             ->GetMeter(instrumentation_scope,
                                        kMeterInstrumentationScopeVersion)
                             ->CreateDoubleHistogram("attempt_latencies")) {}

void AttemptLatency::PreCall(opentelemetry::context::Context const&,
                             PreCallParams const& p) {
  attempt_start_ = std::move(p.attempt_start);
}

void AttemptLatency::PostCall(opentelemetry::context::Context const& context,
                              grpc::ClientContext const& client_context,
                              PostCallParams const& p) {
  auto response_params = GetResponseParamsFromTrailingMetadata(client_context);
  if (response_params) {
    resource_labels_.cluster = response_params->cluster_id();
    resource_labels_.zone = response_params->zone_id();
  }
  data_labels_.status = StatusCodeToString(p.attempt_status.code());
  auto attempt_elapsed = std::chrono::duration_cast<LatencyDuration>(
      p.attempt_end - attempt_start_);
  auto m = IntoLabelMap(resource_labels_, data_labels_);
  attempt_latencies_->Record(attempt_elapsed.count(), std::move(m), context);
}

std::unique_ptr<Metric> AttemptLatency::clone(ResourceLabels resource_labels,
                                              DataLabels data_labels) const {
  auto m = std::make_unique<AttemptLatency>(*this);
  m->resource_labels_ = std::move(resource_labels);
  m->data_labels_ = std::move(data_labels);
  return m;
}

RetryCount::RetryCount(
    std::string const& instrumentation_scope,
    opentelemetry::nostd::shared_ptr<
        opentelemetry::metrics::MeterProvider> const& provider)
    : retry_count_(provider
                       ->GetMeter(instrumentation_scope,
                                  kMeterInstrumentationScopeVersion)
                       ->CreateUInt64Counter("retry_count")
                       .release()) {}

void RetryCount::PreCall(opentelemetry::context::Context const&,
                         PreCallParams const& p) {
  if (!p.first_attempt) {
    ++num_retries_;
  }
}

void RetryCount::PostCall(opentelemetry::context::Context const&,
                          grpc::ClientContext const& client_context,
                          PostCallParams const&) {
  auto response_params = GetResponseParamsFromTrailingMetadata(client_context);
  if (response_params) {
    resource_labels_.cluster = response_params->cluster_id();
    resource_labels_.zone = response_params->zone_id();
  }
}

void RetryCount::OnDone(opentelemetry::context::Context const& context,
                        OnDoneParams const& p) {
  data_labels_.status = StatusCodeToString(p.operation_status.code());
  retry_count_->Add(num_retries_,
                    IntoLabelMap(resource_labels_, data_labels_,
                                 std::set<std::string>{"streaming"}),
                    context);
}

std::unique_ptr<Metric> RetryCount::clone(ResourceLabels resource_labels,
                                          DataLabels data_labels) const {
  auto m = std::make_unique<RetryCount>(*this);
  m->resource_labels_ = std::move(resource_labels);
  m->data_labels_ = std::move(data_labels);
  return m;
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigtable_internal
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_BIGTABLE_WITH_OTEL_METRICS
