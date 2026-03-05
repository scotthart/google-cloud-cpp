// Copyright 2020 Google LLC
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

#include "google/cloud/bigtable/internal/connection_refresh_state.h"
#include "google/cloud/bigtable/testing/mock_bigtable_stub.h"
#include "google/cloud/testing_util/fake_completion_queue_impl.h"
#include "google/cloud/testing_util/mock_completion_queue_impl.h"
#include "google/cloud/testing_util/status_matchers.h"
#include <gmock/gmock.h>
#include <thread>

namespace google {
namespace cloud {
namespace bigtable_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

using ::google::cloud::bigtable::testing::MockBigtableStub;
using ::google::cloud::testing_util::FakeCompletionQueueImpl;
using ::google::cloud::testing_util::IsOk;
using ::google::cloud::testing_util::MockCompletionQueueImpl;
using ::testing::Eq;

using TimerFuture = future<StatusOr<std::chrono::system_clock::time_point>>;

class OutstandingTimersTest : public ::testing::Test {
 public:
  OutstandingTimersTest() : thread_([this] { cq_.Run(); }) {}
  ~OutstandingTimersTest() override {
    cq_.Shutdown();
    thread_.join();
  }

 protected:
  CompletionQueue cq_;
  std::thread thread_;
};

TEST_F(OutstandingTimersTest, Trivial) {
  // With MSVC 2019 (19.28.29334) the value from make_shared<>
  // must be captured.
  auto unused = std::make_shared<OutstandingTimers>(
      internal::GetCompletionQueueImpl(cq_));
}

TEST_F(OutstandingTimersTest, TimerFinishes) {
  auto registry = std::make_shared<OutstandingTimers>(
      internal::GetCompletionQueueImpl(cq_));
  promise<void> continuation_promise;
  auto t = cq_.MakeRelativeTimer(std::chrono::milliseconds(2))
               .then([&](TimerFuture fut) {
                 EXPECT_STATUS_OK(fut.get());
                 continuation_promise.set_value();
               });
  registry->RegisterTimer(std::move(t));
  continuation_promise.get_future().get();
  // This should be a noop.
  registry->CancelAll();
  // Calling it twice shouldn't hurt.
  registry->CancelAll();
}

TEST_F(OutstandingTimersTest, TimerIsCancelled) {
  auto registry = std::make_shared<OutstandingTimers>(
      internal::GetCompletionQueueImpl(cq_));
  promise<void> continuation_promise;
  auto t =
      cq_.MakeRelativeTimer(std::chrono::hours(10)).then([&](TimerFuture fut) {
        auto res = fut.get();
        EXPECT_FALSE(res);
        EXPECT_EQ(StatusCode::kCancelled, res.status().code());
        continuation_promise.set_value();
      });
  registry->RegisterTimer(std::move(t));
  registry->CancelAll();
  continuation_promise.get_future().get();
}

TEST_F(OutstandingTimersTest, TimerOutlivesRegistry) {
  auto registry = std::make_shared<OutstandingTimers>(
      internal::GetCompletionQueueImpl(cq_));
  promise<void> continuation_promise;
  auto t = cq_.MakeRelativeTimer(std::chrono::milliseconds(10))
               .then([&](TimerFuture fut) {
                 auto res = fut.get();
                 EXPECT_STATUS_OK(res);
                 continuation_promise.set_value();
               });
  registry->RegisterTimer(std::move(t));
  registry.reset();
  continuation_promise.get_future().get();
}

TEST_F(OutstandingTimersTest, TimerRegisteredAfterCancelAllGetCancelled) {
  auto registry = std::make_shared<OutstandingTimers>(
      internal::GetCompletionQueueImpl(cq_));
  promise<void> continuation_promise;
  auto t =
      cq_.MakeRelativeTimer(std::chrono::hours(10)).then([&](TimerFuture fut) {
        auto res = fut.get();
        EXPECT_FALSE(res);
        EXPECT_EQ(StatusCode::kCancelled, res.status().code());
        continuation_promise.set_value();
      });
  registry->CancelAll();
  registry->RegisterTimer(std::move(t));
  continuation_promise.get_future().get();
}

TEST(ConnectionRefreshState, Enabled) {
  using ms = std::chrono::milliseconds;
  ConnectionRefreshState state(nullptr, ms(0), ms(1000));
  EXPECT_TRUE(state.enabled());
}

TEST(ConnectionRefreshState, Disabled) {
  using ms = std::chrono::milliseconds;
  ConnectionRefreshState state(nullptr, ms(0), ms(0));
  EXPECT_FALSE(state.enabled());
}

class ScheduleStubRefreshTest : public ::testing::Test {
 public:
  ScheduleStubRefreshTest()
      : thread1_([this] {
          std::cout << "thread1_=" << std::this_thread::get_id() << std::endl;
          cq_.Run();
        }) {}
  //     thread2_([this] {
  //       std::this_thread::sleep_for(std::chrono::milliseconds(2));
  //
  //           std::cout << "thread2_=" << std::this_thread::get_id() <<
  //           std::endl;
  // cq_.Run();
  //     }) {}
  ~ScheduleStubRefreshTest() override {
    cq_.Shutdown();
    thread1_.join();
    // thread2_.join();
  }

 protected:
  CompletionQueue cq_;
  std::thread thread1_;
  // std::thread thread2_;
};

TEST_F(ScheduleStubRefreshTest, Success) {
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
  std::cout << "test_thread=" << std::this_thread::get_id() << std::endl;

  std::chrono::milliseconds min_conn_refresh_period(
      std::chrono::milliseconds(1));
  std::chrono::milliseconds max_conn_refresh_period(
      std::chrono::milliseconds(2));

  auto cq_impl = internal::GetCompletionQueueImpl(cq_);
  // auto fake_cq_impl = std::make_shared<FakeCompletionQueueImpl>();
  // auto mock_cq_impl = std::make_shared<MockCompletionQueueImpl>();

  auto refresh_state = std::make_shared<ConnectionRefreshState>(
      cq_impl, min_conn_refresh_period, max_conn_refresh_period);
  std::string instance_name = "projects/my-project/instances/my-instance";

  std::promise<void> p;
  auto f = p.get_future();

  google::cloud::promise<StatusOr<google::bigtable::v2::PingAndWarmResponse>>
      p2;

  auto mock_stub = std::make_shared<MockBigtableStub>();
  EXPECT_CALL(*mock_stub, AsyncPingAndWarm)
      .WillRepeatedly(
          [&](CompletionQueue&, std::shared_ptr<grpc::ClientContext>,
              google::cloud::internal::ImmutableOptions,
              google::bigtable::v2::PingAndWarmRequest const& request)
              -> future<StatusOr<google::bigtable::v2::PingAndWarmResponse>> {
            std::cout << "mock_stub.PingAndWarm thread="
                      << std::this_thread::get_id() << std::endl;
            EXPECT_THAT(request.name(), Eq(instance_name));
            return p2.get_future();
            // return make_ready_future(
            //     StatusOr<google::bigtable::v2::PingAndWarmResponse>(Status{}));
          });

  // auto connection_status_fn = [](Status const& s) -> void {
  //   std::cout << "connection_status_fn" << std::endl;
  //   EXPECT_THAT(s, IsOk());
  // };

  ::testing::MockFunction<void(Status const&)> mock_fn;
  EXPECT_CALL(mock_fn, Call)
  //     .Times(::testing::AtLeast(1));
      .WillOnce([&p](Status const&) -> void { p.set_value(); });

  ScheduleStubRefresh(cq_impl, refresh_state, mock_stub, instance_name,
                      mock_fn.AsStdFunction());
  p2.set_value(google::bigtable::v2::PingAndWarmResponse{});

  f.get();
  // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  // std::this_thread::sleep_for(std::chrono::milliseconds(5000));

  // fake_cq_impl->SimulateCompletion(true);
  // cq_impl->CancelAll();
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigtable_internal
}  // namespace cloud
}  // namespace google
