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

#include "google/cloud/bigtable/data_connection.h"
#include "google/cloud/bigtable/internal/bigtable_stub_factory.h"
#include "google/cloud/bigtable/internal/data_connection_impl.h"
#include "google/cloud/bigtable/internal/data_tracing_connection.h"
#include "google/cloud/bigtable/internal/defaults.h"
#include "google/cloud/bigtable/internal/mutate_rows_limiter.h"
#include "google/cloud/bigtable/internal/partial_result_set_source.h"
#include "google/cloud/bigtable/internal/row_reader_impl.h"
#include "google/cloud/bigtable/options.h"
#include "google/cloud/bigtable/result_source_interface.h"
#include "google/cloud/background_threads.h"
#include "google/cloud/common_options.h"
#include "google/cloud/credentials.h"
#include "google/cloud/grpc_options.h"
#include "google/cloud/internal/make_status.h"
#include "google/cloud/internal/opentelemetry.h"
#include "google/cloud/internal/unified_grpc_credentials.h"
#include <memory>

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
  std::shared_ptr<DataConnection> conn;

  if (options.has<experimental::InstanceChannelAffinityOption>()) {
    auto stub_creation_fn =
        [auth, cq = background->cq(), options](
            std::string const& instance_name,
            bigtable_internal::StubManager::Priming priming) {
          return bigtable_internal::CreateBigtableStub(auth, cq, instance_name,
                                                       priming, options);
        };

    auto affinity_stubs = bigtable_internal::CreateBigtableAffinityStubs(
        options.get<experimental::InstanceChannelAffinityOption>(),
        stub_creation_fn);
    conn = std::make_shared<bigtable_internal::DataConnectionImpl>(
        std::move(background),
        std::make_unique<bigtable_internal::StubManager>(
            std::move(affinity_stubs), stub_creation_fn),
        std::move(limiter), std::move(options));
  } else {
    auto stub = bigtable_internal::CreateBigtableStub(
        std::move(auth), background->cq(), options);
    conn = std::make_shared<bigtable_internal::DataConnectionImpl>(
        std::move(background),
        std::make_unique<bigtable_internal::StubManager>(std::move(stub)),
        std::move(limiter), std::move(options));
  }
  if (google::cloud::internal::TracingEnabled(conn->options())) {
    conn = bigtable_internal::MakeDataTracingConnection(std::move(conn));
  }
  return conn;
}

#if 0
std::shared_ptr<InstanceDataConnection> MakeInstanceDataConnection(
    InstanceResource instance, Options options) {
  auto conn = MakeDataConnectionHelper(instance, std::move(options));
  auto instance_conn = std::shared_ptr<InstanceDataConnection>(
    new InstanceDataConnection(std::move(instance), std::move(conn)));
  return instance_conn;
}

Status InstanceMismatchError(std::string const& request,
                             std::string const& instance) {
  return google::cloud::internal::InvalidArgumentError(
      absl::StrFormat("Instance mismatch. Provided DataConnection can only be "
                      "used with instance %s. Request contained %s",
                      instance, request),
      GCP_ERROR_INFO());
}

Status InstanceDataConnection::Apply(std::string const& table_name,
                                     SingleRowMutation mut) {
  if (!absl::StartsWithIgnoreCase(table_name, instance_.FullName())) {
    return InstanceMismatchError(table_name, instance_.FullName());
  }
  return connection_->Apply(table_name, std::move(mut));
}

future<Status> InstanceDataConnection::AsyncApply(std::string const& table_name,
                                                  SingleRowMutation mut) {
  if (!absl::StartsWithIgnoreCase(table_name, instance_.FullName())) {
    return make_ready_future(
        InstanceMismatchError(table_name, instance_.FullName()));
  }
  return connection_->AsyncApply(table_name, std::move(mut));
}

std::vector<FailedMutation> InstanceDataConnection::BulkApply(
    std::string const& table_name, BulkMutation mut) {
  if (!absl::StartsWithIgnoreCase(table_name, instance_.FullName())) {
    return bigtable_internal::MakeFailedMutations(
        InstanceMismatchError(table_name, instance_.FullName()), mut.size());
  }
  return connection_->BulkApply(table_name, std::move(mut));
}

future<std::vector<FailedMutation>> InstanceDataConnection::AsyncBulkApply(
    std::string const& table_name, BulkMutation mut) {
  if (!absl::StartsWithIgnoreCase(table_name, instance_.FullName())) {
    return make_ready_future(bigtable_internal::MakeFailedMutations(
        InstanceMismatchError(table_name, instance_.FullName()), mut.size()));
  }
  return connection_->AsyncBulkApply(table_name, std::move(mut));
}

RowReader InstanceDataConnection::ReadRows(std::string const& table_name,
                                           RowSet row_set,
                                           std::int64_t rows_limit,
                                           Filter filter) {
  if (!absl::StartsWithIgnoreCase(table_name, instance_.FullName())) {
    return bigtable_internal::MakeRowReader(
        std::make_shared<bigtable_internal::StatusOnlyRowReader>(
            InstanceMismatchError(table_name, instance_.FullName())));
  }
  return connection_->ReadRows(table_name, std::move(row_set), rows_limit,
                               std::move(filter));
}

RowReader InstanceDataConnection::ReadRowsFull(ReadRowsParams params) {
  if (!absl::StartsWithIgnoreCase(params.table_name, instance_.FullName())) {
    return bigtable_internal::MakeRowReader(
        std::make_shared<bigtable_internal::StatusOnlyRowReader>(
            InstanceMismatchError(params.table_name, instance_.FullName())));
  }
  return connection_->ReadRowsFull(std::move(params));
}

StatusOr<std::pair<bool, Row>> InstanceDataConnection::ReadRow(
    std::string const& table_name, std::string row_key, Filter filter) {
  if (!absl::StartsWithIgnoreCase(table_name, instance_.FullName())) {
    InstanceMismatchError(table_name, instance_.FullName());
  }
  return connection_->ReadRow(table_name, std::move(row_key),
                              std::move(filter));
}

StatusOr<MutationBranch> InstanceDataConnection::CheckAndMutateRow(
    std::string const& table_name, std::string row_key, Filter filter,
    std::vector<Mutation> true_mutations,
    std::vector<Mutation> false_mutations) {
  if (!absl::StartsWithIgnoreCase(table_name, instance_.FullName())) {
    return InstanceMismatchError(table_name, instance_.FullName());
  }
  return connection_->CheckAndMutateRow(
      table_name, std::move(row_key), std::move(filter),
      std::move(true_mutations), std::move(false_mutations));
}

future<StatusOr<MutationBranch>> InstanceDataConnection::AsyncCheckAndMutateRow(
    std::string const& table_name, std::string row_key, Filter filter,
    std::vector<Mutation> true_mutations,
    std::vector<Mutation> false_mutations) {
  if (!absl::StartsWithIgnoreCase(table_name, instance_.FullName())) {
    return make_ready_future(StatusOr<MutationBranch>(
        InstanceMismatchError(table_name, instance_.FullName())));
  }
  return connection_->AsyncCheckAndMutateRow(
      table_name, std::move(row_key), std::move(filter),
      std::move(true_mutations), std::move(false_mutations));
}

StatusOr<std::vector<RowKeySample>> InstanceDataConnection::SampleRows(
    std::string const& table_name) {
  if (!absl::StartsWithIgnoreCase(table_name, instance_.FullName())) {
    return InstanceMismatchError(table_name, instance_.FullName());
  }
  return connection_->SampleRows(table_name);
}

future<StatusOr<std::vector<RowKeySample>>>
InstanceDataConnection::AsyncSampleRows(std::string const& table_name) {
  if (!absl::StartsWithIgnoreCase(table_name, instance_.FullName())) {
    return make_ready_future(StatusOr<std::vector<RowKeySample>>(
        InstanceMismatchError(table_name, instance_.FullName())));
  }
  return connection_->AsyncSampleRows(table_name);
}

StatusOr<Row> InstanceDataConnection::ReadModifyWriteRow(
    google::bigtable::v2::ReadModifyWriteRowRequest request) {
  if (!absl::StartsWithIgnoreCase(request.table_name(), instance_.FullName())) {
    return InstanceMismatchError(request.table_name(), instance_.FullName());
  }
  return connection_->ReadModifyWriteRow(std::move(request));
}

future<StatusOr<Row>> InstanceDataConnection::AsyncReadModifyWriteRow(
    google::bigtable::v2::ReadModifyWriteRowRequest request) {
  if (!absl::StartsWithIgnoreCase(request.table_name(), instance_.FullName())) {
    return make_ready_future(StatusOr<Row>(
        InstanceMismatchError(request.table_name(), instance_.FullName())));
  }
  return connection_->AsyncReadModifyWriteRow(std::move(request));
}

void InstanceDataConnection::AsyncReadRows(
    std::string const& table_name, std::function<future<bool>(Row)> on_row,
    std::function<void(Status)> on_finish, RowSet row_set,
    std::int64_t rows_limit, Filter filter) {
  // TODO(sdhart): figure out how to return an error here.
  return connection_->AsyncReadRows(table_name, std::move(on_row),
                                    std::move(on_finish), std::move(row_set),
                                    rows_limit, std::move(filter));
}

future<StatusOr<std::pair<bool, Row>>> InstanceDataConnection::AsyncReadRow(
    std::string const& table_name, std::string row_key, Filter filter) {
  if (!absl::StartsWithIgnoreCase(table_name, instance_.FullName())) {
    return make_ready_future(StatusOr<std::pair<bool, Row>>(
        InstanceMismatchError(table_name, instance_.FullName())));
  }
  return connection_->AsyncReadRow(table_name, std::move(row_key),
                                   std::move(filter));
}

StatusOr<bigtable::PreparedQuery> InstanceDataConnection::PrepareQuery(
    bigtable::PrepareQueryParams const& p) {
  if (p.instance != instance_) {
    return InstanceMismatchError(p.instance.FullName(), instance_.FullName());
  }
  return connection_->PrepareQuery(p);
}
future<StatusOr<bigtable::PreparedQuery>>
InstanceDataConnection::AsyncPrepareQuery(
    bigtable::PrepareQueryParams const& p) {
  if (p.instance != instance_) {
    return make_ready_future(StatusOr<PreparedQuery>(
        InstanceMismatchError(p.instance.FullName(), instance_.FullName())));
  }
  return connection_->AsyncPrepareQuery(p);
}
bigtable::RowStream InstanceDataConnection::ExecuteQuery(
    bigtable::ExecuteQueryParams p) {
  if (p.bound_query.instance() != instance_) {
    return bigtable::RowStream(
        std::make_unique<bigtable_internal::StatusOnlyResultSetSource>(
            InstanceMismatchError(p.bound_query.instance().FullName(),
                                  instance_.FullName())));
  }
  return connection_->ExecuteQuery(std::move(p));
}
#endif

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigtable
}  // namespace cloud
}  // namespace google
