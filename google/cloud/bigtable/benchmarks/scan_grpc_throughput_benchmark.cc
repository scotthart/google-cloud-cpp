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
#include "gperftools/profiler.h"
#include <google/bigtable/v2/bigtable.grpc.pb.h>
#include <google/bigtable/admin/v2/bigtable_table_admin.grpc.pb.h>
#include <grpcpp/client_context.h>
#include <chrono>
#include <future>
#include <iomanip>
#include <iostream>
#include <sstream>

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

constexpr int kScanSizes[] = {100, 1000, 10000, 100000, 1000000};

/// Run an iteration of the test.
BenchmarkResult RunBenchmark(bigtable::benchmarks::Benchmark const& benchmark,
                             std::int64_t table_size, std::int64_t scan_size,
                             std::chrono::seconds test_duration);
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
                     options->test_duration);
    using std::chrono::duration_cast;
    combined.elapsed = duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - start);
    std::cout << " DONE. Elapsed=" << FormatDuration(combined.elapsed)
              << ", Ops=" << combined.operations.size()
              << ", Rows=" << combined.row_count << "\n";
    auto op_name = "Scan(" + std::to_string(scan_size) + ")";
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

auto constexpr kDataEndpoint = "bigtable.googleapis.com";
auto constexpr kTableAdminEndpoint = "bigtableadmin.googleapis.com";


class GrpcClient {
 public:
  GrpcClient() {
    grpc::ChannelArguments channel_args;
    channel_args.SetMaxReceiveMessageSize(268435456);
    channel_args.SetMaxSendMessageSize(268435456);
    channel_args.SetInt("grpc.keepalive_time_ms", 30000);
    channel_args.SetInt("grpc.keepalive_timeout_ms", 10000);


   background_threads_ =
      google::cloud::internal::MakeBackgroundThreadsFactory(google::cloud::Options{})();

   auto options = google::cloud::Options{}.set<google::cloud::UnifiedCredentialsOption>(
       google::cloud::MakeGoogleDefaultCredentials());
    auto auth_strategy = google::cloud::internal::CreateAuthenticationStrategy(
        background_threads_->cq(), options);
    assert(auth_strategy != nullptr);

    auto data_channel = auth_strategy->CreateChannel(kDataEndpoint, channel_args);
    assert(data_channel != nullptr);
    auto table_channel = auth_strategy->CreateChannel(kTableAdminEndpoint, channel_args);
    assert(table_channel != nullptr);



    data_stub_ = google::bigtable::v2::Bigtable::NewStub(std::move(data_channel));
    assert(data_stub_ != nullptr);
    table_stub_ = google::bigtable::admin::v2::BigtableTableAdmin::NewStub(std::move(table_channel));
    assert(table_stub_ != nullptr);
  }

  std::unique_ptr<
      ::grpc::ClientReaderInterface<::google::bigtable::v2::ReadRowsResponse>>
  ReadRows(grpc::ClientContext* context, google::bigtable::v2::ReadRowsRequest const& request) {
    return data_stub_->ReadRows(context, request);
  }

  grpc::Status GetTable(google::bigtable::admin::v2::GetTableRequest const& request,
                       google::bigtable::admin::v2::Table* response) {
    std::cout << __PRETTY_FUNCTION__  << std::endl;
    grpc::ClientContext context;
    context.set_authority(kTableAdminEndpoint);
    auto status = table_stub_->GetTable(&context, request, response);
    std::cout << __PRETTY_FUNCTION__ << ": POST CALL" << std::endl;
    return status;
  }

 private:
  std::unique_ptr<google::cloud::BackgroundThreads> background_threads_;
//  std::shared_ptr<grpc::ClientContext> context_;
  std::unique_ptr<google::bigtable::v2::Bigtable::StubInterface> data_stub_;
  std::unique_ptr<google::bigtable::admin::v2::BigtableTableAdmin::StubInterface> table_stub_;
};

BenchmarkResult RunBenchmark(bigtable::benchmarks::Benchmark const& benchmark,
                             std::int64_t table_size, std::int64_t scan_size,
                             std::chrono::seconds test_duration) {
  BenchmarkResult result = {};

  //  auto options =
  //  google::cloud::Options{}.set<bigtable::EnableMetricsOption>(
  //      enable_metrics);
  auto table = benchmark.MakeTable();
  std::string table_name = table.table_name();

  std::cout << "table_name=" << table_name << std::endl;

  GrpcClient client;
#if 0
  {
    google::bigtable::admin::v2::GetTableRequest request;
    request.set_name(table_name);
    google::bigtable::admin::v2::Table response;
    auto status = client.GetTable(request, &response);
    if (status.error_code() != grpc::StatusCode::OK) {
      std::cout << "status.error_code()=" << status.error_code() << std::endl;
      std::cout << "status.error_message()=" << status.error_message() << std::endl;
      std::exit(1);
    }
    std::cout << "table=\n" << response.DebugString() << std::endl;
  }
#endif

  auto generator = google::cloud::internal::MakeDefaultPRNG();
  std::uniform_int_distribution<std::int64_t> prng(0,
                                                   table_size - scan_size - 1);

  google::bigtable::v2::ReadRowsRequest request;
  google::bigtable::v2::ReadRowsResponse response;

  auto test_start = std::chrono::steady_clock::now();
  while (std::chrono::steady_clock::now() < test_start + test_duration) {
    auto range =
        bigtable::RowRange::StartingAt(benchmark.MakeKey(prng(generator)));

    long count = 0;  // NOLINT(google-runtime-int)
                     //    auto op = [&count, &table, &scan_size, &range]() ->
                     //    google::cloud::Status {
                     //      auto reader =
    //          table.ReadRows(bigtable::RowSet(std::move(range)), scan_size,
    //                         bigtable::Filter::ColumnRangeClosed(
    //                             kColumnFamily, "field0", "field9"));
    //      for (auto& row : reader) {
    //        if (!row) {
    //          return row.status();
    //        }
    //        ++count;
    //      }
    //      return google::cloud::Status{};
    //    };

    auto op = [&count, &client, &scan_size, &range, &table_name,
    &request, &response]() -> google::cloud::Status {
      bigtable::RowSet row_set(std::move(range));
      request.Clear();
      request.set_table_name(table_name);
      *request.mutable_rows() = std::move(row_set).as_proto();
      *request.mutable_filter() = bigtable::Filter::ColumnRangeClosed(
                                 kColumnFamily, "field0", "field9").as_proto();
      request.set_rows_limit(scan_size);

      grpc::ClientContext context;
      context.set_authority(kDataEndpoint);
      auto stream = client.ReadRows(&context, request);

      response.Clear();
      while (stream->Read(&response)) {
        std::cout << "chunks_size=" << response.chunks_size() << std::endl;
        for (auto i = 0; i < response.chunks_size(); ++i) {
          auto const& chunk = response.chunks(i);
          if (chunk.has_commit_row() && chunk.commit_row()) {
            ++count;
          }
        }
        response.Clear();
      }
      return {};
    };

    result.operations.push_back(Benchmark::TimeOperation(op));
//    std::cout << "count=" << count << std::endl;
    result.row_count += count;
  }
  return result;
}

}  // anonymous namespace
