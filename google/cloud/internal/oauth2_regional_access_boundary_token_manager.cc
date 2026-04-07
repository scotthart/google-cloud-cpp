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
#include "google/cloud/internal/async_rest_retry_loop.h"
// #include "google/cloud/internal/make_status.h"
// #include "google/cloud/internal/oauth2_universe_domain.h"
#include "absl/strings/str_cat.h"
// #include "absl/strings/str_join.h"

namespace google {
namespace cloud {
namespace oauth2_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN
namespace {

auto constexpr kTokenTtl = std::chrono::seconds(6 * 3600);
auto constexpr kTtlGracePeriod = std::chrono::seconds(3600);
auto constexpr kFailedLookupCooldown = std::chrono::seconds(900);
auto constexpr kMaximumRetryDuration = std::chrono::seconds(60);
auto constexpr kInitialBackoffDelay = std::chrono::seconds(1);
auto constexpr kMaximumBackoffDelay = std::chrono::seconds(5);
auto constexpr kBackoffScaling = 2.0;

}  // namespace

RegionalAccessBoundaryTokenManager::RegionalAccessBoundaryTokenManager(
    std::shared_ptr<MinimalIamCredentialsRest> iam_stub,
    std::unique_ptr<rest_internal::RestPureBackgroundThreads> background,
    std::shared_ptr<Clock> clock)
    : background_(std::move(background)),
      clock_(std::move(clock)),
      retry_policy_(std::make_unique<internal::LimitedTimeRetryPolicy<
                        RegionalAccessBoundaryTokenManager::RetryTraits>>(
          kMaximumRetryDuration)),
      backoff_policy_(std::make_unique<ExponentialBackoffPolicy>(
          kInitialBackoffDelay, kMaximumBackoffDelay, kBackoffScaling)),
      iam_stub_(std::move(iam_stub)) {}

RegionalAccessBoundaryTokenManager::RegionalAccessBoundaryTokenManager(
    std::shared_ptr<MinimalIamCredentialsRest> iam_stub,
    std::shared_ptr<Clock> clock)
    : RegionalAccessBoundaryTokenManager(
          std::move(iam_stub),
          std::make_unique<
              rest_internal::RestPureAutomaticallyCreatedBackgroundThreads>(),
          std::move(clock)) {}

RegionalAccessBoundaryTokenManager::RegionalAccessBoundaryTokenManager(
    std::shared_ptr<oauth2_internal::Credentials> credentials,
    HttpClientFactory client_factory, std::shared_ptr<Clock> clock)
    : RegionalAccessBoundaryTokenManager(
          MakeMinimalIamCredentialsRestStub(std::move(credentials), {},
                                            std::move(client_factory)),
          std::make_unique<
              rest_internal::RestPureAutomaticallyCreatedBackgroundThreads>(),
          std::move(clock)) {}

bool RegionalAccessBoundaryTokenManager::DoesEndpointRequireToken(
    std::string_view endpoint) {
  return absl::EndsWithIgnoreCase(endpoint, ".googleapis.com") &&
         !absl::EndsWithIgnoreCase(endpoint, ".rep.googleapis.com") &&
         !absl::EndsWithIgnoreCase(endpoint, (".rep.sandbox.googleapis.com"));
}

bool RegionalAccessBoundaryTokenManager::IsTokenValid(
    std::chrono::system_clock::time_point tp) const {
  return !allowed_locations_.encoded_locations.empty() && tp < expire_time_;
}

std::chrono::seconds RegionalAccessBoundaryTokenManager::TtlGracePeriod() {
  return kTtlGracePeriod;
}

std::chrono::seconds RegionalAccessBoundaryTokenManager::TokenTtl() {
  return kTokenTtl;
}

std::chrono::seconds
RegionalAccessBoundaryTokenManager::FailedLookupCooldown() {
  return kFailedLookupCooldown;
}

// void RegionalAccessBoundaryTokenManager::RefreshToken(
//     ServiceAccountAllowedLocationsRequest const& request) {
//   std::scoped_lock lock(mu_);
//   if (failed_lookup_cooldown_.valid() && !failed_lookup_cooldown_.is_ready())
//   {
//     return;
//   }
//   auto fn = [iam_stub = iam_stub_](
//                 rest_internal::RestPureCompletionQueue&,
//                 std::unique_ptr<rest_internal::RestContext>,
//                 google::cloud::internal::ImmutableOptions,
//                 ServiceAccountAllowedLocationsRequest const& request) ->
//                 future<StatusOr<Token>> {
//     auto response = iam_stub->AllowedLocations(request);
//     if (!response)
//       return
//       make_ready_future(StatusOr<Token>(std::move(response).status()));
//     return make_ready_future(
//         StatusOr<Token>{Token{response->encoded_locations}});
//   };
//
//   auto r = rest_internal::AsyncRestRetryLoop(
//                retry_policy_->clone(), backoff_policy_->clone(),
//                Idempotency::kIdempotent, cq_, fn,
//                google::cloud::internal::ImmutableOptions{}, request,
//                __func__) .then([weak = weak_from_this()](auto f) -> void {
//                  auto new_token = f.get();
//                  auto manager = weak.lock();
//                  if (!manager) return;
//                  if (new_token.ok()) {
//                    manager->token_ = *new_token;
//                    manager->expire_time_ = manager->clock_->Now() +
//                    kTokenTtl;
//                  } else {
//                    manager->token_ = Token{};
//                    manager->failed_lookup_cooldown_ =
//                        manager->cq_.MakeRelativeTimer(kFailedLookupCooldown);
//                  }
//                });
// }

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace oauth2_internal
}  // namespace cloud
}  // namespace google
