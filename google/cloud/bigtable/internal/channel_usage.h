// Copyright 2026 Google LLC
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

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BIGTABLE_INTERNAL_CHANNEL_USAGE_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BIGTABLE_INTERNAL_CHANNEL_USAGE_H

#include "google/cloud/internal/clock.h"
#include "google/cloud/status_or.h"
#include "google/cloud/version.h"
#include <chrono>
#include <deque>
#include <memory>
#include <mutex>
#include <utility>

namespace google {
namespace cloud {
namespace bigtable_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

// This class wraps a `T`, typically a BigtableStub, and tracks the number of
// outstanding RPCs by taking measurements when the wrapped stub is acquired
// and released.
template <typename T>
class ChannelUsage : public std::enable_shared_from_this<ChannelUsage<T>> {
 public:
  using Clock = ::google::cloud::internal::SteadyClock;
  ChannelUsage() = default;
  explicit ChannelUsage(std::shared_ptr<T> stub, std::shared_ptr<Clock> clock =
                                                     std::make_shared<Clock>())
      : stub_(std::move(stub)), clock_(std::move(clock)) {}

  // Computes the weighted average of outstanding RPCs on the channel over the
  // past 60 seconds.
  StatusOr<int> average_outstanding_rpcs() {
    auto constexpr kWindowSeconds = 60;
    auto constexpr kWindowDuration = std::chrono::seconds(kWindowSeconds);
    std::scoped_lock lk(mu_);
    if (!last_refresh_status_.ok()) return last_refresh_status_;
    // If there are no measurements then the stub has never been used.
    if (measurements_.empty()) return 0;
    auto now = clock_->Now();
    auto last_time = now;
    auto window_start = now - kWindowDuration;

    double sum = 0.0;
    double total_weight = 0.0;
    auto iter = measurements_.rbegin();
    while (iter != measurements_.rend() && iter->timestamp >= window_start) {
      double weight =
          std::chrono::duration<double>(last_time - iter->timestamp).count();
      last_time = iter->timestamp;
      sum += iter->outstanding_rpcs * weight;
      total_weight += weight;
      ++iter;
    }

    // It's unlikely we will have a measurement at precisely the beginning of
    // the window. So, we need to use the first measurement outside the window
    // to compute a measurement for the missing part of the window using a
    // weight equal to the missing time.
    if (iter != measurements_.rend()) {
      double weight = std::max(0.0, kWindowSeconds - total_weight);
      sum += iter->outstanding_rpcs * weight;
      total_weight += weight;
      // We want to keep one measurement that's at least 60s old to provide a
      // starting value for the next window.
      ++iter;
    }

    if (measurements_.size() > 1) {
      measurements_.erase(measurements_.begin(), iter.base());
    }
    // After iterating through the measurements if the total_weight is zero,
    // then all of the measurements occurred at time == now, and returning the
    // current number of outstanding RPCs is most correct.
    return total_weight == 0.0 ? outstanding_rpcs_
                               : static_cast<int>(sum / total_weight);
  }

  StatusOr<int> instant_outstanding_rpcs() {
    std::scoped_lock lk(mu_);
    if (!last_refresh_status_.ok()) return last_refresh_status_;
    return outstanding_rpcs_;
  }

  ChannelUsage& set_last_refresh_status(Status s) {
    std::scoped_lock lk(mu_);
    last_refresh_status_ = std::move(s);
    return *this;
  }

  // A channel can only be set if the current value is nullptr. This mutator
  // exists only so that we can obtain a std::weak_ptr to the ChannelUsage
  // object that will eventually hold the channel.
  ChannelUsage& set_stub(std::shared_ptr<T> stub) {
    std::scoped_lock lk(mu_);
    if (!stub_) stub_ = std::move(stub);
    return *this;
  }

  std::weak_ptr<ChannelUsage<T>> MakeWeak() { return this->shared_from_this(); }

  std::shared_ptr<T> AcquireStub() {
    std::scoped_lock lk(mu_);
    ++outstanding_rpcs_;
    auto time = clock_->Now();
    measurements_.emplace_back(outstanding_rpcs_, time);
    return stub_;
  }

  void ReleaseStub() {
    std::scoped_lock lk(mu_);
    --outstanding_rpcs_;
    measurements_.emplace_back(outstanding_rpcs_, clock_->Now());
  }

 private:
  mutable std::mutex mu_;
  std::shared_ptr<T> stub_;
  std::shared_ptr<Clock> clock_ = std::make_shared<Clock>();
  int outstanding_rpcs_ = 0;
  Status last_refresh_status_;
  struct Measurement {
    Measurement(int outstanding_rpcs, std::chrono::steady_clock::time_point p)
        : outstanding_rpcs(outstanding_rpcs), timestamp(p) {}
    int outstanding_rpcs;
    std::chrono::steady_clock::time_point timestamp;
  };
  // Older measurements are removed as part of the average_outstanding_rpcs
  // method.
  std::deque<Measurement> measurements_;
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigtable_internal
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BIGTABLE_INTERNAL_CHANNEL_USAGE_H
