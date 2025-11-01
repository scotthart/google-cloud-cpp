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
#include "google/cloud/internal/make_status.h"
#include "google/cloud/internal/time_utils.h"
#include "google/cloud/testing_util/fake_clock.h"
#include "google/cloud/testing_util/fake_completion_queue_impl.h"
#include "google/cloud/testing_util/is_proto_equal.h"
#include "google/cloud/testing_util/mock_completion_queue_impl.h"
#include "google/cloud/testing_util/status_matchers.h"
#include <google/bigtable/v2/data.pb.h>
#include <google/protobuf/text_format.h>
#include <google/protobuf/util/time_util.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <future>
#include <thread>

namespace google {
namespace cloud {
namespace bigtable_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN
namespace {

using ::google::cloud::internal::ToProtoTimestamp;
using ::google::cloud::testing_util::FakeCompletionQueueImpl;
using ::google::cloud::testing_util::FakeSystemClock;
using ::google::cloud::testing_util::IsProtoEqual;
using ::google::cloud::testing_util::MockCompletionQueueImpl;
using ::google::cloud::testing_util::StatusIs;
using ::google::protobuf::util::TimeUtil;

TEST(QueryPlanTest, ResponseDataAccessor) {
  auto mock_cq = std::make_shared<MockCompletionQueueImpl>();
  promise<StatusOr<std::chrono::system_clock::time_point>> deadline;
  EXPECT_CALL(*mock_cq, MakeDeadlineTimer)
      .WillOnce([&](std::chrono::system_clock::time_point)
                    -> future<StatusOr<std::chrono::system_clock::time_point>> {
        return deadline.get_future();
      });

  CompletionQueue cq(mock_cq);
  google::bigtable::v2::PrepareQueryResponse response;
  response.set_prepared_query("test-query");
  auto constexpr kResultMetadataText = R"pb(
    proto_schema {
      columns {
        name: "user_id"
        type { string_type {} }
      }
    }
  )pb";
  google::bigtable::v2::ResultSetMetadata metadata;
  ASSERT_TRUE(google::protobuf::TextFormat::ParseFromString(kResultMetadataText,
                                                            &metadata));
  *response.mutable_metadata() = metadata;
  *response.mutable_valid_until() =
      TimeUtil::GetCurrentTime() + TimeUtil::SecondsToDuration(300);

  auto plan = QueryPlan::Create(cq, response, [] {
    return make_ready_future(
        make_status_or(google::bigtable::v2::PrepareQueryResponse{}));
  });

  auto response_data = plan->response_data();
  ASSERT_STATUS_OK(response_data);
  EXPECT_EQ(response_data->prepared_query, "test-query");
  EXPECT_THAT(response_data->metadata, IsProtoEqual(metadata));
}

TEST(QueryPlanTest, RefreshExpiredPlan) {
  auto fake_cq_impl = std::make_shared<FakeCompletionQueueImpl>();
  auto fake_clock = std::make_shared<FakeSystemClock>();
  auto now = std::chrono::system_clock::now();
  fake_clock->SetTime(now);

  google::bigtable::v2::PrepareQueryResponse refresh_response;
  refresh_response.set_prepared_query("refreshed-query-plan");
  auto refresh_fn = [&]() {
    return make_ready_future(make_status_or(refresh_response));
  };

  google::bigtable::v2::PrepareQueryResponse response;
  response.set_prepared_query("original-query-plan");
  *response.mutable_valid_until() =
      ToProtoTimestamp(now + std::chrono::seconds(600));

  auto query_plan = QueryPlan::Create(CompletionQueue(fake_cq_impl), response,
                                      refresh_fn, fake_clock);

  auto data = query_plan->response_data();
  ASSERT_STATUS_OK(data);
  EXPECT_EQ(data->prepared_query, "original-query-plan");

  fake_clock->AdvanceTime(std::chrono::seconds(500));
  fake_cq_impl->SimulateCompletion(true);

  data = query_plan->response_data();
  ASSERT_STATUS_OK(data);
  EXPECT_EQ(data->prepared_query, "refreshed-query-plan");

  // Cancel all pending operations, satisfying any remaining futures.
  fake_cq_impl->SimulateCompletion(false);
}

TEST(QueryPlanTest, ReturnExistingPlanWhileRefreshing) {
  auto fake_cq_impl = std::make_shared<FakeCompletionQueueImpl>();
  auto fake_clock = std::make_shared<FakeSystemClock>();
  auto now = std::chrono::system_clock::now();
  fake_clock->SetTime(now);

  promise<void> wait_to_respond;
  auto f = std::make_shared<future<void>>(wait_to_respond.get_future());
  google::bigtable::v2::PrepareQueryResponse refresh_response;
  refresh_response.set_prepared_query("refreshed-query-plan");
  auto refresh_fn = [&]() {
    f->get();
    return make_ready_future(make_status_or(refresh_response));
  };

  google::bigtable::v2::PrepareQueryResponse response;
  response.set_prepared_query("original-query-plan");
  *response.mutable_valid_until() =
      ToProtoTimestamp(now + std::chrono::seconds(600));

  auto query_plan = QueryPlan::Create(CompletionQueue(fake_cq_impl), response,
                                      refresh_fn, fake_clock);

  auto data = query_plan->response_data();
  ASSERT_STATUS_OK(data);
  EXPECT_EQ(data->prepared_query, "original-query-plan");

  StatusOr<QueryPlan::ResponseData> while_refreshing;
  std::async(std::launch::async, [&]() {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    while_refreshing = query_plan->response_data();
    wait_to_respond.set_value();
  }).get();

  fake_clock->AdvanceTime(std::chrono::seconds(500));
  fake_cq_impl->SimulateCompletion(true);

  ASSERT_STATUS_OK(while_refreshing);
  EXPECT_EQ(while_refreshing->prepared_query, "original-query-plan");

  data = query_plan->response_data();
  ASSERT_STATUS_OK(data);
  EXPECT_EQ(data->prepared_query, "refreshed-query-plan");

  // Cancel all pending operations, satisfying any remaining futures.
  fake_cq_impl->SimulateCompletion(false);
}

TEST(QueryPlanTest, WaitForNewPlanWhileRefreshing) {
  auto fake_cq_impl = std::make_shared<FakeCompletionQueueImpl>();
  auto fake_clock = std::make_shared<FakeSystemClock>();
  auto now = std::chrono::system_clock::now();
  fake_clock->SetTime(now);

  promise<void> wait_to_respond;
  auto f = std::make_shared<future<void>>(wait_to_respond.get_future());
  StatusOr<google::bigtable::v2::PrepareQueryResponse> refresh_response;
  refresh_response = internal::InternalError("oops!");
  auto refresh_fn = [&]() {
    if (!refresh_response.ok()) {
      std::cout << "refresh returning error" << std::endl;
      return make_ready_future(refresh_response);
    }
    std::cout << "refresh waiting" << std::endl;
    f->get();
    std::cout << "refresh returning success" << std::endl;
    return make_ready_future(refresh_response);
  };

  google::bigtable::v2::PrepareQueryResponse response;
  response.set_prepared_query("original-query-plan");
  *response.mutable_valid_until() =
      ToProtoTimestamp(now + std::chrono::seconds(600));

  auto query_plan = QueryPlan::Create(CompletionQueue(fake_cq_impl), response,
                                      refresh_fn, fake_clock);

  auto data = query_plan->response_data();
  ASSERT_STATUS_OK(data);
  EXPECT_EQ(data->prepared_query, "original-query-plan");

  fake_clock->AdvanceTime(std::chrono::seconds(500));
  fake_cq_impl->SimulateCompletion(true);

  data = query_plan->response_data();
  EXPECT_THAT(data, StatusIs(StatusCode::kInternal, "oops!"));
#if 0
  std::cout << "EXPECT_THAT error" << std::endl;


  std::cout << "launch thread" << std::endl;
  StatusOr<QueryPlan::ResponseData> while_refreshing;
  std::async(std::launch::async, [&]() {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    refresh_response = google::bigtable::v2::PrepareQueryResponse{};
    refresh_response->set_prepared_query("refreshed-query-plan");

    wait_to_respond.set_value();
    while_refreshing = query_plan->response_data();

  }).get();
  data = query_plan->response_data();

  ASSERT_STATUS_OK(while_refreshing);
  EXPECT_EQ(while_refreshing->prepared_query, "refreshed-query-plan");


  ASSERT_STATUS_OK(data);
  EXPECT_EQ(data->prepared_query, "refreshed-query-plan");
#endif
  // Cancel all pending operations, satisfying any remaining futures.
  fake_cq_impl->SimulateCompletion(false);
}

}  // namespace
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigtable_internal
}  // namespace cloud
}  // namespace google
