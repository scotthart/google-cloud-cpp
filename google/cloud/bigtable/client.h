// Copyright 2025 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BIGTABLE_CLIENT_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BIGTABLE_CLIENT_H

#include "google/cloud/bigtable/data_connection.h"
#include "google/cloud/bigtable/query.h"
#include "google/cloud/options.h"
#include "google/cloud/version.h"

// #include "google/cloud/backoff_policy.h"
// #include "google/cloud/internal/non_constructible.h"
// #include "google/cloud/options.h"
// #include "google/cloud/status.h"
// #include "google/cloud/status_or.h"
// #include <google/spanner/v1/spanner.pb.h>
// #include <grpcpp/grpcpp.h>
// #include <functional>
// #include <initializer_list>
// #include <memory>
// #include <string>
// #include <vector>

namespace google {
namespace cloud {
namespace bigtable {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

// clang-format off
/**
 * Performs database client operations on Spanner.
 *
 * Applications use this class to perform operations on
 * [Spanner Databases][spanner-doc-link].
 *
 * @par Performance
 *
 * `Client` objects are relatively cheap to create, copy, and move. However,
 * each `Client` object must be created with a `std::shared_ptr<Connection>`,
 * which itself is relatively expensive to create. Therefore, connection
 * instances should be shared when possible. See the `MakeConnection()` method
 * and the `Connection` interface for more details.
 *
 * @par Thread Safety
 *
 * Instances of this class created via copy-construction or copy-assignment
 * share the underlying pool of connections. Access to these copies via multiple
 * threads is guaranteed to work. Two threads operating on the same instance of
 * this class is not guaranteed to work.
 *
 * @par Error Handling
 *
 * This class uses `StatusOr<T>` to report errors. When an operation fails to
 * perform its work the returned `StatusOr<T>` contains the error details. If
 * the `ok()` member function in the `StatusOr<T>` returns `true` then it
 * contains the expected result. For more information, see the
 * [Error Handling Guide](#spanner-error-handling).
 *
 * @code
 * namespace spanner = ::google::cloud::spanner;
 *
 * auto db = spanner::Database("my_project", "my_instance", "my_db_id"));
 * auto conn = spanner::MakeConnection(db);
 * auto client = spanner::Client(conn);
 *
 * auto rows = client.Read(...);
 * using RowType = std::tuple<std::int64_t, std::string>;
 * for (auto const& row : spanner::StreamOf<RowType>(rows)) {
 *   // ...
 * }
 * @endcode
 *
 * @par Query Options
 *
 * Most operations that take an `SqlStatement` may also be modified with
 * query `Options`. These options can be set at various levels, with more
 * specific levels taking precedence over broader ones. For example,
 * `Options` that are passed directly to `Client::ExecuteQuery()` will
 * take precedence over the `Client`-level defaults (if any), which will
 * themselves take precedence over any environment variables. The following
 * table shows the environment variables that may optionally be set and the
 * query `Options` setting that they affect.
 *
 * Environment Variable                   | Options setting
 * -------------------------------------- | --------------------
 * `SPANNER_OPTIMIZER_VERSION`            | `QueryOptimizerVersionOption`
 * `SPANNER_OPTIMIZER_STATISTICS_PACKAGE` | `QueryOptimizerStatisticsPackageOption`
 *
 * @see https://cloud.google.com/spanner/docs/reference/rest/v1/QueryOptions
 * @see http://cloud/spanner/docs/query-optimizer/manage-query-optimizer
 *
 * [spanner-doc-link]:
 * https://cloud.google.com/spanner/docs/api-libraries-overview
 */
// clang-format on
class Client {
 public:
  /**
   * Constructs a `Client` object using the specified @p conn and @p opts.
   *
   * See `MakeConnection()` for how to create a connection to Spanner. To help
   * with unit testing, callers may create fake/mock `Connection` objects that
   * are injected into the `Client`.
   */
  explicit Client(std::shared_ptr<DataConnection> conn, Options opts = {})
      : conn_(std::move(conn)),
        options_(google::cloud::internal::MergeOptions(std::move(opts),
                                                       conn_->options())) {}

  /// No default construction.
  Client() = delete;

  ///@{
  /// @name Copy and move support
  Client(Client const&) = default;
  Client& operator=(Client const&) = default;
  Client(Client&&) = default;
  Client& operator=(Client&&) = default;
  ///@}

  ///@{
  /// @name Equality
  friend bool operator==(Client const& a, Client const& b) {
    return a.conn_ == b.conn_;
  }
  friend bool operator!=(Client const& a, Client const& b) { return !(a == b); }
  ///@}

  StatusOr<PreparedQuery> PrepareQuery(InstanceResource instance,
                                       SqlStatement statement,
                                       Options opts = {});
  future<StatusOr<PreparedQuery>> AsyncPrepareQuery(InstanceResource instance,
                                                    SqlStatement statement,
                                                    Options opts = {});

  RowStream ExecuteQuery(PreparedQuery prepared_query, Options opts = {});
  RowStream ExecuteQuery(BoundQuery&& bound_query, Options opts = {});

 private:
  std::shared_ptr<DataConnection> conn_;
  Options options_;
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigtable
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BIGTABLE_CLIENT_H
