// Copyright 2026 Google LLC
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

#include "google/cloud/bigtable/internal/directpath_diagnostics.h"
#include "google/cloud/bigtable/options.h"
#include <gmock/gmock.h>

namespace google {
namespace cloud {
namespace bigtable_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN
namespace {

using ::testing::Eq;

TEST(DirectPathDiagnosticsTest, ToString) {
  EXPECT_THAT(ToString(DiagnosticFailureReason::kNotInGcp), Eq("not_in_gcp"));
  EXPECT_THAT(ToString(DiagnosticFailureReason::kMetadataUnreachable),
              Eq("metadata_unreachable"));
  EXPECT_THAT(ToString(DiagnosticFailureReason::kNoIpAssigned),
              Eq("no_ip_assigned"));
  EXPECT_THAT(ToString(DiagnosticFailureReason::kLoopbackMisconfigured),
              Eq("loopback_misconfigured"));
  EXPECT_THAT(ToString(DiagnosticFailureReason::kLoopbackMisconfiguredIpv4),
              Eq("loopback_misconfigured_ipv4"));
  EXPECT_THAT(ToString(DiagnosticFailureReason::kLoopbackMisconfiguredIpv6),
              Eq("loopback_misconfigured_ipv6"));
  EXPECT_THAT(ToString(DiagnosticFailureReason::kMetadataMissing),
              Eq("metadata_missing"));
  EXPECT_THAT(ToString(DiagnosticFailureReason::kXdsReachabilityFailed),
              Eq("xds_reachability_failed"));
  EXPECT_THAT(ToString(DiagnosticFailureReason::kXdsEdsFailed),
              Eq("xds_eds_failed"));
  EXPECT_THAT(ToString(DiagnosticFailureReason::kXdsMalformedEndpoint),
              Eq("xds_malformed_endpoint"));
  EXPECT_THAT(ToString(DiagnosticFailureReason::kRouteUnreachable),
              Eq("route_unreachable"));
  EXPECT_THAT(ToString(DiagnosticFailureReason::kAltsHandshakeFailed),
              Eq("alts_handshake_failed"));
  EXPECT_THAT(ToString(DiagnosticFailureReason::kTimeout), Eq("timeout"));
  EXPECT_THAT(ToString(DiagnosticFailureReason::kUnknown), Eq("unknown"));
}

TEST(DirectPathDiagnosticsTest, RunDiagnostics) {
  DiagnosticFailureReason const reason =
      DirectPathDiagnostics::RunDiagnostics(Options{});
  // In a local/test environment outside GCP VM or on Windows, it will return
  // not_in_gcp or unknown or metadata_unreachable.
  EXPECT_TRUE(reason == DiagnosticFailureReason::kNotInGcp ||
              reason == DiagnosticFailureReason::kMetadataUnreachable ||
              reason == DiagnosticFailureReason::kUnknown);
}

}  // namespace
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigtable_internal
}  // namespace cloud
}  // namespace google
