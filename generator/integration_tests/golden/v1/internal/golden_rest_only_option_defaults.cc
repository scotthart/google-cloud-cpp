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
// source: generator/integration_tests/test2.proto

#include "generator/integration_tests/golden/v1/internal/golden_rest_only_option_defaults.h"
#include "generator/integration_tests/golden/v1/golden_rest_only_connection.h"
#include "generator/integration_tests/golden/v1/golden_rest_only_options.h"
#include "google/cloud/internal/populate_common_options.h"
#include "google/cloud/internal/populate_grpc_options.h"
#include "google/cloud/internal/absl_str_cat_quiet.h"
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace golden_v1_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

namespace {
auto constexpr kBackoffScaling = 2.0;
}  // namespace

Options GoldenRestOnlyDefaultOptions(std::string const& location, Options options) {
  options = internal::PopulateCommonOptions(
      std::move(options), "GOOGLE_CLOUD_CPP_GOLDEN_REST_ONLY_ENDPOINT",
      "", "GOOGLE_CLOUD_CPP_GOLDEN_REST_ONLY_AUTHORITY",
      // optional location tag for generating docs
      absl::StrCat(location, location.empty() ? "" : "-", "goldenrestonly.googleapis.com"));
  options = internal::PopulateGrpcOptions(std::move(options));
  if (!options.has<golden_v1::GoldenRestOnlyRetryPolicyOption>()) {
    options.set<golden_v1::GoldenRestOnlyRetryPolicyOption>(
        golden_v1::GoldenRestOnlyLimitedTimeRetryPolicy(
            std::chrono::minutes(30)).clone());
  }
  if (!options.has<golden_v1::GoldenRestOnlyBackoffPolicyOption>()) {
    options.set<golden_v1::GoldenRestOnlyBackoffPolicyOption>(
        ExponentialBackoffPolicy(std::chrono::seconds(0), std::chrono::seconds(1),
            std::chrono::minutes(5), kBackoffScaling, kBackoffScaling).clone());
  }
  if (!options.has<golden_v1::GoldenRestOnlyConnectionIdempotencyPolicyOption>()) {
    options.set<golden_v1::GoldenRestOnlyConnectionIdempotencyPolicyOption>(
        golden_v1::MakeDefaultGoldenRestOnlyConnectionIdempotencyPolicy());
  }

  return options;
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace golden_v1_internal
}  // namespace cloud
}  // namespace google
