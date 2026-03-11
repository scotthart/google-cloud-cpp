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

#include "google/cloud/bigtable/internal/dynamic_channel_pool.h"
#include "google/cloud/bigtable/testing/mock_bigtable_stub.h"
#include "google/cloud/internal/make_status.h"
#include "google/cloud/testing_util/fake_clock.h"
#include "google/cloud/testing_util/fake_completion_queue_impl.h"
#include "google/cloud/testing_util/mock_completion_queue_impl.h"
#include "google/cloud/testing_util/status_matchers.h"
#include <gmock/gmock.h>
#include <thread>

namespace google {
namespace cloud {
namespace bigtable_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

class DynamicChannelPoolTestWrapper {
 public:
  explicit DynamicChannelPoolTestWrapper(
      std::shared_ptr<DynamicChannelPool<BigtableStub>> pool)
      : pool_(std::move(pool)) {}

  std::shared_ptr<ChannelUsage<BigtableStub>> HandleBadChannels(
      std::scoped_lock<std::mutex> const& lk,
      DynamicChannelPool<BigtableStub>::ChannelSelectionData& d) {
    return pool_->HandleBadChannels(lk, d);
  }

  void ScheduleAddChannels(std::scoped_lock<std::mutex> const& lk) {
    pool_->ScheduleRemoveChannels(lk);
  }

  void AddChannels(std::vector<int> const& new_channel_ids) {
    pool_->AddChannels(new_channel_ids);
  }

  void ScheduleRemoveChannels(std::scoped_lock<std::mutex> const& lk) {
    pool_->ScheduleRemoveChannels(lk);
  }

  void RemoveChannels() { pool_->RemoveChannels(); }

  void EvictBadChannels(
      std::scoped_lock<std::mutex> const& lk,
      std::vector<typename std::vector<
          std::shared_ptr<ChannelUsage<BigtableStub>>>::iterator>&
          bad_channel_iters) {
    pool_->EvictBadChannels(lk, bad_channel_iters);
  }

  void SetSizeIncreaseCooldownTimer(std::scoped_lock<std::mutex> const& lk) {
    pool_->SetSizeIncreaseCooldownTimer(lk);
  }

  void SetSizeDecreaseCooldownTimer(std::scoped_lock<std::mutex> const& lk) {
    pool_->SetSizeDecreaseCooldownTimer(lk);
  }

  void CheckPoolChannelHealth(std::scoped_lock<std::mutex> const& lk) {
    pool_->CheckPoolChannelHealth(lk);
  }

 protected:
  std::shared_ptr<DynamicChannelPool<BigtableStub>> pool_;
};

namespace {

using ::google::cloud::bigtable::testing::MockBigtableStub;
using ::google::cloud::testing_util::FakeCompletionQueueImpl;
using ::google::cloud::testing_util::FakeSteadyClock;
// using ::google::cloud::testing_util::IsOkAndHolds;
using ::google::cloud::testing_util::MockCompletionQueueImpl;
// using ::google::cloud::testing_util::StatusIs;
using ::testing::Eq;
using ::testing::IsEmpty;
using ::testing::MockFunction;

class DynamicChannelPoolTest : public ::testing::Test {
 public:
  DynamicChannelPoolTest()
      : fake_cq_impl_(std::make_shared<FakeCompletionQueueImpl>()),
        mock_cq_impl_(std::make_shared<MockCompletionQueueImpl>()),
        fake_clock_impl_(std::make_shared<FakeSteadyClock>()),
        thread_([this] { cq_.Run(); }) {}

  ~DynamicChannelPoolTest() override {
    cq_.Shutdown();
    thread_.join();
  }

 protected:
  std::shared_ptr<FakeCompletionQueueImpl> fake_cq_impl_;
  std::shared_ptr<MockCompletionQueueImpl> mock_cq_impl_;
  std::shared_ptr<FakeSteadyClock> fake_clock_impl_;
  CompletionQueue cq_;
  std::thread thread_;
};

TEST_F(DynamicChannelPoolTest, SelectLeastUsedFromTwoChannels) {
  auto instance_name =
      bigtable::InstanceResource(Project("my-project"), "my-instance")
          .FullName();
  DynamicChannelPoolSizingPolicy sizing_policy;

  // There should be no attempt to grow the pool.
  EXPECT_CALL(*mock_cq_impl_, RunAsync).Times(0);
  auto refresh_state = std::make_shared<ConnectionRefreshState>(
      fake_cq_impl_, std::chrono::milliseconds(1),
      std::chrono::milliseconds(10));

  auto stub_factory_fn = [&](int, std::string const&, StubManager::Priming) {
    return std::make_shared<ChannelUsage<BigtableStub>>(
        std::make_shared<MockBigtableStub>(), fake_clock_impl_, 20);
  };

  std::vector<std::shared_ptr<ChannelUsage<BigtableStub>>> channels;
  auto mock_stub_0 = std::make_shared<MockBigtableStub>();
  EXPECT_CALL(*mock_stub_0, CheckAndMutateRow)
      .WillOnce([](grpc::ClientContext&, Options const&,
                   google::bigtable::v2::CheckAndMutateRowRequest const&) {
        google::bigtable::v2::CheckAndMutateRowResponse response;
        response.set_predicate_matched(true);
        return response;
      });
  auto mock_stub_1 = std::make_shared<MockBigtableStub>();
  EXPECT_CALL(*mock_stub_1, CheckAndMutateRow).Times(0);
  int initial_rpc_count = 0;
  channels.push_back(std::make_shared<ChannelUsage<BigtableStub>>(
      std::move(mock_stub_0), fake_clock_impl_, initial_rpc_count++));
  channels.push_back(std::make_shared<ChannelUsage<BigtableStub>>(
      std::move(mock_stub_1), fake_clock_impl_, initial_rpc_count));

  // Pool creation should set the pool size increase cooldown timer.
  EXPECT_CALL(*mock_cq_impl_, MakeRelativeTimer)
      .WillOnce([&](std::chrono::nanoseconds ns) {
        EXPECT_THAT(ns.count(),
                    Eq(std::chrono::nanoseconds(
                           sizing_policy.pool_size_decrease_cooldown_interval)
                           .count()));
        return make_ready_future(StatusOr(std::chrono::system_clock::now()));
      });

  sizing_policy.maximum_channel_pool_size = 2;
  sizing_policy.minimum_channel_pool_size = 2;
  auto pool = DynamicChannelPool<BigtableStub>::Create(
      instance_name, CompletionQueue(mock_cq_impl_), channels, refresh_state,
      stub_factory_fn, sizing_policy);
  auto selected_stub = pool->GetChannelRandomTwoLeastUsed();
  grpc::ClientContext context;
  auto response =
      selected_stub->AcquireStub()->CheckAndMutateRow(context, {}, {});
  ASSERT_STATUS_OK(response);
  EXPECT_TRUE(response->predicate_matched());

  fake_cq_impl_->SimulateCompletion(false);
}

TEST_F(DynamicChannelPoolTest, OneInitialChannel) {
  auto instance_name =
      bigtable::InstanceResource(Project("my-project"), "my-instance")
          .FullName();
  DynamicChannelPoolSizingPolicy sizing_policy;

  // There should be no attempt to grow the pool after creation.
  EXPECT_CALL(*mock_cq_impl_, RunAsync).Times(0);

  auto refresh_state = std::make_shared<ConnectionRefreshState>(
      fake_cq_impl_, std::chrono::milliseconds(1),
      std::chrono::milliseconds(10));

  {  // Pool created with 1 channel.
    auto mock_stub = std::make_shared<MockBigtableStub>();
    MockFunction<StatusOr<std::shared_ptr<ChannelUsage<BigtableStub>>>(
        std::uint32_t, std::string const&, StubManager::Priming)>
        stub_factory_fn;
    EXPECT_CALL(stub_factory_fn, Call).Times(0);
    // .WillOnce(::testing::Return(
    //     std::make_shared<ChannelUsage<BigtableStub>>(mock_stub)));

    std::vector<std::shared_ptr<ChannelUsage<BigtableStub>>> channels;
    auto mock_stub_0 = std::make_shared<MockBigtableStub>();
    EXPECT_CALL(*mock_stub_0, CheckAndMutateRow)
        .WillOnce([](grpc::ClientContext&, Options const&,
                     google::bigtable::v2::CheckAndMutateRowRequest const&) {
          google::bigtable::v2::CheckAndMutateRowResponse response;
          response.set_predicate_matched(true);
          return response;
        });

    int initial_rpc_count = 0;
    channels.push_back(std::make_shared<ChannelUsage<BigtableStub>>(
        std::move(mock_stub_0), fake_clock_impl_, initial_rpc_count));

    // Pool creation should set the pool size increase cooldown timer.
    EXPECT_CALL(*mock_cq_impl_, MakeRelativeTimer)
        .WillOnce([&](std::chrono::nanoseconds ns) {
          EXPECT_THAT(ns.count(),
                      Eq(std::chrono::nanoseconds(
                             sizing_policy.pool_size_decrease_cooldown_interval)
                             .count()));
          return cq_.MakeRelativeTimer(
              sizing_policy.pool_size_decrease_cooldown_interval);
        });

    sizing_policy.maximum_channel_pool_size = 1;
    sizing_policy.minimum_channel_pool_size = 1;
    auto pool = DynamicChannelPool<BigtableStub>::Create(
        instance_name, CompletionQueue(mock_cq_impl_), channels, refresh_state,
        stub_factory_fn.AsStdFunction(), sizing_policy);
    EXPECT_THAT(pool->size(), Eq(1));

    auto selected_stub = pool->GetChannelRandomTwoLeastUsed();
    grpc::ClientContext context;
    auto response =
        selected_stub->AcquireStub()->CheckAndMutateRow(context, {}, {});
    ASSERT_STATUS_OK(response);
    EXPECT_TRUE(response->predicate_matched());
  }

  fake_cq_impl_->SimulateCompletion(false);
}

TEST_F(DynamicChannelPoolTest, EmptyInitialPool) {
  auto instance_name =
      bigtable::InstanceResource(Project("my-project"), "my-instance")
          .FullName();
  DynamicChannelPoolSizingPolicy sizing_policy;

  // There should be no attempt to grow the pool after creation.
  EXPECT_CALL(*mock_cq_impl_, RunAsync).Times(0);
  auto refresh_state = std::make_shared<ConnectionRefreshState>(
      fake_cq_impl_, std::chrono::milliseconds(1),
      std::chrono::milliseconds(10));

  {  // Pool created with 0 channels.
    auto mock_stub = std::make_shared<MockBigtableStub>();
    EXPECT_CALL(*mock_stub, CheckAndMutateRow)
        .WillOnce([](grpc::ClientContext&, Options const&,
                     google::bigtable::v2::CheckAndMutateRowRequest const&) {
          google::bigtable::v2::CheckAndMutateRowResponse response;
          response.set_predicate_matched(true);
          return response;
        });

    MockFunction<StatusOr<std::shared_ptr<ChannelUsage<BigtableStub>>>(
        std::uint32_t, std::string const&, StubManager::Priming)>
        stub_factory_fn;
    EXPECT_CALL(stub_factory_fn, Call)
        .Times(1)
        .WillOnce(::testing::Return(
            std::make_shared<ChannelUsage<BigtableStub>>(mock_stub)));

    std::vector<std::shared_ptr<ChannelUsage<BigtableStub>>> channels;

    // Pool creation should set the pool size increase cooldown timer.
    EXPECT_CALL(*mock_cq_impl_, MakeRelativeTimer)
        .WillOnce([&](std::chrono::nanoseconds ns) {
          EXPECT_THAT(ns.count(),
                      Eq(std::chrono::nanoseconds(
                             sizing_policy.pool_size_decrease_cooldown_interval)
                             .count()));
          return make_ready_future(StatusOr(std::chrono::system_clock::now()));
        });

    sizing_policy.maximum_channel_pool_size = 1;
    sizing_policy.minimum_channel_pool_size = 0;
    auto pool = DynamicChannelPool<BigtableStub>::Create(
        instance_name, CompletionQueue(mock_cq_impl_), channels, refresh_state,
        stub_factory_fn.AsStdFunction(), sizing_policy);

    EXPECT_THAT(*pool, ::testing::IsEmpty());

    auto selected_stub = pool->GetChannelRandomTwoLeastUsed();
    grpc::ClientContext context;
    auto response =
        selected_stub->AcquireStub()->CheckAndMutateRow(context, {}, {});
    ASSERT_STATUS_OK(response);
    EXPECT_TRUE(response->predicate_matched());

    EXPECT_THAT(pool->size(), Eq(1));
  }
  fake_cq_impl_->SimulateCompletion(false);
}

#if 0
TEST_F(DynamicChannelPoolTest, ShrinkPool) {
  auto instance_name =
      bigtable::InstanceResource(Project("my-project"), "my-instance")
          .FullName();
  DynamicChannelPoolSizingPolicy sizing_policy;

  auto refresh_state = std::make_shared<ConnectionRefreshState>(
      fake_cq_impl_, std::chrono::milliseconds(1),
      std::chrono::milliseconds(10));

  auto stub_factory_fn = [&](int, std::string const&, StubManager::Priming) {
    return std::make_shared<ChannelUsage<BigtableStub>>(
        std::make_shared<MockBigtableStub>(), fake_clock_impl_, 20);
  };

  std::vector<std::shared_ptr<ChannelUsage<BigtableStub>>> channels;
  auto mock_stub_0 = std::make_shared<MockBigtableStub>();
  EXPECT_CALL(*mock_stub_0, CheckAndMutateRow)
      .WillOnce([](grpc::ClientContext&, Options const&,
                   google::bigtable::v2::CheckAndMutateRowRequest const&) {
        google::bigtable::v2::CheckAndMutateRowResponse response;
        response.set_predicate_matched(true);
        return response;
      });
  int initial_rpc_count = 0;
  channels.push_back(std::make_shared<ChannelUsage<BigtableStub>>(
      std::move(mock_stub_0), fake_clock_impl_, initial_rpc_count++));
  auto mock_stub_1 = std::make_shared<MockBigtableStub>();
  EXPECT_CALL(*mock_stub_1, CheckAndMutateRow).Times(0);
  channels.push_back(std::make_shared<ChannelUsage<BigtableStub>>(
      std::move(mock_stub_1), fake_clock_impl_, initial_rpc_count));

  // Pool creation should set the pool size increase cooldown timer.
  EXPECT_CALL(*mock_cq_impl_, MakeRelativeTimer)
      .WillOnce([&](std::chrono::nanoseconds ns) {
        EXPECT_THAT(ns.count(),
                    Eq(std::chrono::nanoseconds(
                           sizing_policy.pool_size_decrease_cooldown_interval)
                           .count()));
        return make_ready_future(StatusOr(std::chrono::system_clock::now()));
      })
      // Getting a channel from the pool after the initial cooldown timer has
      // expired should remove a channel from selection consideration and
      // trigger decreasing the underutilized pool.
      .WillOnce([&](std::chrono::nanoseconds ns) {
        EXPECT_THAT(ns.count(),
                    Eq(std::chrono::nanoseconds(
                           sizing_policy.remove_channel_polling_interval)
                           .count()));
        return cq_.MakeRelativeTimer(std::chrono::nanoseconds(0));
      })
      // And the decrease cooldown timer should be set again.
      .WillOnce([&](std::chrono::nanoseconds ns) {
        EXPECT_THAT(ns.count(),
                    Eq(std::chrono::nanoseconds(
                           sizing_policy.pool_size_decrease_cooldown_interval)
                           .count()));
        return make_ready_future(StatusOr(std::chrono::system_clock::now()));
      });

  sizing_policy.maximum_channel_pool_size = 2;
  sizing_policy.minimum_channel_pool_size = 1;
  auto pool = DynamicChannelPool<BigtableStub>::Create(
      instance_name, CompletionQueue(mock_cq_impl_), channels, refresh_state,
      stub_factory_fn, sizing_policy);
  EXPECT_THAT(pool->size(), Eq(2));

  auto selected_stub = pool->GetChannelRandomTwoLeastUsed();
  grpc::ClientContext context;
  auto response =
      selected_stub->AcquireStub()->CheckAndMutateRow(context, {}, {});
  ASSERT_STATUS_OK(response);
  EXPECT_TRUE(response->predicate_matched());
  EXPECT_THAT(pool->size(), Eq(1));

  auto draining_channels_size_one =
      [](std::vector<std::shared_ptr<ChannelUsage<BigtableStub>>>& c) {
        EXPECT_THAT(c.size(), Eq(1));
        std::cout << "draining rpcs=" << *c.front()->instant_outstanding_rpcs()
                  << std::endl;
        c.front()->ReleaseStub();
      };
  pool->InstrumentDrainingChannelsNonLocking(draining_channels_size_one);

  fake_clock_impl_->AdvanceTime(sizing_policy.remove_channel_polling_interval +
                                std::chrono::seconds(1));

  auto draining_channels_empty =
      [](std::vector<std::shared_ptr<ChannelUsage<BigtableStub>>>& c) {
        EXPECT_THAT(c, IsEmpty());
      };

  // Execute this check on the CompletionQueue thread to maintain sequencing
  // with execution of RemoveChannels.
  cq_.RunAsync([pool, fn = std::move(draining_channels_empty)]() {
    pool->InstrumentDrainingChannelsNonLocking(fn);
  });

  fake_cq_impl_->SimulateCompletion(false);
}
#endif

TEST_F(DynamicChannelPoolTest, AddChannels) {
  auto instance_name =
      bigtable::InstanceResource(Project("my-project"), "my-instance")
          .FullName();
  DynamicChannelPoolSizingPolicy sizing_policy;
  auto refresh_state = std::make_shared<ConnectionRefreshState>(
      fake_cq_impl_, std::chrono::milliseconds(1),
      std::chrono::milliseconds(10));

  MockFunction<StatusOr<std::shared_ptr<ChannelUsage<BigtableStub>>>(
      std::uint32_t, std::string const&, StubManager::Priming)>
      stub_factory_fn;
  auto mock_stub_0 = std::make_shared<MockBigtableStub>();
  auto mock_stub_1 = std::make_shared<MockBigtableStub>();
  EXPECT_CALL(stub_factory_fn, Call)
  .WillOnce([&](int id, std::string const& instance, StubManager::Priming priming) {
    EXPECT_THAT(id, Eq(0));
    EXPECT_THAT(instance, Eq(instance_name));
    EXPECT_THAT(priming, Eq(StubManager::Priming::kSynchronousPriming));
    return std::make_shared<ChannelUsage<BigtableStub>>(
        mock_stub_0, fake_clock_impl_, 20);
  })
  .WillOnce([&](int id, std::string const& instance, StubManager::Priming priming) {
    EXPECT_THAT(id, Eq(1));
    EXPECT_THAT(instance, Eq(instance_name));
    EXPECT_THAT(priming, Eq(StubManager::Priming::kSynchronousPriming));
    return std::make_shared<ChannelUsage<BigtableStub>>(
        mock_stub_1, fake_clock_impl_, 20);
  });

  std::vector<std::shared_ptr<ChannelUsage<BigtableStub>>> channels;
  auto pool = DynamicChannelPool<BigtableStub>::Create(
      instance_name, CompletionQueue(mock_cq_impl_), channels, refresh_state,
      stub_factory_fn.AsStdFunction(), sizing_policy);
  DynamicChannelPoolTestWrapper wrapper(pool);
  std::vector<int> new_channel_ids = {0, 1};
  wrapper.AddChannels(new_channel_ids);
  EXPECT_THAT(pool->size(), Eq(2));
  fake_cq_impl_->SimulateCompletion(false);
}


}  // namespace
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigtable_internal
}  // namespace cloud
}  // namespace google
