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
// source: google/cloud/compute/network_profiles/v1/network_profiles.proto

#include "google/cloud/compute/network_profiles/v1/internal/network_profiles_option_defaults.h"
#include "google/cloud/compute/network_profiles/v1/network_profiles_connection.h"
#include "google/cloud/compute/network_profiles/v1/network_profiles_options.h"
#include "google/cloud/internal/populate_common_options.h"
#include "google/cloud/internal/populate_grpc_options.h"
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace compute_network_profiles_v1_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

namespace {
auto constexpr kBackoffScaling = 2.0;
}  // namespace

Options NetworkProfilesDefaultOptions(Options options) {
  options = internal::PopulateCommonOptions(
      std::move(options), "GOOGLE_CLOUD_CPP_NETWORK_PROFILES_ENDPOINT", "",
      "GOOGLE_CLOUD_CPP_NETWORK_PROFILES_AUTHORITY", "compute.googleapis.com");
  options = internal::PopulateGrpcOptions(std::move(options));
  if (!options.has<
          compute_network_profiles_v1::NetworkProfilesRetryPolicyOption>()) {
    options.set<compute_network_profiles_v1::NetworkProfilesRetryPolicyOption>(
        compute_network_profiles_v1::NetworkProfilesLimitedTimeRetryPolicy(
            std::chrono::minutes(30))
            .clone());
  }
  if (!options.has<
          compute_network_profiles_v1::NetworkProfilesBackoffPolicyOption>()) {
    options
        .set<compute_network_profiles_v1::NetworkProfilesBackoffPolicyOption>(
            ExponentialBackoffPolicy(
                std::chrono::seconds(0), std::chrono::seconds(1),
                std::chrono::minutes(5), kBackoffScaling, kBackoffScaling)
                .clone());
  }
  if (!options.has<compute_network_profiles_v1::
                       NetworkProfilesConnectionIdempotencyPolicyOption>()) {
    options.set<compute_network_profiles_v1::
                    NetworkProfilesConnectionIdempotencyPolicyOption>(
        compute_network_profiles_v1::
            MakeDefaultNetworkProfilesConnectionIdempotencyPolicy());
  }

  return options;
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace compute_network_profiles_v1_internal
}  // namespace cloud
}  // namespace google
