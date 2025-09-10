// Copyright 2025 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "google/cloud/bigtable/benchmarks/benchmark.h"
#include "gperftools/profiler.h"
#include <chrono>
#include <future>
#include <iomanip>
#include <iostream>
#include <sstream>

char const kDescription[] =
    R"""(Measure the throughput of `Table::AsyncReadRows()`.

This benchmark measures the throughput of `AsyncReadRows()` on a "typical" table
used for serving data.  The benchmark:
- Creates a table with 10,000,000 rows, each row with a single column family,
  but with 10 columns.
- If there is a collision on the table name the benchmark aborts immediately.
- The benchmark populates the table during an initial phase. The benchmark uses
  `BulkApply()` to populate the table, multiple threads to populate in parallel,
  and provides an initial split hint when creating the table.
- The benchmark reports the throughput of this bulk upload phase.

After successfully uploading the initial data, the main phase of the benchmark
starts. During this phase the benchmark will:

- Execute the following block with different scan sizes:
  - Execute the following loop for S seconds:
    - Pick one of the 10,000,000 keys at random, with uniform probability.
    - Scan the number rows starting the key selected above.
    - Go back and pick a new random key.

The benchmark will report throughput in rows per second for each scans with 100,
1,000, 10,000, 100,000, and 1,000,000 rows.

Using a command-line parameter the benchmark can be configured to create a local
gRPC server that implements the Cloud Bigtable APIs used by the benchmark.  If
this parameter is not used, the benchmark uses the default configuration, that
is, a production instance of Cloud Bigtable unless the CLOUD_BIGTABLE_EMULATOR
environment variable is set.
)""";

/// Helper functions and types for the scan_throughput_benchmark.
namespace {
namespace bigtable = ::google::cloud::bigtable;
using bigtable::benchmarks::Benchmark;
using bigtable::benchmarks::BenchmarkResult;
using bigtable::benchmarks::FormatDuration;
using bigtable::benchmarks::kColumnFamily;

constexpr int kScanSizes[] = {100, 1000, 10000, 100000, 1000000};

/// Run an iteration of the test.
BenchmarkResult RunBenchmark(bigtable::benchmarks::Benchmark const& benchmark,
                             std::int64_t table_size, std::int64_t scan_size,
                             std::chrono::seconds test_duration,
                             bool enable_metrics);
}  // anonymous namespace

int main(int argc, char* argv[]) {
  auto options = bigtable::benchmarks::ParseArgs(argc, argv, kDescription);
  if (!options) {
    std::cerr << options.status() << "\n";
    return -1;
  }
  if (options->exit_after_parse) return 0;

  std::cout << "test_duration=" << options->test_duration.count() << "s\n";
  std::cout << "table_size=" << options->table_size << "\n";
  std::cout << "enable_metrics=" << (options->enable_metrics ? "true" : "false")
            << "\n";
  Benchmark benchmark(*options);

  // Create and populate the table for the benchmark.
  benchmark.CreateTable();
  auto populate_results = benchmark.PopulateTable();
  Benchmark::PrintThroughputResult(std::cout, "scant", "Upload",
                                   *populate_results);

  //  ProfilerStart("/tmp/cpu_profile.prof");
  std::map<std::string, BenchmarkResult> results_by_size;
  for (auto scan_size : kScanSizes) {
    std::cout << "# Running benchmark [" << scan_size << "] " << std::flush;
    auto start = std::chrono::steady_clock::now();
    auto combined =
        RunBenchmark(benchmark, options->table_size, scan_size,
                     options->test_duration, options->enable_metrics);
    using std::chrono::duration_cast;
    combined.elapsed = duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - start);
    std::cout << " DONE. Elapsed=" << FormatDuration(combined.elapsed)
              << ", Ops=" << combined.operations.size()
              << ", Rows=" << combined.row_count << "\n";
    auto op_name = "AsyncScan(" + std::to_string(scan_size) + ")";
    Benchmark::PrintLatencyResult(std::cout, "scant", op_name, combined);
    results_by_size[op_name] = std::move(combined);
  }
  //  ProfilerStop();

  std::cout << bigtable::benchmarks::Benchmark::ResultsCsvHeader() << "\n";
  benchmark.PrintResultCsv(std::cout, "scant", "BulkApply()", "Latency",
                           *populate_results);
  for (auto& kv : results_by_size) {
    benchmark.PrintResultCsv(std::cout, "scant", kv.first, "IterationTime",
                             kv.second);
  }

  benchmark.DeleteTable();

  return 0;
}

namespace {

BenchmarkResult RunBenchmark(bigtable::benchmarks::Benchmark const& benchmark,
                             std::int64_t table_size, std::int64_t scan_size,
                             std::chrono::seconds test_duration,
                             bool enable_metrics) {
  BenchmarkResult result = {};

  auto options = google::cloud::Options{}.set<bigtable::EnableMetricsOption>(
      enable_metrics);
  auto table = benchmark.MakeTable(options);

  auto generator = google::cloud::internal::MakeDefaultPRNG();
  std::uniform_int_distribution<std::int64_t> prng(0,
                                                   table_size - scan_size - 1);

  auto test_start = std::chrono::steady_clock::now();
  while (std::chrono::steady_clock::now() < test_start + test_duration) {
    auto range =
        bigtable::RowRange::StartingAt(benchmark.MakeKey(prng(generator)));
    std::promise<bool> all_done;
    std::future<bool> all_done_future = all_done.get_future();

    auto op = [&all_done, &all_done_future, &table, &scan_size,
               &range]() -> google::cloud::Status {
      table.AsyncReadRows(
          [](auto const&) { return google::cloud::make_ready_future(true); },
          [&all_done](auto const&) { all_done.set_value(true); },
          bigtable::RowSet(std::move(range)), scan_size,
          bigtable::Filter::ColumnRangeClosed(kColumnFamily, "field0",
                                              "field9"));
      all_done_future.wait();
      return {};
    };

    result.operations.push_back(Benchmark::TimeOperation(op));
    result.row_count += scan_size;
  }

  return result;
}

}  // anonymous namespace
