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

#ifndef GOOGLE_CLOUD_CPP_GENERATOR_INTEGRATION_TESTS_GOLDEN_V1_GOLDEN_REST_ONLY_OPTIONS_H
#define GOOGLE_CLOUD_CPP_GENERATOR_INTEGRATION_TESTS_GOLDEN_V1_GOLDEN_REST_ONLY_OPTIONS_H

#include "generator/integration_tests/golden/v1/golden_rest_only_connection.h"
#include "generator/integration_tests/golden/v1/golden_rest_only_connection_idempotency_policy.h"
#include "google/cloud/backoff_policy.h"
#include "google/cloud/options.h"
#include "google/cloud/version.h"
#include <memory>

namespace google {
namespace cloud {
namespace golden_v1 {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

/**
 * Use with `google::cloud::Options` to configure the retry policy.
 *
 * @ingroup generator-integration_tests-golden-options
 */
struct GoldenRestOnlyRetryPolicyOption {
  using Type = std::shared_ptr<GoldenRestOnlyRetryPolicy>;
};

/**
 * Use with `google::cloud::Options` to configure the backoff policy.
 *
 * @ingroup generator-integration_tests-golden-options
 */
struct GoldenRestOnlyBackoffPolicyOption {
  using Type = std::shared_ptr<BackoffPolicy>;
};

/**
 * Use with `google::cloud::Options` to configure which operations are retried.
 *
 * @ingroup generator-integration_tests-golden-options
 */
struct GoldenRestOnlyConnectionIdempotencyPolicyOption {
  using Type = std::shared_ptr<GoldenRestOnlyConnectionIdempotencyPolicy>;
};

/**
 * The options applicable to GoldenRestOnly.
 *
 * @ingroup generator-integration_tests-golden-options
 */
using GoldenRestOnlyPolicyOptionList =
    OptionList<GoldenRestOnlyRetryPolicyOption,
               GoldenRestOnlyBackoffPolicyOption,
               GoldenRestOnlyConnectionIdempotencyPolicyOption>;

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace golden_v1
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GENERATOR_INTEGRATION_TESTS_GOLDEN_V1_GOLDEN_REST_ONLY_OPTIONS_H
