#!/usr/bin/env bash
#
# Copyright 2023 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# To debug failed tests, please refer to
# https://github.com/googleapis/cloud-bigtable-clients-test

set -euo pipefail

source "$(dirname "$0")/../../../../ci/lib/init.sh"

if [[ $# -lt 1 ]]; then
  echo "Usage: $(basename "$0") <bazel-program> [bazel-args]"
  exit 1
fi

BAZEL_BIN="$1"
shift
bazel_args=("$@")

# Build and start the proxy in the background process. They are split as the
# test will wait for the proxy to be live, subject to timeout (e.g. 100s).
# Building the binary can easily take more than the timeout limit.
pushd "$(dirname "$0")/../test_proxy" >/dev/null
"${BAZEL_BIN}" build "${bazel_args[@]}" :cbt_test_proxy_main
GOOGLE_CLOUD_CPP_ENABLE_CLOG=1 "${BAZEL_BIN}" run "${bazel_args[@]}" :cbt_test_proxy_main -- 9999 2>&1 &
proxy_pid=$!
popd >/dev/null

# Run the test
pushd /var/tmp/downloads/cloud-bigtable-clients-test/tests >/dev/null
# Run all non ExecuteQuery tests with skips for non ExecuteQuery tests.
#go test -v \
#  -skip "Generic_CloseClient|Generic_DeadlineExceeded|NoRetry_OutOfOrderError_Reverse|Retry_LastScannedRow_Reverse|Retry_WithRetryInfo_OverallDedaline|TestExecuteQuery" \
#  -proxy_addr=:9999
#exit_status=$?

# Run all the ExecuteQuery tests that either work or we plan to skip such as
# CloseClient
go test -v \
  -run "TestExecuteQuery" \
  -skip "CloseClient|FailsOnInvalidType|TestExecuteQuery_PlanRefresh_RespectsDeadline|TestExecuteQuery_FailsOnEmptyMetadata|TestExecuteQuery_FailsOnExecuteQueryMetadata" \
  -proxy_addr=:9999
exit_status=$?

#go test -v \
#  -run "TestExecuteQuery_RetryTest_WithPlanRefresh|TestExecuteQuery_PlanRefresh_RecoversAfterPermanentError" \
#  -proxy_addr=:9999
#exit_status=$?

#--- FAIL: TestExecuteQuery_PlanRefresh_RespectsDeadline (2.73s)
#--- PASS: TestExecuteQuery_PlanRefresh_Retries (0.00s)
#--- FAIL: TestExecuteQuery_PlanRefresh_RecoversAfterPermanentError (0.00s)

#--- FAIL: TestExecuteQuery_FailsOnEmptyMetadata (0.03s)
#--- FAIL: TestExecuteQuery_FailsOnExecuteQueryMetadata (0.03s)
#--- FAIL: TestExecuteQuery_FailsOnInvalidType (0.03s)
#--- FAIL: TestExecuteQuery_ExecuteQueryRespectsDeadline (10.04s)
#--- FAIL: TestExecuteQuery_RetryTest_WithPlanRefresh (0.09s)
#--- FAIL: TestExecuteQuery_PlanRefresh (0.79s)
#--- FAIL: TestExecuteQuery_PlanRefresh_WithMetadataChange (0.00s)
#--- FAIL: TestExecuteQuery_PlanRefresh_AfterResumeTokenCausesError (0.00s)
#--- FAIL: TestExecuteQuery_PlanRefresh_RespectsDeadline (0.00s)
#--- FAIL: TestExecuteQuery_PlanRefresh_Retries (0.00s)
#--- FAIL: TestExecuteQuery_PlanRefresh_RecoversAfterPermanentError (0.00s)

#--- PASS: TestExecuteQuery_EmptyResponse (0.08s)
#--- PASS: TestExecuteQuery_SingleSimpleRow (0.03s)
#--- PASS: TestExecuteQuery_TypesTest (0.04s)
#--- PASS: TestExecuteQuery_NullsTest (0.03s)
#--- PASS: TestExecuteQuery_NestedNullsTest (0.03s)
#--- PASS: TestExecuteQuery_MapAllowsDuplicateKey (0.03s)
#--- PASS: TestExecuteQuery_QueryParams (0.04s)
#--- PASS: TestExecuteQuery_ChunkingTest (0.08s)
#--- PASS: TestExecuteQuery_BatchesTest (0.13s)
#--- PASS: TestExecuteQuery_FailsOnNotEnoughData (0.03s)
#--- PASS: TestExecuteQuery_FailsOnNotEnoughDataWithCompleteRows (0.03s)
#--- PASS: TestExecuteQuery_FailsOnTypeMismatch (0.03s)
#--- PASS: TestExecuteQuery_FailsOnTypeMismatchWithinMap (0.03s)
#--- PASS: TestExecuteQuery_FailsOnTypeMismatchWithinArray (0.03s)
#--- PASS: TestExecuteQuery_FailsOnTypeMismatchWithinStruct (0.04s)
#--- PASS: TestExecuteQuery_FailsOnStructMissingField (0.03s)
#--- PASS: TestExecuteQuery_StructWithNoColumnNames (0.03s)
#--- PASS: TestExecuteQuery_StructWithDuplicateColumnNames (0.03s)
#--- PASS: TestExecuteQuery_FailsOnSuccesfulStreamWithNoToken (0.03s)
#--- PASS: TestExecuteQuery_HeadersAreSet (0.03s)
#--- PASS: TestExecuteQuery_PrepareQueryRespectsDeadline (2.02s)
#--- PASS: TestExecuteQuery_ConcurrentRequests (6.04s)
#--- PASS: TestExecuteQuery_RetryTest_FirstResponse (0.09s)
#--- PASS: TestExecuteQuery_RetryTest_MidStream (0.13s)
#--- PASS: TestExecuteQuery_RetryTest_TokenWithoutData (0.14s)
#--- PASS: TestExecuteQuery_RetryTest_ErrorAfterFinalData (0.12s)
#--- PASS: TestExecuteQuery_RetryTest_ResetPartialBatch (0.13s)
#--- PASS: TestExecuteQuery_RetryTest_ResetCompleteBatch (0.14s)
#--- PASS: TestExecuteQuery_ChecksumMismatch (0.03s)

# Stream reading tests b/461232110
#go test -v \
#  -run "Simple|ChecksumMismatch" \
#  -proxy_addr=:9999
#exit_status=$?

#--- PASS: TestExecuteQuery_FailsOnSuccesfulStreamWithNoToken
#--- PASS: TestExecuteQuery_FailsOnNotEnoughData (0.03s)
#--- PASS: TestExecuteQuery_FailsOnNotEnoughDataWithCompleteRows (0.03s)
#--- PASS: TestExecuteQuery_ChecksumMismatch (0.04s)

# Response/Metadata mismatches b/461233335
#go test -v \
#  -run "TestExecuteQuery" \
#  -skip "CloseClient|FailsOnEmptyMetadata|FailsOnExecuteQueryMetadata|FailsOnInvalidType|FailsOnNotEnoughData|FailsOnNotEnoughDataWithCompleteRows|FailsOnSuccesfulStreamWithNoToken|ChecksumMismatch|FailsOnTypeMismatch|FailsOnTypeMismatchWithinMap|FailsOnTypeMismatchWithinArray|FailsOnTypeMismatchWithinStruct|FailsOnStructMissingField|RetryTest_WithPlanRefresh|PlanRefresh" \
#  -proxy_addr=:9999
#exit_status=$?

# These next four go test commands group the currently failing ExecuteQuery
# tests into groups that exercise similar functionality and should be worked on
# together.

# Metadata tests b/461232934
#go test -v \
#  -run "RetryTest_WithPlanRefresh|PlanRefresh" \
#  -proxy_addr=:9999
#exit_status=$?

# Stream reading tests b/461232110
#go test -v \
#  -run "Simple|FailsOnNotEnoughData|FailsOnSuccesfulStreamWithNoToken" \
#  -proxy_addr=:9999
#exit_status=$?

#--- PASS: TestExecuteQuery_FailsOnSuccesfulStreamWithNoToken
#--- PASS: TestExecuteQuery_FailsOnNotEnoughData (0.03s)
#--- PASS: TestExecuteQuery_FailsOnNotEnoughDataWithCompleteRows (0.03s)

# ChecksumMismatch"

# Response/Metadata mismatches b/461233335
#go test -v \
#  -run "FailsOnTypeMismatch|FailsOnTypeMismatchWithinMap|FailsOnTypeMismatchWithinArray|FailsOnTypeMismatchWithinStruct|FailsOnStructMissingField" \
#  -proxy_addr=:9999
#exit_status=$?

# QueryPlan refresh tests b/461233613
#  -run "PlanRefresh" \
#go test -v \
#  -run "TestExecuteQuery_PlanRefresh_AfterResumeTokenCausesError" \
#  -proxy_addr=:9999
#exit_status=$?

#--- PASS: TestExecuteQuery_PlanRefresh (0.18s)
#--- PASS: TestExecuteQuery_PlanRefresh_WithMetadataChange (0.13s)
#--- PASS: TestExecuteQuery_PlanRefresh_Retries (0.00s)

# will need to reconcile the Internal error this case expects to retry
# with the Internal error that is not retried in FailsOnNotEnoughData
#--- FAIL: TestExecuteQuery_PlanRefresh_RecoversAfterPermanentError (0.00s)

# can probably fix, but both involve tokens so lets get the token tests working
#--- FAIL: TestExecuteQuery_PlanRefresh_AfterResumeTokenCausesError (0.03s)
#--- FAIL: TestExecuteQuery_RetryTest_WithPlanRefresh (0.15s)

# missing feature
#--- FAIL: TestExecuteQuery_PlanRefresh_RespectsDeadline (2.81s)

# Remove the entire module cache, including unpacked source code of versioned
# dependencies.
go clean -modcache
popd >/dev/null

# Stop the proxy
kill $proxy_pid

exit "${exit_status}"
