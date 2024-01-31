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

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_UNIVERSE_DOMAIN_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_UNIVERSE_DOMAIN_H

#include "google/cloud/credentials.h"
#include "google/cloud/internal/make_status.h"
#include "google/cloud/internal/retry_policy_impl.h"
#include "google/cloud/retry_policy.h"
#include "google/cloud/status_or.h"
#include "google/cloud/version.h"
#include "absl/types/optional.h"
#include <string>

namespace google {
namespace cloud {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

StatusOr<std::string> GetUniverseDomain(Credentials const& credentials,
                                        Options options = {});
StatusOr<std::string> GetUniverseDomain(Options options);

StatusOr<Options> AddUniverseDomainOption(Options options = {});

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_UNIVERSE_DOMAIN_H
