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

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_TPC_OPTIONS_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_TPC_OPTIONS_H

#include "google/cloud/credentials.h"
#include "google/cloud/internal/make_status.h"
#include "google/cloud/internal/retry_policy_impl.h"
#include "google/cloud/retry_policy.h"
#include "google/cloud/version.h"
#include "absl/types/optional.h"
#include <string>

namespace google {
namespace cloud {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN
#if 0
struct EnableTpcUniverseDomainOption {
  using Type = absl::optional<std::string>;
}
#endif
#if 0
struct EnableTpcUniverseDomainOption {
  struct Type {
    Type();
    template <typename U>
    Type(U&& u) : value(std::forward<U>(u)) {}

    absl::optional<std::string> value;
    operator decltype(value)() const {return value;}

  };
};
#endif

#if 0
struct EnableTpcUniverseDomainOption {
  class Type {
   public:
    template <typename U>
    Type(U&& u) : value(std::forward<U>(u)) {}
    std::string operator *() const {
        return *value;
    }
    operator bool() const { return has_value(); }
    bool has_value() const { return value.has_value(); }
    operator absl::optional<std::string>() const { return value; }
   private:
    Type();

    absl::optional<std::string> value;
  };
};
#endif

struct TpcUniverseDomainOption {
  class Type {
   public:
    Type();
    template <typename U>
    Type(U&& u) : value(std::forward<U>(u)) {}
    operator std::string() const { return value; }

   private:
    std::string value;
  };
};

StatusOr<std::string> GetUniverseDomain(std::shared_ptr<Credentials> creds,
                                        Options const& options);

class UniverseDomainRetryPolicy : public ::google::cloud::RetryPolicy {
 public:
  /// Creates a new instance of the policy, reset to the initial state.
  virtual std::unique_ptr<UniverseDomainRetryPolicy> clone() const = 0;
};

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

struct UniverseDomainRetryPolicyOption {
  using Type = std::shared_ptr<UniverseDomainRetryPolicy>;
};

StatusOr<Options> MakeTpcDefaultCredentialsOptions();

StatusOr<Options> MakeTpcDefaultCredentialsOptions(
    std::string const& desired_universe_domain);

// struct EnableTpcUniverseDomainOption {
//   struct Foo {
//     Foo();
//     explicit Foo(std::string s) : s(std::move(s)) {}
//     explicit Foo(const char* s) : s(s) {}
//     operator std::string() const {return s;}
//     std::string s;
//   };
//   using Type = absl::optional<Foo>;
// };

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_TPC_OPTIONS_H
