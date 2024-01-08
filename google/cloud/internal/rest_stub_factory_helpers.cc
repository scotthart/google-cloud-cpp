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

#include "google/cloud/internal/rest_stub_factory_helpers.h"
#include "google/cloud/common_options.h"
#include "google/cloud/credentials.h"
#include "google/cloud/internal/absl_str_cat_quiet.h"
#include "google/cloud/internal/credentials_impl.h"
#include "google/cloud/internal/populate_common_options.h"
#include "google/cloud/internal/rest_options.h"
#include "google/cloud/internal/service_endpoint.h"
#include "absl/strings/match.h"

namespace google {
namespace cloud {
namespace rest_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

Options DetermineStubCreationOptions(
    absl::optional<std::string> const& service_endpoint_env_var,
    std::string const& default_service_endpoint,
    Options& options) {
  Options stub_creation_opts = options;

  if (!options.has<UnifiedCredentialsOption>()) {
    stub_creation_opts.set<UnifiedCredentialsOption>(
        MakeGoogleDefaultCredentials(internal::MakeAuthOptions(options)));
  }

  auto lro_endpoint = internal::DetermineServiceEndpoint(
      {},
      internal::FetchOption<rest_internal::LongrunningEndpointOption>(options),
      "https://longrunning.googleapis.com",
      options);

  auto service_endpoint = internal::DetermineServiceEndpoint(
      service_endpoint_env_var,
      internal::FetchOption<EndpointOption>(options), default_service_endpoint,
      options);

  if (!lro_endpoint.ok() || !service_endpoint.ok()) {
    if (!service_endpoint.ok()) {
      options.unset<EndpointOption>();
      stub_creation_opts.set<UnifiedCredentialsOption>(
          internal::MakeErrorCredentials(std::move(service_endpoint).status()));
    } else {
      options.unset<rest_internal::LongrunningEndpointOption>();
      stub_creation_opts.set<UnifiedCredentialsOption>(
          internal::MakeErrorCredentials(std::move(lro_endpoint).status()));
    }
  } else {
    if (!absl::StartsWithIgnoreCase(*lro_endpoint, "http")) {
      stub_creation_opts.set<rest_internal::LongrunningEndpointOption>(
          absl::StrCat("https://", *lro_endpoint));
    } else {
      stub_creation_opts.set<rest_internal::LongrunningEndpointOption>(
          *lro_endpoint);
    }

    if (!absl::StartsWithIgnoreCase(*service_endpoint, "http")) {
      stub_creation_opts.set<EndpointOption>(absl::StrCat(
          "https://", *service_endpoint));
    } else {
      stub_creation_opts.set<EndpointOption>(*service_endpoint);
    }
    options.set<EndpointOption>(*service_endpoint);
    options.set<rest_internal::LongrunningEndpointOption>(*lro_endpoint);
  }

  return stub_creation_opts;
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace rest_internal
}  // namespace cloud
}  // namespace google
