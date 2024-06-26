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
// source: google/cloud/sql/v1/cloud_sql_operations.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_SQL_V1_SQL_OPERATIONS_CONNECTION_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_SQL_V1_SQL_OPERATIONS_CONNECTION_H

#include "google/cloud/sql/v1/internal/sql_operations_retry_traits.h"
#include "google/cloud/sql/v1/sql_operations_connection_idempotency_policy.h"
#include "google/cloud/backoff_policy.h"
#include "google/cloud/experimental_tag.h"
#include "google/cloud/internal/retry_policy_impl.h"
#include "google/cloud/options.h"
#include "google/cloud/status_or.h"
#include "google/cloud/stream_range.h"
#include "google/cloud/version.h"
#include <google/cloud/sql/v1/cloud_sql_operations.pb.h>
#include <memory>

namespace google {
namespace cloud {
namespace sql_v1 {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

/// The retry policy for `SqlOperationsServiceConnection`.
class SqlOperationsServiceRetryPolicy : public ::google::cloud::RetryPolicy {
 public:
  /// Creates a new instance of the policy, reset to the initial state.
  virtual std::unique_ptr<SqlOperationsServiceRetryPolicy> clone() const = 0;
};

/**
 * A retry policy for `SqlOperationsServiceConnection` based on counting errors.
 *
 * This policy stops retrying if:
 * - An RPC returns a non-transient error.
 * - More than a prescribed number of transient failures is detected.
 *
 * In this class the following status codes are treated as transient errors:
 * - [`kUnavailable`](@ref google::cloud::StatusCode)
 */
class SqlOperationsServiceLimitedErrorCountRetryPolicy
    : public SqlOperationsServiceRetryPolicy {
 public:
  /**
   * Create an instance that tolerates up to @p maximum_failures transient
   * errors.
   *
   * @note Disable the retry loop by providing an instance of this policy with
   *     @p maximum_failures == 0.
   */
  explicit SqlOperationsServiceLimitedErrorCountRetryPolicy(
      int maximum_failures)
      : impl_(maximum_failures) {}

  SqlOperationsServiceLimitedErrorCountRetryPolicy(
      SqlOperationsServiceLimitedErrorCountRetryPolicy&& rhs) noexcept
      : SqlOperationsServiceLimitedErrorCountRetryPolicy(
            rhs.maximum_failures()) {}
  SqlOperationsServiceLimitedErrorCountRetryPolicy(
      SqlOperationsServiceLimitedErrorCountRetryPolicy const& rhs) noexcept
      : SqlOperationsServiceLimitedErrorCountRetryPolicy(
            rhs.maximum_failures()) {}

  int maximum_failures() const { return impl_.maximum_failures(); }

  bool OnFailure(Status const& status) override {
    return impl_.OnFailure(status);
  }
  bool IsExhausted() const override { return impl_.IsExhausted(); }
  bool IsPermanentFailure(Status const& status) const override {
    return impl_.IsPermanentFailure(status);
  }
  std::unique_ptr<SqlOperationsServiceRetryPolicy> clone() const override {
    return std::make_unique<SqlOperationsServiceLimitedErrorCountRetryPolicy>(
        maximum_failures());
  }

  // This is provided only for backwards compatibility.
  using BaseType = SqlOperationsServiceRetryPolicy;

 private:
  google::cloud::internal::LimitedErrorCountRetryPolicy<
      sql_v1_internal::SqlOperationsServiceRetryTraits>
      impl_;
};

/**
 * A retry policy for `SqlOperationsServiceConnection` based on elapsed time.
 *
 * This policy stops retrying if:
 * - An RPC returns a non-transient error.
 * - The elapsed time in the retry loop exceeds a prescribed duration.
 *
 * In this class the following status codes are treated as transient errors:
 * - [`kUnavailable`](@ref google::cloud::StatusCode)
 */
class SqlOperationsServiceLimitedTimeRetryPolicy
    : public SqlOperationsServiceRetryPolicy {
 public:
  /**
   * Constructor given a `std::chrono::duration<>` object.
   *
   * @tparam DurationRep a placeholder to match the `Rep` tparam for @p
   *     duration's type. The semantics of this template parameter are
   *     documented in `std::chrono::duration<>`. In brief, the underlying
   *     arithmetic type used to store the number of ticks. For our purposes it
   *     is simply a formal parameter.
   * @tparam DurationPeriod a placeholder to match the `Period` tparam for @p
   *     duration's type. The semantics of this template parameter are
   *     documented in `std::chrono::duration<>`. In brief, the length of the
   *     tick in seconds, expressed as a `std::ratio<>`. For our purposes it is
   *     simply a formal parameter.
   * @param maximum_duration the maximum time allowed before the policy expires.
   *     While the application can express this time in any units they desire,
   *     the class truncates to milliseconds.
   *
   * @see https://en.cppreference.com/w/cpp/chrono/duration for more information
   *     about `std::chrono::duration`.
   */
  template <typename DurationRep, typename DurationPeriod>
  explicit SqlOperationsServiceLimitedTimeRetryPolicy(
      std::chrono::duration<DurationRep, DurationPeriod> maximum_duration)
      : impl_(maximum_duration) {}

  SqlOperationsServiceLimitedTimeRetryPolicy(
      SqlOperationsServiceLimitedTimeRetryPolicy&& rhs) noexcept
      : SqlOperationsServiceLimitedTimeRetryPolicy(rhs.maximum_duration()) {}
  SqlOperationsServiceLimitedTimeRetryPolicy(
      SqlOperationsServiceLimitedTimeRetryPolicy const& rhs) noexcept
      : SqlOperationsServiceLimitedTimeRetryPolicy(rhs.maximum_duration()) {}

  std::chrono::milliseconds maximum_duration() const {
    return impl_.maximum_duration();
  }

  bool OnFailure(Status const& status) override {
    return impl_.OnFailure(status);
  }
  bool IsExhausted() const override { return impl_.IsExhausted(); }
  bool IsPermanentFailure(Status const& status) const override {
    return impl_.IsPermanentFailure(status);
  }
  std::unique_ptr<SqlOperationsServiceRetryPolicy> clone() const override {
    return std::make_unique<SqlOperationsServiceLimitedTimeRetryPolicy>(
        maximum_duration());
  }

  // This is provided only for backwards compatibility.
  using BaseType = SqlOperationsServiceRetryPolicy;

 private:
  google::cloud::internal::LimitedTimeRetryPolicy<
      sql_v1_internal::SqlOperationsServiceRetryTraits>
      impl_;
};

/**
 * The `SqlOperationsServiceConnection` object for `SqlOperationsServiceClient`.
 *
 * This interface defines virtual methods for each of the user-facing overload
 * sets in `SqlOperationsServiceClient`. This allows users to inject custom
 * behavior (e.g., with a Google Mock object) when writing tests that use
 * objects of type `SqlOperationsServiceClient`.
 *
 * To create a concrete instance, see `MakeSqlOperationsServiceConnection()`.
 *
 * For mocking, see `sql_v1_mocks::MockSqlOperationsServiceConnection`.
 */
class SqlOperationsServiceConnection {
 public:
  virtual ~SqlOperationsServiceConnection() = 0;

  virtual Options options() { return Options{}; }

  virtual StatusOr<google::cloud::sql::v1::Operation> Get(
      google::cloud::sql::v1::SqlOperationsGetRequest const& request);

  virtual StreamRange<google::cloud::sql::v1::Operation> List(
      google::cloud::sql::v1::SqlOperationsListRequest request);

  virtual Status Cancel(
      google::cloud::sql::v1::SqlOperationsCancelRequest const& request);
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace sql_v1
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_SQL_V1_SQL_OPERATIONS_CONNECTION_H
