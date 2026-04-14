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

#include "google/cloud/internal/oauth2_regional_access_boundary_token_manager.h"
#include "google/cloud/internal/make_status.h"
#include "google/cloud/internal/rest_pure_background_threads_impl.h"
#include "google/cloud/internal/rest_response.h"
#include "google/cloud/internal/unified_rest_credentials.h"
#include "google/cloud/testing_util/fake_clock.h"
#include "google/cloud/testing_util/status_matchers.h"
#include <gmock/gmock.h>

namespace google {
namespace cloud {
namespace oauth2_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN
namespace {

using ::google::cloud::testing_util::IsOkAndHolds;
using ::testing::A;
using ::testing::IsEmpty;
using ::testing::MockFunction;
using ::testing::Return;

class MockMinimalIamCredentialsRest : public MinimalIamCredentialsRest {
 public:
  MOCK_METHOD(StatusOr<google::cloud::AccessToken>, GenerateAccessToken,
              (GenerateAccessTokenRequest const&), (override));
  MOCK_METHOD(StatusOr<AllowedLocationsResponse>, AllowedLocations,
              (ServiceAccountAllowedLocationsRequest const&), (override));
  MOCK_METHOD(StatusOr<AllowedLocationsResponse>, AllowedLocations,
              (WorkloadIdentityAllowedLocationsRequest const&), (override));
  MOCK_METHOD(StatusOr<AllowedLocationsResponse>, AllowedLocations,
              (WorkforceIdentityAllowedLocationsRequest const&), (override));
  MOCK_METHOD(StatusOr<std::string>, universe_domain, (Options const& options),
              (override, const));
};

class MockRestPureCompletionQueueImpl
    : public rest_internal::RestPureCompletionQueueInterface {
 public:
  MOCK_METHOD(void, Run, (), (override));
  MOCK_METHOD(void, Shutdown, (), (override));
  MOCK_METHOD(void, CancelAll, (), (override));
  MOCK_METHOD(future<StatusOr<std::chrono::system_clock::time_point>>,
              MakeDeadlineTimer,
              (std::chrono::system_clock::time_point deadline), (override));
  MOCK_METHOD(future<StatusOr<std::chrono::system_clock::time_point>>,
              MakeRelativeTimer, (std::chrono::nanoseconds), (override));
  MOCK_METHOD(void, RunAsync, (std::unique_ptr<internal::RunAsyncBase>),
              (override));
};

class MockRestPureBackgroundThreads
    : public rest_internal::RestPureBackgroundThreads {
 public:
  MOCK_METHOD(rest_internal::RestPureCompletionQueue, cq, (),
              (override, const));
};

class MockBackoffPolicy : public BackoffPolicy {
 public:
  MOCK_METHOD(std::unique_ptr<BackoffPolicy>, clone, (), (const, override));
  MOCK_METHOD(std::chrono::milliseconds, OnCompletion, (), (override));
};

TEST(RegionalAccessBoundaryTokenManagerRetryTraitsTest, RetryTraits) {
  auto http_status_500 =
      rest_internal::AsStatus(rest_internal::kInternalServerError, {});
  auto http_status_502 =
      rest_internal::AsStatus(rest_internal::kBadGateway, {});
  auto http_status_503 =
      rest_internal::AsStatus(rest_internal::kServiceUnavailable, {});
  auto http_status_504 =
      rest_internal::AsStatus(rest_internal::kGatewayTimeout, {});

  using RetryTraits = RegionalAccessBoundaryTokenManager::RetryTraits;

  EXPECT_FALSE(RetryTraits::IsPermanentFailure(http_status_500));
  EXPECT_FALSE(RetryTraits::IsPermanentFailure(http_status_502));
  EXPECT_FALSE(RetryTraits::IsPermanentFailure(http_status_503));
  EXPECT_FALSE(RetryTraits::IsPermanentFailure(http_status_504));

  auto http_status_404 = rest_internal::AsStatus(rest_internal::kNotFound, {});
  EXPECT_TRUE(RetryTraits::IsPermanentFailure(http_status_404));
}

class RegionalAccessBoundaryTokenManagerTest : public ::testing::Test {
 protected:
  RegionalAccessBoundaryTokenManagerTest()
      : mock_iam_stub_(std::make_shared<MockMinimalIamCredentialsRest>()),
        fake_clock_(std::make_shared<testing_util::FakeSystemClock>()) {}

  std::shared_ptr<MockMinimalIamCredentialsRest> mock_iam_stub_;
  std::shared_ptr<testing_util::FakeSystemClock> fake_clock_;
};

TEST_F(RegionalAccessBoundaryTokenManagerTest,
       GetAllowedLocationsHeaderNonApplicableEndpoints) {
  auto manager = RegionalAccessBoundaryTokenManager::Create(mock_iam_stub_, {});

  ServiceAccountAllowedLocationsRequest request;
  auto header = manager->GetAllowedLocationsHeader(
      request, std::chrono::system_clock::now(), "service.rep.googleapis.com");
  EXPECT_THAT(header, IsOkAndHolds(IsEmpty()));

  auto header_sandbox = manager->GetAllowedLocationsHeader(
      request, std::chrono::system_clock::now(),
      "service.rep.sandbox.googleapis.com");
  EXPECT_THAT(header_sandbox, IsOkAndHolds(IsEmpty()));

  auto header_non_gdu = manager->GetAllowedLocationsHeader(
      request, std::chrono::system_clock::now(), "service.bar.com");
  EXPECT_THAT(header_non_gdu, IsOkAndHolds(IsEmpty()));
}

TEST_F(RegionalAccessBoundaryTokenManagerTest,
       GetAllowedLocationsHeaderValidTokenSoftExpiry) {
  fake_clock_->SetTime(std::chrono::system_clock::now());
  MockFunction<std::unique_ptr<BackoffPolicy>()> backoff_fn;
  EXPECT_CALL(backoff_fn, Call).Times(0);

  AllowedLocationsResponse allowed_locations;
  allowed_locations.locations = {"location1"};
  allowed_locations.encoded_locations = "encoded-location";

  auto manager = RegionalAccessBoundaryTokenManager::Create(
      mock_iam_stub_, {}, backoff_fn.AsStdFunction(), fake_clock_,
      allowed_locations);

  fake_clock_->AdvanceTime(std::chrono::seconds(1));

  ServiceAccountAllowedLocationsRequest request;
  auto header = manager->GetAllowedLocationsHeader(request, fake_clock_->Now(),
                                                   "service.googleapis.com");
  EXPECT_THAT(header,
              IsOkAndHolds(rest_internal::HttpHeader{
                  "x-allowed-locations", allowed_locations.encoded_locations}));

  promise<void> sync_threads;
  AllowedLocationsResponse refreshed_allowed_locations;
  refreshed_allowed_locations.locations = {"location2"};
  refreshed_allowed_locations.encoded_locations = "encoded-location-2";
  // Refresh is called due to soft expiry, but current token is still returned.
  EXPECT_CALL(
      *mock_iam_stub_,
      AllowedLocations(A<ServiceAccountAllowedLocationsRequest const&>()))
      .WillOnce([&, f = sync_threads.get_future()](
                    ServiceAccountAllowedLocationsRequest const&) mutable {
        f.get();
        return refreshed_allowed_locations;
      });

  fake_clock_->AdvanceTime(
      RegionalAccessBoundaryTokenManager::TokenTtl() -
      RegionalAccessBoundaryTokenManager::TtlGracePeriod());

  header = manager->GetAllowedLocationsHeader(request, fake_clock_->Now(),
                                              "service.googleapis.com");
  EXPECT_THAT(header,
              IsOkAndHolds(rest_internal::HttpHeader{
                  "x-allowed-locations", allowed_locations.encoded_locations}));
  EXPECT_TRUE(manager->IsRefreshPending());
  sync_threads.set_value();

  // Give background thread a chance to call AllowedLocations.
  std::this_thread::sleep_for(std::chrono::seconds(2));
  header = manager->GetAllowedLocationsHeader(request, fake_clock_->Now(),
                                              "service.googleapis.com");
  EXPECT_THAT(header, IsOkAndHolds(rest_internal::HttpHeader{
                          "x-allowed-locations",
                          refreshed_allowed_locations.encoded_locations}));
}

TEST_F(RegionalAccessBoundaryTokenManagerTest,
       GetAllowedLocationsHeaderNoInitialValidTokenWithRetry) {
  AllowedLocationsResponse response;
  response.locations = {"location1"};
  response.encoded_locations = "encoded-location";
  EXPECT_CALL(
      *mock_iam_stub_,
      AllowedLocations(A<ServiceAccountAllowedLocationsRequest const&>()))
      .WillOnce([&](ServiceAccountAllowedLocationsRequest const&) {
        return internal::UnavailableError("unavailable");
      })
      .WillOnce([&](ServiceAccountAllowedLocationsRequest const&) {
        return response;
      });

  auto manager = RegionalAccessBoundaryTokenManager::Create(mock_iam_stub_, {});

  ServiceAccountAllowedLocationsRequest request;
  auto header = manager->GetAllowedLocationsHeader(
      request, std::chrono::system_clock::now(), "service.googleapis.com");
  EXPECT_THAT(header, IsOkAndHolds(IsEmpty()));

  // Give the background thread a chance to run the future::then callback
  // and update the token.
  std::this_thread::sleep_for(std::chrono::seconds(2));

  header = manager->GetAllowedLocationsHeader(
      request, std::chrono::system_clock::now(), "service.googleapis.com");
  EXPECT_THAT(header, IsOkAndHolds(rest_internal::HttpHeader{
                          "x-allowed-locations", response.encoded_locations}));
}

TEST_F(RegionalAccessBoundaryTokenManagerTest,
       GetAllowedLocationsHeaderPermanentFailureAndRecovery) {
  AllowedLocationsResponse response;
  response.locations = {"location1"};
  response.encoded_locations = "encoded-location";
  EXPECT_CALL(
      *mock_iam_stub_,
      AllowedLocations(A<ServiceAccountAllowedLocationsRequest const&>()))
      .WillOnce([&](ServiceAccountAllowedLocationsRequest const&) {
        return internal::UnavailableError("unavailable");
      })
      .WillOnce([&](ServiceAccountAllowedLocationsRequest const&) {
        return internal::InternalError("uh oh");
      })
      .WillOnce([&](ServiceAccountAllowedLocationsRequest const&) {
        return response;
      });

  MockFunction<std::unique_ptr<BackoffPolicy>()> backoff_fn;
  EXPECT_CALL(backoff_fn, Call).WillOnce([]() {
    auto mock_backoff = std::make_unique<MockBackoffPolicy>();
    EXPECT_CALL(*mock_backoff, OnCompletion)
        .WillOnce(Return(std::chrono::milliseconds(1000)));
    return mock_backoff;
  });

  auto manager = RegionalAccessBoundaryTokenManager::Create(
      mock_iam_stub_, {}, backoff_fn.AsStdFunction());

  ServiceAccountAllowedLocationsRequest request;
  auto header = manager->GetAllowedLocationsHeader(
      request, std::chrono::system_clock::now(), "service.googleapis.com");
  EXPECT_THAT(header, IsOkAndHolds(IsEmpty()));

  // Give the background thread a chance to run and update the token.
  std::this_thread::sleep_for(std::chrono::seconds(2));

  header = manager->GetAllowedLocationsHeader(
      request, std::chrono::system_clock::now(), "service.googleapis.com");
  EXPECT_THAT(header, IsOkAndHolds(IsEmpty()));
  // Permanent error encountered; verify cooldown has been set.
  EXPECT_TRUE(manager->IsOnCooldown());

  // With no valid token and active cooldown, no call to AllowedLocations on the
  // iam stub should occur.
  header = manager->GetAllowedLocationsHeader(
      request, std::chrono::system_clock::now(), "service.googleapis.com");
  EXPECT_THAT(header, IsOkAndHolds(IsEmpty()));

  // With the mock backoff returning a short failure cooldown, let it expire.
  std::this_thread::sleep_for(std::chrono::seconds(1));

  header = manager->GetAllowedLocationsHeader(
      request, std::chrono::system_clock::now(), "service.googleapis.com");
  EXPECT_THAT(header, IsOkAndHolds(IsEmpty()));

  // Give the background thread a chance to run and update the token.
  std::this_thread::sleep_for(std::chrono::seconds(2));

  header = manager->GetAllowedLocationsHeader(
      request, std::chrono::system_clock::now(), "service.googleapis.com");
  EXPECT_THAT(header, IsOkAndHolds(rest_internal::HttpHeader{
                          "x-allowed-locations", response.encoded_locations}));
}

}  // namespace
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace oauth2_internal
}  // namespace cloud
}  // namespace google
