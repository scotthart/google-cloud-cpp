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

#include "google/cloud/bigtable/internal/query_plan.h"
#include "google/cloud/completion_queue.h"
#include <google/bigtable/v2/data.pb.h>

namespace google {
namespace cloud {
namespace bigtable_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

std::shared_ptr<QueryPlan> QueryPlan::Create(
    CompletionQueue cq, google::bigtable::v2::PrepareQueryResponse response,
    RefreshFn fn) {
  auto plan = std::shared_ptr<QueryPlan>(
      new QueryPlan(std::move(cq), std::move(response), std::move(fn)));
  plan->Initialize();
  return plan;
}

void QueryPlan::Invalidate(Status status) {
  {
    std::unique_lock<std::mutex> lock(mu_);
    response_ = std::move(status);
    if (!IsRefreshing(lock)) {
      state_ = RefreshState::kBegin;
    }
  }
  RefreshQueryPlan();
}

bool QueryPlan::IsRefreshing(std::unique_lock<std::mutex> const&) const {
  return state_ == RefreshState::kBegin || state_ == RefreshState::kPending;
}

void QueryPlan::Initialize() {
  std::unique_lock<std::mutex> lock(mu_);
  ScheduleRefresh(lock);
}

// ScheduleRefresh should only be called after updating response_.
void QueryPlan::ScheduleRefresh(std::unique_lock<std::mutex> const&) {
  // TODO(sdhart): if we return here, what are the long term consequences for
  // future refreshes?
  if (!response_.ok()) return;
  // We want to start the refresh process before the query plan expires.
  auto constexpr kRefreshDeadlineOffset = 120;
  auto refresh_deadline =
      std::chrono::system_clock::time_point(
          std::chrono::seconds(response_->valid_until().seconds()) +
          std::chrono::nanoseconds(response_->valid_until().nanos())) -
      std::chrono::seconds(kRefreshDeadlineOffset);

  std::weak_ptr<QueryPlan> plan = shared_from_this();
  refresh_timer_ =
      cq_.MakeDeadlineTimer(refresh_deadline)
          .then([plan](future<StatusOr<std::chrono::system_clock::time_point>>
                           result) {
            if (result.get().ok()) {
              if (auto p = plan.lock()) {
                p->SetBeginState();
                p->RefreshQueryPlan();
              }
            }
          });
}

void QueryPlan::RefreshQueryPlan() {
  {
    std::unique_lock<std::mutex> lock(mu_);
    cond_.wait(lock, [this] { return state_ != RefreshState::kPending; });
    if (state_ == RefreshState::kDone) {
      return;
    }
    state_ = RefreshState::kPending;
  }
  auto response = refresh_fn_().get();
  bool done = false;
  {
    std::unique_lock<std::mutex> lock(mu_);
    response_ = std::move(response);
    if (response_.ok()) {
      done = true;
      // If we have to refresh an invalidated query plan, cancel any existing
      // timer before starting a new one.
      if (refresh_timer_.valid()) {
        refresh_timer_.cancel();
      }
      ScheduleRefresh(lock);
    }
  }
  if (done) {
    cond_.notify_all();
  } else {
    cond_.notify_one();
  }
}

void QueryPlan::SetBeginState() {
  std::lock_guard<std::mutex> lock(mu_);
  state_ = RefreshState::kBegin;
}

StatusOr<std::string> QueryPlan::prepared_query() {
  std::unique_lock<std::mutex> lock(mu_);
  if (IsRefreshing(lock) || !response_.ok()) {
    lock.unlock();
    RefreshQueryPlan();
    lock.lock();
  }

  if (state_ == RefreshState::kDone && !response_.ok()) {
    return response_.status();
  }
  return response_->prepared_query();
}

StatusOr<google::bigtable::v2::ResultSetMetadata> QueryPlan::metadata() {
  std::unique_lock<std::mutex> lock(mu_);
  if (IsRefreshing(lock) || !response_.ok()) {
    lock.unlock();
    RefreshQueryPlan();
    lock.lock();
  }

  if (state_ == RefreshState::kDone && !response_.ok()) {
    return response_.status();
  }
  return response_->metadata();
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigtable_internal
}  // namespace cloud
}  // namespace google
