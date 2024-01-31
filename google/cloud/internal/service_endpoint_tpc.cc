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

#include "google/cloud/common_options.h"
#include "google/cloud/credentials.h"
#include "google/cloud/internal/absl_str_replace_quiet.h"
#include "google/cloud/internal/make_status.h"
#include "google/cloud/internal/service_endpoint.h"
// #include "google/cloud/internal/unified_grpc_credentials.h"
#include "google/cloud/tpc_options.h"
#include "absl/strings/str_format.h"

namespace google {
namespace cloud {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN
namespace internal {

StatusOr<std::string> DetermineServiceEndpoint(
    absl::optional<std::string> endpoint_env_var,
    absl::optional<std::string> endpoint_option, Options const& options,
    std::string default_host) {
  auto constexpr kGoogleDefaultUniverse = "googleapis.com";
  if (endpoint_env_var.has_value()) return *endpoint_env_var;
  if (endpoint_option.has_value()) return *endpoint_option;

  if (options.has<TpcUniverseDomainOption>()) {
    if (options.has<UnifiedCredentialsOption>()) {
      auto const& creds = options.get<UnifiedCredentialsOption>();
      std::string enable_tpc_universe_domain_option =
          options.get<TpcUniverseDomainOption>();
      // If the TpcUniverseDomainOption is set by the user, then we must
      // interrogate the credentials as part of determining the service
      // endpoint.
      if (!enable_tpc_universe_domain_option.empty()) {
        auto credentials_universe_domain = creds->universe_domain();
        // If the auth library encounters an error retrieving the
        // universe_domain from the credentials and the user has provided an
        // TpcUniverseDomainOption, we must not create a connection and
        // instead return the error from the auth library.
        if (!credentials_universe_domain.ok()) {
          return std::move(credentials_universe_domain).status();
        }

        // If the TpcUniverseDomainOption is set, then we must only create a
        // connection if the credentials universe_domain matches the option
        // value.
        if (enable_tpc_universe_domain_option == *credentials_universe_domain) {
          return absl::StrReplaceAll(
              default_host,
              {{kGoogleDefaultUniverse, *credentials_universe_domain}});
        }
        return internal::InvalidArgumentError(absl::StrFormat(
            "Credentials universe_domain: %s does not match "
            "EnableTpcUniverseDomainOption: %s",
            *credentials_universe_domain, enable_tpc_universe_domain_option));

      } else {
        return internal::InvalidArgumentError(
            "TpcUniverseDomainOption can not be empty");
      }
    } else {
      return internal::InvalidArgumentError(
          "UnifiedCredentialsOption must be set");
    }
  }

  // If the TpcUniverseDomainOption is NOT set by the user, the service
  // endpoint from the proto service definition is used.
  return default_host;
}

}  // namespace internal
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace cloud
}  // namespace google
