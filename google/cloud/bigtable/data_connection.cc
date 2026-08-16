// Copyright 2022 Google LLC
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

#include "google/cloud/internal/disable_deprecation_warnings.inc"
#include "google/cloud/bigtable/data_connection.h"
#include "google/cloud/bigtable/internal/bigtable_stub_factory.h"
#include "google/cloud/bigtable/internal/data_connection_impl.h"
#include "google/cloud/bigtable/internal/data_tracing_connection.h"
#include "google/cloud/bigtable/internal/defaults.h"
#include "google/cloud/bigtable/internal/directpath_diagnostics.h"
#include "google/cloud/bigtable/internal/directpath_prober.h"
#include "google/cloud/bigtable/internal/grpc_metrics_exporter.h"
#include "google/cloud/bigtable/internal/metrics.h"
#include "google/cloud/bigtable/internal/mutate_rows_limiter.h"
#include "google/cloud/bigtable/internal/partial_result_set_source.h"
#include "google/cloud/bigtable/internal/row_reader_impl.h"
#include "google/cloud/bigtable/options.h"
#include "google/cloud/bigtable/result_source_interface.h"
#include "google/cloud/background_threads.h"
#include "google/cloud/common_options.h"
#include "google/cloud/credentials.h"
#include "google/cloud/future.h"
#include "google/cloud/grpc_options.h"
#include "google/cloud/internal/opentelemetry.h"
#include "google/cloud/internal/unified_grpc_credentials.h"
#ifdef GOOGLE_CLOUD_CPP_BIGTABLE_WITH_OTEL_METRICS
#include "google/cloud/bigtable/internal/client_schema_metrics.h"
#include "google/cloud/monitoring/v3/metric_connection.h"
#include "google/cloud/internal/random.h"
#include <opentelemetry/context/runtime_context.h>
#endif  // GOOGLE_CLOUD_CPP_BIGTABLE_WITH_OTEL_METRICS
#include <memory>
#include <mutex>

namespace google {
namespace cloud {
namespace bigtable_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

std::vector<bigtable::FailedMutation> MakeFailedMutations(Status const& status,
                                                          std::size_t n) {
  std::vector<bigtable::FailedMutation> mutations;
  mutations.reserve(n);
  for (int i = 0; i != static_cast<int>(n); ++i) {
    mutations.emplace_back(status, i);
  }
  return mutations;
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigtable_internal
namespace bigtable {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

DataConnection::~DataConnection() = default;

// NOLINTNEXTLINE(performance-unnecessary-value-param)
Status DataConnection::Apply(std::string const&, SingleRowMutation) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

future<Status> DataConnection::AsyncApply(
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    std::string const&, SingleRowMutation) {
  return make_ready_future(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

std::vector<FailedMutation> DataConnection::BulkApply(
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    std::string const&, BulkMutation mut) {
  return bigtable_internal::MakeFailedMutations(
      Status(StatusCode::kUnimplemented, "not-implemented"), mut.size());
}

future<std::vector<FailedMutation>> DataConnection::AsyncBulkApply(
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    std::string const&, BulkMutation mut) {
  return make_ready_future(bigtable_internal::MakeFailedMutations(
      Status(StatusCode::kUnimplemented, "not-implemented"), mut.size()));
}

RowReader DataConnection::ReadRows(std::string const& table_name,
                                   RowSet row_set, std::int64_t rows_limit,
                                   Filter filter) {
  auto const& options = google::cloud::internal::CurrentOptions();
  return ReadRowsFull(ReadRowsParams{
      std::move(table_name),
      options.get<AppProfileIdOption>(),
      std::move(row_set),
      rows_limit,
      std::move(filter),
      options.get<ReverseScanOption>(),
  });
}

// NOLINTNEXTLINE(performance-unnecessary-value-param)
RowReader DataConnection::ReadRowsFull(ReadRowsParams) {
  return MakeRowReader(std::make_shared<bigtable_internal::StatusOnlyRowReader>(
      Status(StatusCode::kUnimplemented, "not implemented")));
}

StatusOr<std::pair<bool, Row>> DataConnection::ReadRow(
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    std::string const&, std::string, Filter) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StatusOr<MutationBranch> DataConnection::CheckAndMutateRow(
    std::string const&,
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    std::string, Filter, std::vector<Mutation>, std::vector<Mutation>) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

future<StatusOr<MutationBranch>> DataConnection::AsyncCheckAndMutateRow(
    std::string const&,
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    std::string, Filter, std::vector<Mutation>, std::vector<Mutation>) {
  return make_ready_future<StatusOr<MutationBranch>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

StatusOr<std::vector<RowKeySample>> DataConnection::SampleRows(
    std::string const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

future<StatusOr<std::vector<RowKeySample>>> DataConnection::AsyncSampleRows(
    std::string const&) {
  return make_ready_future<StatusOr<std::vector<RowKeySample>>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

StatusOr<Row> DataConnection::ReadModifyWriteRow(
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    google::bigtable::v2::ReadModifyWriteRowRequest) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

future<StatusOr<Row>> DataConnection::AsyncReadModifyWriteRow(
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    google::bigtable::v2::ReadModifyWriteRowRequest) {
  return make_ready_future<StatusOr<Row>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

void DataConnection::AsyncReadRows(
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    std::string const&, std::function<future<bool>(Row)>,
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    std::function<void(Status)> on_finish, RowSet, std::int64_t, Filter) {
  on_finish(Status(StatusCode::kUnimplemented, "not implemented"));
}

future<StatusOr<std::pair<bool, Row>>> DataConnection::AsyncReadRow(
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    std::string const&, std::string, Filter) {
  return make_ready_future<StatusOr<std::pair<bool, Row>>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

StatusOr<bigtable::PreparedQuery> DataConnection::PrepareQuery(
    bigtable::PrepareQueryParams const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}
future<StatusOr<bigtable::PreparedQuery>> DataConnection::AsyncPrepareQuery(
    bigtable::PrepareQueryParams const&) {
  return make_ready_future<StatusOr<PreparedQuery>>(
      Status(StatusCode::kUnimplemented, "not implemented"));
}

bigtable::RowStream DataConnection::ExecuteQuery(bigtable::ExecuteQueryParams) {
  return RowStream(
      std::make_unique<bigtable_internal::StatusOnlyResultSetSource>(
          Status(StatusCode::kUnimplemented, "not implemented")));
}

std::shared_ptr<DataConnection> MakeDataConnection(
    std::vector<InstanceResource> instances, Options options) {
  options.set<bigtable_internal::InstanceChannelAffinityOption>(
      std::move(instances));
  return MakeDataConnection(std::move(options));
}

std::shared_ptr<DataConnection> MakeDataConnection(Options options) {
  google::cloud::internal::CheckExpectedOptions<
      AppProfileIdOption, CommonOptionList, GrpcOptionList,
      UnifiedCredentialsOptionList, ClientOptionList, DataPolicyOptionList>(
      options, __func__);
  options = bigtable::internal::DefaultDataOptions(std::move(options));
  auto background =
      google::cloud::internal::MakeBackgroundThreadsFactory(options)();
  auto auth = google::cloud::internal::CreateAuthenticationStrategy(
      background->cq(), options);
  auto limiter =
      bigtable_internal::MakeMutateRowsLimiter(background->cq(), options);

  std::shared_ptr<monitoring_v3::MetricServiceConnection>
      metric_service_connection;
  std::unique_ptr<bigtable_internal::OperationContextFactory>
      operation_context_factory;

#ifdef GOOGLE_CLOUD_CPP_BIGTABLE_WITH_OTEL_METRICS
  std::string client_uid;
  if (options.get<EnableMetricsOption>()) {
    metric_service_connection = monitoring_v3::MakeMetricServiceConnection(
        internal::MetricsExporterConnectionOptions(options));
    auto gen = google::cloud::internal::MakeDefaultPRNG();
    client_uid = google::cloud::internal::Sample(
        gen, 16, "abcdefghijklmnopqrstuvwxyz0123456789");
#ifdef GOOGLE_CLOUD_CPP_BIGTABLE_WITH_GRPC_OTEL_METRICS
    if (bigtable::internal::IsDirectPath(options) &&
        options.has<bigtable_internal::InstanceChannelAffinityOption>() &&
        options.get<experimental::DirectPathMetricsModeOption>() ==
            experimental::DirectPathMetricsMode::kEnabled) {
      bigtable_internal::EnableGrpcMetrics(metric_service_connection, options,
                                           client_uid);
    }
#endif  // GOOGLE_CLOUD_CPP_BIGTABLE_WITH_GRPC_OTEL_METRICS
    operation_context_factory =
        std::make_unique<bigtable_internal::MetricsOperationContextFactory>(
            client_uid, metric_service_connection, options);
  } else {
    operation_context_factory =
        std::make_unique<bigtable_internal::SimpleOperationContextFactory>();
  }
#else
  operation_context_factory =
      std::make_unique<bigtable_internal::SimpleOperationContextFactory>();
#endif  // GOOGLE_CLOUD_CPP_BIGTABLE_WITH_OTEL_METRICS

#ifdef GOOGLE_CLOUD_CPP_BIGTABLE_WITH_OTEL_METRICS
  auto const* metrics_factory =
      dynamic_cast<bigtable_internal::MetricsOperationContextFactory*>(
          operation_context_factory.get());
  std::shared_ptr<bigtable_internal::DirectAccessCompatibility>
      direct_access_compatibility =
          metrics_factory != nullptr
              ? metrics_factory->direct_access_compatibility()
              : nullptr;
#endif

  std::shared_ptr<DataConnection> conn;

  if (options.has<bigtable_internal::InstanceChannelAffinityOption>()) {
    if (bigtable::internal::IsDirectPath(options)) {
      Options dp_options = options;
      dp_options.set<::google::cloud::bigtable_internal::DataEndpointOption>(
          "google-c2p:///bigtable.googleapis.com");
      dp_options.set<EndpointOption>("google-c2p:///bigtable.googleapis.com");
      dp_options.set<AuthorityOption>("bigtable.googleapis.com");
      dp_options.set<experimental::DirectPathModeOption>(
          experimental::DirectPathMode::kEnabled);

      Options cp_options = options;
      cp_options.set<::google::cloud::bigtable_internal::DataEndpointOption>(
          "bigtable.googleapis.com");
      cp_options.set<EndpointOption>("bigtable.googleapis.com");
      cp_options.set<AuthorityOption>("bigtable.googleapis.com");
      cp_options.set<experimental::DirectPathModeOption>(
          experimental::DirectPathMode::kDisabled);

      promise<std::unique_ptr<bigtable_internal::StubManager>> dp_promise;
      future<std::unique_ptr<bigtable_internal::StubManager>> dp_future =
          dp_promise.get_future();
      promise<std::unique_ptr<bigtable_internal::StubManager>> cp_promise;
      future<std::unique_ptr<bigtable_internal::StubManager>> cp_future =
          cp_promise.get_future();

      background->cq().RunAsync([p = std::move(dp_promise), auth,
                                 cq = background->cq(), dp_options]() mutable {
        auto stub_creation_fn =
            [auth, cq, dp_options](
                std::string_view instance_name,
                bigtable_internal::StubManager::Priming priming) {
              return bigtable_internal::CreateBigtableStub(
                  auth, cq, instance_name, priming, dp_options);
            };
        absl::flat_hash_map<std::string,
                            std::shared_ptr<bigtable_internal::BigtableStub>>
            affinity_stubs = bigtable_internal::CreateBigtableAffinityStubs(
                dp_options
                    .get<bigtable_internal::InstanceChannelAffinityOption>(),
                stub_creation_fn);
        p.set_value(std::make_unique<bigtable_internal::StubManager>(
            std::move(affinity_stubs), stub_creation_fn));
      });

      background->cq().RunAsync([p = std::move(cp_promise), auth,
                                 cq = background->cq(), cp_options]() mutable {
        auto stub_creation_fn =
            [auth, cq, cp_options](
                std::string_view instance_name,
                bigtable_internal::StubManager::Priming priming) {
              return bigtable_internal::CreateBigtableStub(
                  auth, cq, instance_name, priming, cp_options);
            };
        absl::flat_hash_map<std::string,
                            std::shared_ptr<bigtable_internal::BigtableStub>>
            affinity_stubs = bigtable_internal::CreateBigtableAffinityStubs(
                cp_options
                    .get<bigtable_internal::InstanceChannelAffinityOption>(),
                stub_creation_fn);
        p.set_value(std::make_unique<bigtable_internal::StubManager>(
            std::move(affinity_stubs), stub_creation_fn));
      });

      bigtable_internal::DirectPathProbeResult const probe_result =
          bigtable_internal::DirectPathProber::Probe(auth, dp_options,
                                                     background->cq());

      if (probe_result.success) {
        std::unique_ptr<bigtable_internal::StubManager> stub_manager =
            dp_future.get();
        background->cq().RunAsync(
            [f = std::move(cp_future)]() mutable { (void)f.get(); });
#ifdef GOOGLE_CLOUD_CPP_BIGTABLE_WITH_OTEL_METRICS
        if (direct_access_compatibility != nullptr) {
          direct_access_compatibility->Record(
              opentelemetry::context::RuntimeContext::GetCurrent(), 1,
              bigtable_internal::DirectAccessCompatibilityLabels{
                  bigtable_internal::ToString(probe_result.ip_preference), ""});
        }
#endif
        conn = std::make_shared<bigtable_internal::DataConnectionImpl>(
            std::move(background), std::move(stub_manager),
            std::move(operation_context_factory), std::move(limiter),
            std::move(dp_options));
      } else {
        std::unique_ptr<bigtable_internal::StubManager> stub_manager =
            cp_future.get();
        background->cq().RunAsync(
            [f = std::move(dp_future)]() mutable { (void)f.get(); });
#ifdef GOOGLE_CLOUD_CPP_BIGTABLE_WITH_OTEL_METRICS
        bigtable_internal::DirectPathDiagnostics::RunAsync(
            background->cq(), client_uid, metric_service_connection, dp_options,
            direct_access_compatibility);
#endif
        conn = std::make_shared<bigtable_internal::DataConnectionImpl>(
            std::move(background), std::move(stub_manager),
            std::move(operation_context_factory), std::move(limiter),
            std::move(cp_options));
      }
    } else {
      auto stub_creation_fn =
          [auth, cq = background->cq(), options](
              std::string_view instance_name,
              bigtable_internal::StubManager::Priming priming) {
            return bigtable_internal::CreateBigtableStub(
                auth, cq, instance_name, priming, options);
          };

      auto affinity_stubs = bigtable_internal::CreateBigtableAffinityStubs(
          options.get<bigtable_internal::InstanceChannelAffinityOption>(),
          stub_creation_fn);
#ifdef GOOGLE_CLOUD_CPP_BIGTABLE_WITH_OTEL_METRICS
      if (direct_access_compatibility != nullptr) {
        direct_access_compatibility->Record(
            opentelemetry::context::RuntimeContext::GetCurrent(), 0,
            bigtable_internal::DirectAccessCompatibilityLabels{
                "", "manually_disabled"});
      }
#endif
      conn = std::make_shared<bigtable_internal::DataConnectionImpl>(
          std::move(background),
          std::make_unique<bigtable_internal::StubManager>(
              std::move(affinity_stubs), stub_creation_fn),
          std::move(operation_context_factory), std::move(limiter),
          std::move(options));
    }
  } else {
    auto stub = bigtable_internal::CreateBigtableStub(
        std::move(auth), background->cq(), options);
#ifdef GOOGLE_CLOUD_CPP_BIGTABLE_WITH_OTEL_METRICS
    if (direct_access_compatibility != nullptr) {
      direct_access_compatibility->Record(
          opentelemetry::context::RuntimeContext::GetCurrent(), 0,
          bigtable_internal::DirectAccessCompatibilityLabels{
              "", "manually_disabled"});
    }
#endif
    conn = std::make_shared<bigtable_internal::DataConnectionImpl>(
        std::move(background),
        std::make_unique<bigtable_internal::StubManager>(std::move(stub)),
        std::move(operation_context_factory), std::move(limiter),
        std::move(options));
  }
  if (google::cloud::internal::TracingEnabled(conn->options())) {
    conn = bigtable_internal::MakeDataTracingConnection(std::move(conn));
  }
  return conn;
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigtable
}  // namespace cloud
}  // namespace google
