// Copyright 2023 Google LLC
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

#include "google/cloud/universe_domain.h"
#include "google/cloud/internal/unified_rest_credentials.h"
#include "google/cloud/universe_domain_options.h"
#include <iostream>

namespace google {
namespace cloud {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN
namespace {

class UniverseDomainLimitedErrorCountRetryPolicy
    : public UniverseDomainRetryPolicy {
 public:
  /**
   * Create an instance that tolerates up to @p maximum_failures transient
   * errors.
   *
   * @note Disable the retry loop by providing an instance of this policy with
   *     @p maximum_failures == 0.
   */
  explicit UniverseDomainLimitedErrorCountRetryPolicy(int maximum_failures)
      : impl_(maximum_failures) {}

  UniverseDomainLimitedErrorCountRetryPolicy(
      UniverseDomainLimitedErrorCountRetryPolicy&& rhs) noexcept
      : UniverseDomainLimitedErrorCountRetryPolicy(rhs.maximum_failures()) {}
  UniverseDomainLimitedErrorCountRetryPolicy(
      UniverseDomainLimitedErrorCountRetryPolicy const& rhs) noexcept
      : UniverseDomainLimitedErrorCountRetryPolicy(rhs.maximum_failures()) {}

  int maximum_failures() const { return impl_.maximum_failures(); }

  bool OnFailure(Status const& status) override {
    return impl_.OnFailure(status);
  }
  bool IsExhausted() const override { return impl_.IsExhausted(); }
  bool IsPermanentFailure(Status const& status) const override {
    return impl_.IsPermanentFailure(status);
  }
  std::unique_ptr<UniverseDomainRetryPolicy> clone() const override {
    return std::make_unique<UniverseDomainLimitedErrorCountRetryPolicy>(
        maximum_failures());
  }

  // This is provided only for backwards compatibility.
  using BaseType = UniverseDomainRetryPolicy;

 private:
  struct UniverseDomainRetryTraits {
    static inline bool IsPermanentFailure(google::cloud::Status const& status) {
      return status.code() != StatusCode::kOk &&
             status.code() != StatusCode::kUnavailable;
    }
  };

  google::cloud::internal::LimitedErrorCountRetryPolicy<
      UniverseDomainRetryTraits>
      impl_;
};

}  // namespace

StatusOr<std::string> GetUniverseDomain(
    std::shared_ptr<Credentials> const& creds, Options options) {
  std::shared_ptr<UniverseDomainRetryPolicy> retry_policy;
  if (!options.has<UniverseDomainRetryPolicyOption>()) {
    options.set<UniverseDomainRetryPolicyOption>(
        std::make_shared<UniverseDomainLimitedErrorCountRetryPolicy>(3));
  }
  std::shared_ptr<oauth2_internal::Credentials> oauth2_creds =
      google::cloud::rest_internal::MapCredentials(*creds);
  return oauth2_creds->universe_domain(options);
}

StatusOr<std::string> GetUniverseDomain(Options options) {
  if (!options.has<UnifiedCredentialsOption>()) {
    options.set<UnifiedCredentialsOption>(
        google::cloud::MakeGoogleDefaultCredentials(options));
  }
  return GetUniverseDomain(options.get<UnifiedCredentialsOption>(), options);
}

StatusOr<Options> AddUniverseDomainOption(Options options) {
  StatusOr<std::string> universe_domain = GetUniverseDomain(options);
  if (!universe_domain.ok()) return std::move(universe_domain).status();
  options.set<UniverseDomainOption>(*universe_domain);
  return options;
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace cloud
}  // namespace google
