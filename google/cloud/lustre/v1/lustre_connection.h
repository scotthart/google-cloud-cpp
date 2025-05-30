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
// source: google/cloud/lustre/v1/lustre.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_LUSTRE_V1_LUSTRE_CONNECTION_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_LUSTRE_V1_LUSTRE_CONNECTION_H

#include "google/cloud/lustre/v1/internal/lustre_retry_traits.h"
#include "google/cloud/lustre/v1/lustre_connection_idempotency_policy.h"
#include "google/cloud/backoff_policy.h"
#include "google/cloud/future.h"
#include "google/cloud/internal/retry_policy_impl.h"
#include "google/cloud/no_await_tag.h"
#include "google/cloud/options.h"
#include "google/cloud/polling_policy.h"
#include "google/cloud/status_or.h"
#include "google/cloud/stream_range.h"
#include "google/cloud/version.h"
#include <google/cloud/lustre/v1/lustre.pb.h>
#include <google/longrunning/operations.grpc.pb.h>
#include <memory>

namespace google {
namespace cloud {
namespace lustre_v1 {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

/// The retry policy for `LustreConnection`.
class LustreRetryPolicy : public ::google::cloud::RetryPolicy {
 public:
  /// Creates a new instance of the policy, reset to the initial state.
  virtual std::unique_ptr<LustreRetryPolicy> clone() const = 0;
};

/**
 * A retry policy for `LustreConnection` based on counting errors.
 *
 * This policy stops retrying if:
 * - An RPC returns a non-transient error.
 * - More than a prescribed number of transient failures is detected.
 *
 * In this class the following status codes are treated as transient errors:
 * - [`kUnavailable`](@ref google::cloud::StatusCode)
 */
class LustreLimitedErrorCountRetryPolicy : public LustreRetryPolicy {
 public:
  /**
   * Create an instance that tolerates up to @p maximum_failures transient
   * errors.
   *
   * @note Disable the retry loop by providing an instance of this policy with
   *     @p maximum_failures == 0.
   */
  explicit LustreLimitedErrorCountRetryPolicy(int maximum_failures)
      : impl_(maximum_failures) {}

  LustreLimitedErrorCountRetryPolicy(
      LustreLimitedErrorCountRetryPolicy&& rhs) noexcept
      : LustreLimitedErrorCountRetryPolicy(rhs.maximum_failures()) {}
  LustreLimitedErrorCountRetryPolicy(
      LustreLimitedErrorCountRetryPolicy const& rhs) noexcept
      : LustreLimitedErrorCountRetryPolicy(rhs.maximum_failures()) {}

  int maximum_failures() const { return impl_.maximum_failures(); }

  bool OnFailure(Status const& status) override {
    return impl_.OnFailure(status);
  }
  bool IsExhausted() const override { return impl_.IsExhausted(); }
  bool IsPermanentFailure(Status const& status) const override {
    return impl_.IsPermanentFailure(status);
  }
  std::unique_ptr<LustreRetryPolicy> clone() const override {
    return std::make_unique<LustreLimitedErrorCountRetryPolicy>(
        maximum_failures());
  }

  // This is provided only for backwards compatibility.
  using BaseType = LustreRetryPolicy;

 private:
  google::cloud::internal::LimitedErrorCountRetryPolicy<
      lustre_v1_internal::LustreRetryTraits>
      impl_;
};

/**
 * A retry policy for `LustreConnection` based on elapsed time.
 *
 * This policy stops retrying if:
 * - An RPC returns a non-transient error.
 * - The elapsed time in the retry loop exceeds a prescribed duration.
 *
 * In this class the following status codes are treated as transient errors:
 * - [`kUnavailable`](@ref google::cloud::StatusCode)
 */
class LustreLimitedTimeRetryPolicy : public LustreRetryPolicy {
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
  explicit LustreLimitedTimeRetryPolicy(
      std::chrono::duration<DurationRep, DurationPeriod> maximum_duration)
      : impl_(maximum_duration) {}

  LustreLimitedTimeRetryPolicy(LustreLimitedTimeRetryPolicy&& rhs) noexcept
      : LustreLimitedTimeRetryPolicy(rhs.maximum_duration()) {}
  LustreLimitedTimeRetryPolicy(LustreLimitedTimeRetryPolicy const& rhs) noexcept
      : LustreLimitedTimeRetryPolicy(rhs.maximum_duration()) {}

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
  std::unique_ptr<LustreRetryPolicy> clone() const override {
    return std::make_unique<LustreLimitedTimeRetryPolicy>(maximum_duration());
  }

  // This is provided only for backwards compatibility.
  using BaseType = LustreRetryPolicy;

 private:
  google::cloud::internal::LimitedTimeRetryPolicy<
      lustre_v1_internal::LustreRetryTraits>
      impl_;
};

/**
 * The `LustreConnection` object for `LustreClient`.
 *
 * This interface defines virtual methods for each of the user-facing overload
 * sets in `LustreClient`. This allows users to inject custom behavior
 * (e.g., with a Google Mock object) when writing tests that use objects of type
 * `LustreClient`.
 *
 * To create a concrete instance, see `MakeLustreConnection()`.
 *
 * For mocking, see `lustre_v1_mocks::MockLustreConnection`.
 */
class LustreConnection {
 public:
  virtual ~LustreConnection() = 0;

  virtual Options options() { return Options{}; }

  virtual StreamRange<google::cloud::lustre::v1::Instance> ListInstances(
      google::cloud::lustre::v1::ListInstancesRequest request);

  virtual StatusOr<google::cloud::lustre::v1::Instance> GetInstance(
      google::cloud::lustre::v1::GetInstanceRequest const& request);

  virtual future<StatusOr<google::cloud::lustre::v1::Instance>> CreateInstance(
      google::cloud::lustre::v1::CreateInstanceRequest const& request);

  virtual StatusOr<google::longrunning::Operation> CreateInstance(
      NoAwaitTag,
      google::cloud::lustre::v1::CreateInstanceRequest const& request);

  virtual future<StatusOr<google::cloud::lustre::v1::Instance>> CreateInstance(
      google::longrunning::Operation const& operation);

  virtual future<StatusOr<google::cloud::lustre::v1::Instance>> UpdateInstance(
      google::cloud::lustre::v1::UpdateInstanceRequest const& request);

  virtual StatusOr<google::longrunning::Operation> UpdateInstance(
      NoAwaitTag,
      google::cloud::lustre::v1::UpdateInstanceRequest const& request);

  virtual future<StatusOr<google::cloud::lustre::v1::Instance>> UpdateInstance(
      google::longrunning::Operation const& operation);

  virtual future<StatusOr<google::cloud::lustre::v1::OperationMetadata>>
  DeleteInstance(
      google::cloud::lustre::v1::DeleteInstanceRequest const& request);

  virtual StatusOr<google::longrunning::Operation> DeleteInstance(
      NoAwaitTag,
      google::cloud::lustre::v1::DeleteInstanceRequest const& request);

  virtual future<StatusOr<google::cloud::lustre::v1::OperationMetadata>>
  DeleteInstance(google::longrunning::Operation const& operation);

  virtual future<StatusOr<google::cloud::lustre::v1::ImportDataResponse>>
  ImportData(google::cloud::lustre::v1::ImportDataRequest const& request);

  virtual StatusOr<google::longrunning::Operation> ImportData(
      NoAwaitTag, google::cloud::lustre::v1::ImportDataRequest const& request);

  virtual future<StatusOr<google::cloud::lustre::v1::ImportDataResponse>>
  ImportData(google::longrunning::Operation const& operation);

  virtual future<StatusOr<google::cloud::lustre::v1::ExportDataResponse>>
  ExportData(google::cloud::lustre::v1::ExportDataRequest const& request);

  virtual StatusOr<google::longrunning::Operation> ExportData(
      NoAwaitTag, google::cloud::lustre::v1::ExportDataRequest const& request);

  virtual future<StatusOr<google::cloud::lustre::v1::ExportDataResponse>>
  ExportData(google::longrunning::Operation const& operation);

  virtual StreamRange<google::cloud::location::Location> ListLocations(
      google::cloud::location::ListLocationsRequest request);

  virtual StatusOr<google::cloud::location::Location> GetLocation(
      google::cloud::location::GetLocationRequest const& request);

  virtual StreamRange<google::longrunning::Operation> ListOperations(
      google::longrunning::ListOperationsRequest request);

  virtual StatusOr<google::longrunning::Operation> GetOperation(
      google::longrunning::GetOperationRequest const& request);

  virtual Status DeleteOperation(
      google::longrunning::DeleteOperationRequest const& request);

  virtual Status CancelOperation(
      google::longrunning::CancelOperationRequest const& request);
};

/**
 * A factory function to construct an object of type `LustreConnection`.
 *
 * The returned connection object should not be used directly; instead it
 * should be passed as an argument to the constructor of LustreClient.
 *
 * The optional @p options argument may be used to configure aspects of the
 * returned `LustreConnection`. Expected options are any of the types in
 * the following option lists:
 *
 * - `google::cloud::CommonOptionList`
 * - `google::cloud::GrpcOptionList`
 * - `google::cloud::UnifiedCredentialsOptionList`
 * - `google::cloud::lustre_v1::LustrePolicyOptionList`
 *
 * @note Unexpected options will be ignored. To log unexpected options instead,
 *     set `GOOGLE_CLOUD_CPP_ENABLE_CLOG=yes` in the environment.
 *
 * @param options (optional) Configure the `LustreConnection` created by
 * this function.
 */
std::shared_ptr<LustreConnection> MakeLustreConnection(Options options = {});

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace lustre_v1
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_LUSTRE_V1_LUSTRE_CONNECTION_H
