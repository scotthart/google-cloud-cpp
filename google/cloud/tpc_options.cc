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

#include "google/cloud/tpc_options.h"
#include <iostream>

namespace google {
namespace cloud {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN
namespace {

StatusOr<std::string> GetUniverseDomainFromMetadataServer(Options const& opts) {
  // make metadata server call and parse response, similar to process used
  // in oauth2_compute_engine_credentials.cc
  return {};
}
}  // namespace

TpcUniverseDomainOption::Type::Type() {}  // NOLINT

StatusOr<std::string> GetUniverseDomain(std::shared_ptr<Credentials> creds,
                                        Options const& options) {
  StatusOr<std::string> universe_domain{internal::FailedPreconditionError(
      "Credentials type does not support universe_domain")};

  if (creds->universe_domain_location() ==
      Credentials::UniverseDomainLocation::kInSitu) {
    // universe_domain would be present in file credentials were created from
    // and already parsed
    universe_domain = creds->universe_domain();
  } else if (creds->universe_domain_location() ==
             Credentials::UniverseDomainLocation::kMDS) {
    // universe_domain requires an rpc call to the MetadataServer.
    Options opts = options;
    if (!opts.has<UniverseDomainRetryPolicyOption>()) {
      opts.set<UniverseDomainRetryPolicyOption>(
          UniverseDomainLimitedErrorCountRetryPolicy(3).clone());
    }
    universe_domain = GetUniverseDomainFromMetadataServer(opts);
    creds->set_universe_domain(std::move(universe_domain));
  }

  return universe_domain;
}

StatusOr<Options> MakeTpcDefaultCredentialsOptions() {
  auto options = google::cloud::Options{}.set<UniverseDomainRetryPolicyOption>(
      UniverseDomainLimitedErrorCountRetryPolicy(3).clone());
  auto creds = google::cloud::MakeGoogleDefaultCredentials();
  auto universe_domain = google::cloud::GetUniverseDomain(creds, options);
  if (!universe_domain.ok()) throw std::move(universe_domain).status();
  options.set<google::cloud::UnifiedCredentialsOption>(creds);
  options.set<google::cloud::TpcUniverseDomainOption>(*universe_domain);
  return options;
}

StatusOr<Options> MakeTpcDefaultCredentialsOptions(
    std::string const& desired_universe_domain) {
  auto options = google::cloud::Options{}.set<UniverseDomainRetryPolicyOption>(
      UniverseDomainLimitedErrorCountRetryPolicy(3).clone());
  auto creds = google::cloud::MakeGoogleDefaultCredentials();
  auto universe_domain = google::cloud::GetUniverseDomain(creds, options);
  if (!universe_domain.ok()) return std::move(universe_domain).status();
  if (*universe_domain != desired_universe_domain) {
    return internal::InvalidArgumentError("error message");
  }
  options.set<google::cloud::UnifiedCredentialsOption>(creds);
  options.set<google::cloud::TpcUniverseDomainOption>(*universe_domain);
  return options;
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace cloud
}  // namespace google
