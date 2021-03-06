// Copyright 2019 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "google/cloud/spanner/connection_options.h"
#include "google/cloud/spanner/internal/options.h"
#include "google/cloud/internal/absl_str_join_quiet.h"
#include "google/cloud/internal/common_options.h"
#include "google/cloud/internal/getenv.h"
#include "google/cloud/internal/grpc_options.h"

namespace google {
namespace cloud {
namespace spanner {
inline namespace SPANNER_CLIENT_NS {

std::string ConnectionOptionsTraits::default_endpoint() {
  // TODO(5738): cache the default endpoint in a function-local static after we
  // add support for users using the new `Options` class. We don't want to
  // cache the value currently because users might expect that changing the env
  // var between calls to `MakeConnection()` actually changes the endpoint, and
  // we want to give them an alternative way to accomplish that.
  return spanner_internal::DefaultOptions().get<internal::EndpointOption>();
}

std::string ConnectionOptionsTraits::user_agent_prefix() {
  static auto const* const kUserAgentPrefix = new auto([] {
    auto const defaults = spanner_internal::DefaultOptions();
    auto const& products = defaults.get<internal::UserAgentProductsOption>();
    return absl::StrJoin(products, " ");
  }());
  return *kUserAgentPrefix;
}

int ConnectionOptionsTraits::default_num_channels() {
  static auto const kNumChannels =
      spanner_internal::DefaultOptions().get<internal::GrpcNumChannelsOption>();
  return kNumChannels;
}

}  // namespace SPANNER_CLIENT_NS
}  // namespace spanner
}  // namespace cloud
}  // namespace google
