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
#include "google/cloud/bigtable/internal/bigtable_stub.h"
#include "google/cloud/internal/unified_grpc_credentials.h"
#ifdef PROFILE
#include "google/cloud/internal/getenv.h"
#include "gperftools/profiler.h"
#endif
#include <google/bigtable/admin/v2/bigtable_table_admin.grpc.pb.h>
#include <google/bigtable/v2/bigtable.grpc.pb.h>
#include <grpcpp/client_context.h>
#include <chrono>
#include <future>
#include <iomanip>
#include <iostream>
#include <sstream>

#define SYNC 1

char const kDescription[] = R"""(Measure the throughput of `Table::ReadRows()`.

This benchmark measures the throughput of `ReadRows()` on a "typical" table used
for serving data.  The benchmark:
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

std::string ToString(grpc_arg const& arg) {
  std::string output;
  output = absl::StrCat("{{", arg.key, "}, {");
  switch (arg.type) {
    case GRPC_ARG_STRING:
      absl::StrAppend(&output, arg.value.string, "}},");
      break;
    case GRPC_ARG_INTEGER:
      absl::StrAppend(&output, arg.value.integer, "}},");
      break;
    case GRPC_ARG_POINTER:
      absl::StrAppend(&output, "some pointer}},");
      break;
    default:
      absl::StrAppend(&output, "UNKNOWN_ARG_TYPE}},");
  }
  return output;
}

constexpr int kScanSizes[] = {100, 1000, 10000, 100000, 1000000};

auto constexpr kDataEndpoint = "bigtable.googleapis.com";

class GrpcClient {
 public:
  GrpcClient() {
    auto options =
        google::cloud::Options{}.set<google::cloud::UnifiedCredentialsOption>(
            google::cloud::MakeGoogleDefaultCredentials());
    options = google::cloud::bigtable::internal::DefaultDataOptions(options);
    // potentially create background threads
    auto auth_strategy =
        google::cloud::internal::CreateAuthenticationStrategy({}, options);
    grpc::ChannelArguments channel_args =
        google::cloud::internal::MakeChannelArguments(options);

    std::cout << "GrpcClient Channel Args:\n";
    grpc_channel_args args = channel_args.c_channel_args();
    for (size_t i = 0; i < args.num_args; ++i) {
      grpc_arg a = args.args[i];
      std::cout << ToString(a) << std::endl;
    }

    auto data_channel =
        auth_strategy->CreateChannel(kDataEndpoint, channel_args);
    data_stub_ =
        google::bigtable::v2::Bigtable::NewStub(std::move(data_channel));
  }

  std::unique_ptr<
      ::grpc::ClientReaderInterface<::google::bigtable::v2::ReadRowsResponse>>
  ReadRows(grpc::ClientContext* context,
           google::bigtable::v2::ReadRowsRequest const& request) {
    return data_stub_->ReadRows(context, request);
  }

  std::unique_ptr<::grpc::ClientAsyncReaderInterface<
      ::google::bigtable::v2::ReadRowsResponse>>
  AsyncReadRows(grpc::ClientContext* context, grpc::CompletionQueue* cq,
                google::bigtable::v2::ReadRowsRequest const& request) {
    return data_stub_->AsyncReadRows(context, request, cq, (void*)1);
  }

  google::bigtable::v2::ReadRowsRequest request;
  google::bigtable::v2::ReadRowsResponse response;

 private:
  std::unique_ptr<google::bigtable::v2::Bigtable::StubInterface> data_stub_;
};

enum class Mode { kSync, kAsync };

/// Run an iteration of the test.
BenchmarkResult RunBenchmark(bigtable::benchmarks::Benchmark const& benchmark,
                             google::cloud::internal::DefaultPRNG& generator,
                             std::uniform_int_distribution<std::int64_t> prng,
                             std::int64_t scan_size,
                             std::chrono::seconds test_duration,
                             std::string const& table_name,
                             GrpcClient& grpc_client, Mode mode);

}  // anonymous namespace

int main(int argc, char* argv[]) {
  auto options = bigtable::benchmarks::ParseArgs(argc, argv, kDescription);
  if (!options) {
    std::cerr << options.status() << "\n";
    return -1;
  }
  if (options->exit_after_parse) return 0;

  options->enable_metrics = false;
  std::cout << "test_duration=" << options->test_duration.count() << "s\n";
  std::cout << "table_size=" << options->table_size << "\n";
  std::cout << "enable_metrics=" << (options->enable_metrics ? "true" : "false")
            << "\n";
  Benchmark benchmark(*options);

  // Create and populate the table for the benchmark.
  auto table_id = benchmark.CreateTable();
  std::string table_name =
      absl::StrFormat("projects/%s/instances/%s/tables/%s", options->project_id,
                      options->instance_id, table_id);
  std::cout << "benchmark.CreateTable()=" << table_name << std::endl;
  auto populate_results = benchmark.PopulateTable();
  Benchmark::PrintThroughputResult(std::cout, "scant", "Upload",
                                   *populate_results);

  GrpcClient grpc_client;
  auto generator = google::cloud::internal::MakeDefaultPRNG();

#ifdef PROFILE
  auto profile_data_path = google::cloud::internal::GetEnv("PROFILER_PATH");
  if (profile_data_path) {
    profile_data_path = absl::StrCat(*profile_data_path, ".sync");
    ProfilerStart(profile_data_path->c_str());
  }
  auto profiler_start = std::chrono::steady_clock::now();
#endif  // PROFILE
  std::map<std::string, BenchmarkResult> sync_results_by_size;
  for (auto scan_size : kScanSizes) {
    std::uniform_int_distribution<std::int64_t> prng(
        0, options->table_size - scan_size - 1);

    std::cout << "# Running benchmark [" << scan_size << "] " << std::flush;
    auto start = std::chrono::steady_clock::now();
    auto combined = RunBenchmark(benchmark, generator, prng, scan_size,
                                 options->test_duration, table_name,
                                 grpc_client, Mode::kSync);
    using std::chrono::duration_cast;
    combined.elapsed = duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - start);
    std::cout << " DONE. Elapsed=" << FormatDuration(combined.elapsed)
              << ", Ops=" << combined.operations.size()
              << ", Rows=" << combined.row_count << "\n";
    auto op_name = "Scan(" + std::to_string(scan_size) + ")";
    Benchmark::PrintLatencyResult(std::cout, "scant", op_name, combined);
    sync_results_by_size[op_name] = std::move(combined);
  }
#ifdef PROFILE
  auto profiler_stop = std::chrono::steady_clock::now();
  if (profile_data_path) {
    ProfilerStop();
    std::cout << "Steady clock sync profiling duration="
              << FormatDuration(profiler_stop - profiler_start) << "\n";
  }

  profile_data_path = google::cloud::internal::GetEnv("PROFILER_PATH");
  if (profile_data_path) {
    profile_data_path = absl::StrCat(*profile_data_path, ".async");
    ProfilerStart(profile_data_path->c_str());
  }
  profiler_start = std::chrono::steady_clock::now();
#endif  // PROFILE
  std::map<std::string, BenchmarkResult> async_results_by_size;
  for (auto scan_size : kScanSizes) {
    std::uniform_int_distribution<std::int64_t> prng(
        0, options->table_size - scan_size - 1);

    std::cout << "# Running benchmark [" << scan_size << "] " << std::flush;
    auto start = std::chrono::steady_clock::now();
    auto combined = RunBenchmark(benchmark, generator, prng, scan_size,
                                 options->test_duration, table_name,
                                 grpc_client, Mode::kAsync);
    using std::chrono::duration_cast;
    combined.elapsed = duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - start);
    std::cout << " DONE. Elapsed=" << FormatDuration(combined.elapsed)
              << ", Ops=" << combined.operations.size()
              << ", Rows=" << combined.row_count << "\n";
    auto op_name = "AsyncScan(" + std::to_string(scan_size) + ")";
    Benchmark::PrintLatencyResult(std::cout, "scant", op_name, combined);
    async_results_by_size[op_name] = std::move(combined);
  }
#ifdef PROFILE
  profiler_stop = std::chrono::steady_clock::now();
  if (profile_data_path) {
    ProfilerStop();
    std::cout << "Steady clock async profiling duration="
              << FormatDuration(profiler_stop - profiler_start) << "\n";
  }
#endif  // PROFILE

  std::cout << bigtable::benchmarks::Benchmark::ResultsCsvHeader() << "\n";
  benchmark.PrintResultCsv(std::cout, "scant", "BulkApply()", "Latency",
                           *populate_results);
  for (auto& kv : sync_results_by_size) {
    benchmark.PrintResultCsv(std::cout, "scant", kv.first, "IterationTime",
                             kv.second);
  }
  for (auto& kv : async_results_by_size) {
    benchmark.PrintResultCsv(std::cout, "scant", kv.first, "IterationTime",
                             kv.second);
  }

  benchmark.DeleteTable();
  return 0;
}

namespace {

BenchmarkResult RunBenchmark(bigtable::benchmarks::Benchmark const& benchmark,
                             google::cloud::internal::DefaultPRNG& generator,
                             std::uniform_int_distribution<std::int64_t> prng,
                             std::int64_t scan_size,
                             std::chrono::seconds test_duration,
                             std::string const& table_name, GrpcClient& client,
                             Mode mode) {
  BenchmarkResult result = {};

  auto test_start = std::chrono::steady_clock::now();
  while (std::chrono::steady_clock::now() < test_start + test_duration) {
    auto range =
        bigtable::RowRange::StartingAt(benchmark.MakeKey(prng(generator)));
    long count = 0;  // NOLINT(google-runtime-int)

    if (mode == Mode::kSync) {
      auto op = [&count, &client, &scan_size, &range,
                 &table_name]() -> google::cloud::Status {
        bigtable::RowSet row_set(std::move(range));
        client.request.Clear();
        client.request.set_table_name(table_name);
        *client.request.mutable_rows() = std::move(row_set).as_proto();
        *client.request.mutable_filter() =
            bigtable::Filter::ColumnRangeClosed(kColumnFamily, "field0",
                                                "field9")
                .as_proto();
        client.request.set_rows_limit(scan_size);

        grpc::ClientContext context;
        context.set_authority(kDataEndpoint);
        auto stream = client.ReadRows(&context, client.request);

        client.response.Clear();
        bool keep_reading = true;
        while (keep_reading) {
          keep_reading = stream->Read(&client.response);
          for (auto i = 0; i < client.response.chunks_size(); ++i) {
            auto const& chunk = client.response.chunks(i);
            if (chunk.has_commit_row() && chunk.commit_row()) {
              ++count;
            }
          }
          client.response.Clear();
        }

        return {};
      };
      result.operations.push_back(Benchmark::TimeOperation(op));
    } else {
      auto op = [&count, &client, &scan_size, &range,
                 &table_name]() -> google::cloud::Status {
        bigtable::RowSet row_set(std::move(range));
        client.request.Clear();
        client.request.set_table_name(table_name);
        *client.request.mutable_rows() = std::move(row_set).as_proto();
        *client.request.mutable_filter() =
            bigtable::Filter::ColumnRangeClosed(kColumnFamily, "field0",
                                                "field9")
                .as_proto();
        client.request.set_rows_limit(scan_size);

        grpc::ClientContext context;
        context.set_authority(kDataEndpoint);

        grpc::CompletionQueue cq;

        auto reader = client.AsyncReadRows(&context, &cq, client.request);
        client.response.Clear();
        void* read_tag = (void*)2;
        reader->Read(&client.response, read_tag);

        void* got_tag;
        bool ok = false;

        while (cq.Next(&got_tag, &ok)) {
          if (got_tag == (void*)1) {
            // Initial tag, AsyncReadRows is ready.
            continue;
          }
          if (got_tag == read_tag) {
            if (ok) {
              for (auto const& chunk : client.response.chunks()) {
                if (!chunk.row_key().empty()) {
                  count++;
                }
              }
              reader->Read(&client.response, read_tag);
            } else {
              // Stream is done.
              break;
            }
          }
        }

        grpc::Status status;
        void* finish_tag = (void*)3;
        reader->Finish(&status, finish_tag);
        while (cq.Next(&got_tag, &ok) && got_tag != finish_tag) {
        }

        cq.Shutdown();
        while (cq.Next(&got_tag, &ok)) {
        }

        if (!status.ok()) {
          std::cerr << "RPC failed: " << status.error_message() << std::endl;
          std::exit(1);
        }

        return {};
      };
      result.operations.push_back(Benchmark::TimeOperation(op));
    }

    //    std::cout << "count=" << count << std::endl;
    result.row_count += count;
  }
  return result;
}

}  // anonymous namespace
