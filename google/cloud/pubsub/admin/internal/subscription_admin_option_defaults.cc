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
// source: google/pubsub/v1/pubsub.proto

#include "google/cloud/pubsub/admin/internal/subscription_admin_option_defaults.h"
#include "google/cloud/pubsub/admin/subscription_admin_connection.h"
#include "google/cloud/pubsub/admin/subscription_admin_options.h"
#include "google/cloud/internal/absl_str_cat_quiet.h"
#include "google/cloud/internal/populate_common_options.h"
#include "google/cloud/internal/populate_grpc_options.h"
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace pubsub_admin_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

namespace {
auto constexpr kBackoffScaling = 2.0;
}  // namespace

Options SubscriptionAdminDefaultOptions(std::string const& location,
                                        Options options) {
  options = internal::PopulateCommonOptions(
      std::move(options), "GOOGLE_CLOUD_CPP_SUBSCRIBER_ENDPOINT",
      "PUBSUB_EMULATOR_HOST", "GOOGLE_CLOUD_CPP_SUBSCRIBER_AUTHORITY",
      // optional location tag for generating docs
      absl::StrCat(location, location.empty() ? "" : "-",
                   "pubsub.googleapis.com"));
  options = internal::PopulateGrpcOptions(std::move(options));
  if (!options.has<pubsub_admin::SubscriptionAdminRetryPolicyOption>()) {
    options.set<pubsub_admin::SubscriptionAdminRetryPolicyOption>(
        pubsub_admin::SubscriptionAdminLimitedTimeRetryPolicy(
            std::chrono::minutes(30))
            .clone());
  }
  if (!options.has<pubsub_admin::SubscriptionAdminBackoffPolicyOption>()) {
    options.set<pubsub_admin::SubscriptionAdminBackoffPolicyOption>(
        ExponentialBackoffPolicy(
            std::chrono::seconds(0), std::chrono::seconds(1),
            std::chrono::minutes(5), kBackoffScaling, kBackoffScaling)
            .clone());
  }
  if (!options.has<
          pubsub_admin::SubscriptionAdminConnectionIdempotencyPolicyOption>()) {
    options
        .set<pubsub_admin::SubscriptionAdminConnectionIdempotencyPolicyOption>(
            pubsub_admin::
                MakeDefaultSubscriptionAdminConnectionIdempotencyPolicy());
  }

  return options;
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace pubsub_admin_internal
}  // namespace cloud
}  // namespace google
