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

#include "google/cloud/bigtable/internal/directpath_prober.h"
#include "google/cloud/bigtable/options.h"
#include "google/cloud/testing_util/mock_grpc_authentication_strategy.h"
#include "google/cloud/testing_util/status_matchers.h"
#include <gmock/gmock.h>
#include <chrono>

namespace google {
namespace cloud {
namespace bigtable_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN
namespace {

using ::google::cloud::testing_util::IsOk;
using ::google::cloud::testing_util::MockAuthenticationStrategy;
using ::google::cloud::testing_util::StatusIs;
using ::testing::AllOf;
using ::testing::Eq;
using ::testing::ExplainMatchResult;
using ::testing::IsEmpty;
using ::testing::Not;

MATCHER_P(ProbeSuccess, success_matcher, "") {
  return ExplainMatchResult(success_matcher, arg.success, result_listener);
}

MATCHER_P(ProbeIpPreference, ip_matcher, "") {
  return ExplainMatchResult(ip_matcher, arg.ip_preference, result_listener);
}

TEST(DirectPathProberTest, ToStringIpPreference) {
  EXPECT_THAT(ToString(IpPreference::kIpv4), Eq("ipv4"));
  EXPECT_THAT(ToString(IpPreference::kIpv6), Eq("ipv6"));
  EXPECT_THAT(ToString(IpPreference::kNone), IsEmpty());
}

TEST(DirectPathProberTest, ProbeNullAuthFails) {
  DirectPathProbeResult const result =
      DirectPathProber::Probe(nullptr, Options{}, CompletionQueue{});
  EXPECT_THAT(result.success, Eq(false));
  EXPECT_THAT(result.status, StatusIs(StatusCode::kInvalidArgument));
}

TEST(DirectPathProberTest, ProbeHonorsTimeoutOption) {
  auto mock_auth = std::make_shared<MockAuthenticationStrategy>();
  EXPECT_CALL(*mock_auth, RequiresConfigureContext())
      .WillRepeatedly(testing::Return(false));
  EXPECT_CALL(*mock_auth, CreateChannel(testing::_, testing::_))
      .WillRepeatedly([](std::string const&, grpc::ChannelArguments const&) {
        return grpc::CreateCustomChannel("localhost:1",
                                         grpc::InsecureChannelCredentials(),
                                         grpc::ChannelArguments());
      });

  Options const options =
      Options{}.set<bigtable::experimental::DirectPathProbeTimeoutOption>(
          std::chrono::milliseconds(100));

  DirectPathProbeResult const result =
      DirectPathProber::Probe(mock_auth, options, CompletionQueue{});
  EXPECT_THAT(result, AllOf(ProbeSuccess(Eq(false)),
                            ProbeIpPreference(Eq(IpPreference::kNone))));
  EXPECT_THAT(result.status, Not(IsOk()));
}

}  // namespace
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigtable_internal
}  // namespace cloud
}  // namespace google
