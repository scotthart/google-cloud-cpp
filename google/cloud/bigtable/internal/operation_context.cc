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

#include "google/cloud/bigtable/internal/operation_context.h"
#include "google/cloud/bigtable/internal/metrics.h"
#include "absl/strings/match.h"
#include "absl/strings/str_split.h"
#ifdef GOOGLE_CLOUD_CPP_BIGTABLE_WITH_OTEL_METRICS
#include <opentelemetry/context/runtime_context.h>
#endif

namespace google {
namespace cloud {
namespace bigtable_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

#ifdef GOOGLE_CLOUD_CPP_BIGTABLE_WITH_OTEL_METRICS
namespace {
std::vector<std::shared_ptr<Metric>> CloneMetrics(
    ResourceLabels const& resource_labels, DataLabels const& data_labels,
    std::vector<std::shared_ptr<Metric const>> const& metrics) {
  std::vector<std::shared_ptr<Metric>> v;
  v.reserve(metrics.size());
  for (auto const& m : metrics) {
    v.emplace_back(m->clone(resource_labels, data_labels));
  }
  return v;
}
}  // namespace
#endif

#if 0
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
#endif

void OperationContext::ProcessMetadata(
    std::multimap<grpc::string_ref, grpc::string_ref> const& metadata) {
  for (auto const& kv : metadata) {
    auto key = std::string{kv.first.data(), kv.first.size()};
    if (absl::StartsWith(key, "x-goog-cbt-cookie")) {
      cookies_[std::move(key)] =
          std::string{kv.second.data(), kv.second.size()};
    }
  }
}

#ifdef GOOGLE_CLOUD_CPP_BIGTABLE_WITH_OTEL_METRICS

OperationContext::OperationContext(
    ResourceLabels const& resource_labels, DataLabels const& data_labels,
    std::vector<std::shared_ptr<Metric const>> const& metrics,
    std::shared_ptr<Clock> clock)
    : cloned_metrics_(CloneMetrics(resource_labels, data_labels, metrics)),
      clock_(std::move(clock)) {}

void OperationContext::PreCall(grpc::ClientContext& client_context) {
  auto otel_context = opentelemetry::context::RuntimeContext::GetCurrent();
  auto attempt_start = clock_->Now();
  if (attempt_number_ == 0) {
    operation_start_ = attempt_start;
  }
  for (auto& m : cloned_metrics_) {
    m->PreCall(otel_context,
               PreCallParams{attempt_start, attempt_number_ == 0});
  }

  for (auto const& h : cookies_) {
    client_context.AddMetadata(h.first, h.second);
  }
  client_context.AddMetadata("bigtable-attempt",
                             std::to_string(attempt_number_++));
}

void OperationContext::PostCall(grpc::ClientContext const& client_context,
                                google::cloud::Status const& status) {
  ProcessMetadata(client_context.GetServerInitialMetadata());
  ProcessMetadata(client_context.GetServerTrailingMetadata());
  //  auto response_params =
  //  GetResponseParamsFromTrailingMetadata(client_context); if
  //  (response_params) {
  //    std::cout << "cluster_id: " << response_params->cluster_id()
  //              << "; zone_id: " << response_params->zone_id()
  //              << std::endl;
  //  }
  auto attempt_end = clock_->Now();
  auto otel_context = opentelemetry::context::RuntimeContext::GetCurrent();
  for (auto& m : cloned_metrics_) {
    m->PostCall(otel_context, client_context,
                PostCallParams{attempt_end, status});
  }
}

void OperationContext::OnDone(Status const& s) {
  auto operation_end = clock_->Now();
  auto otel_context = opentelemetry::context::RuntimeContext::GetCurrent();
  for (auto& m : cloned_metrics_) {
    m->OnDone(otel_context, OnDoneParams{operation_end, s});
  }
}

void OperationContext::ElementRequest(grpc::ClientContext const&) {
  auto element_request = clock_->Now();
  auto otel_context = opentelemetry::context::RuntimeContext::GetCurrent();
  for (auto& m : cloned_metrics_) {
    m->ElementRequest(otel_context, ElementRequestParams{element_request});
  }
}

void OperationContext::ElementDelivery(grpc::ClientContext const&) {
  auto otel_context = opentelemetry::context::RuntimeContext::GetCurrent();
  auto first_response = clock_->Now();
  for (auto& m : cloned_metrics_) {
    m->ElementDelivery(otel_context,
                       ElementDeliveryParams{first_response, first_response_});
  }
  if (first_response_) {
    first_response_ = false;
  }
}

#else  // GOOGLE_CLOUD_CPP_BIGTABLE_WITH_OTEL_METRICS

OperationContext::OperationContext(
    ResourceLabels const&, DataLabels const&,
    std::vector<std::shared_ptr<Metric const>> const&, std::shared_ptr<Clock>) {
}

void OperationContext::PreCall(grpc::ClientContext& client_context) {
  for (auto const& h : cookies_) {
    client_context.AddMetadata(h.first, h.second);
  }
  client_context.AddMetadata("bigtable-attempt",
                             std::to_string(attempt_number_++));
}

void OperationContext::PostCall(grpc::ClientContext const& client_context,
                                google::cloud::Status const&) {
  ProcessMetadata(client_context.GetServerInitialMetadata());
  ProcessMetadata(client_context.GetServerTrailingMetadata());
  //  auto response_params =
  //  GetResponseParamsFromTrailingMetadata(client_context); if
  //  (response_params) {
  //    std::cout << "cluster_id: " << response_params->cluster_id()
  //              << "; zone_id: " << response_params->zone_id()
  //              << std::endl;
  //  }
}

void OperationContext::OnDone(Status const&) {}

void OperationContext::ElementRequest(grpc::ClientContext const&) {}

void OperationContext::ElementDelivery(grpc::ClientContext const&) {}

#endif  // GOOGLE_CLOUD_CPP_BIGTABLE_WITH_OTEL_METRICS

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigtable_internal
}  // namespace cloud
}  // namespace google
