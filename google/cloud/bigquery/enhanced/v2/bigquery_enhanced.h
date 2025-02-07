// Copyright 2024 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BIGQUERY_ENHANCED_V2_BIGQUERY_ENHANCED_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BIGQUERY_ENHANCED_V2_BIGQUERY_ENHANCED_H
#if 0
#include "google/cloud/bigquery/jobs/v2/jobs_client.h"
#include "google/cloud/bigquery/jobs/v2/jobs_proto_export.h"
#include "google/cloud/future.h"
#include "google/cloud/options.h"
#include "google/cloud/status_or.h"
#include "google/cloud/version.h"
#include <google/protobuf/timestamp.pb.h>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace google {
namespace cloud {
namespace bigquery_enhanced_v2 {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

#if 0
//// absl
//namespace absl {
//template <typename T>
//struct optional {};
//template <typename ...Ts >
//struct variant {};
//}
//
//// protobuf types
//namespace google::protobuf {
//struct Message {};
//struct Timestamp {};
//}
//
//// apache arrow types
//namespace arrow {
//struct RecordBatch {};
//struct Schema {};
//namespace io {
//struct BufferReader {};
//}
//
//namespace ipc {
//struct IpcReadOptions {};
//}
//
//}
//
//// common google::cloud types
//struct Options {};
//template <typename T>
//struct StatusOr {};
//template <typename T>
//struct StreamRange {};
//template <typename T>
//struct future {};
//struct CompletionQueue {};
//struct RowStream {};  // refactored spanner::RowStream to use BigQuery datatypes
//
//// generated common protos
//namespace google::cloud::cpp::bigquery::v2 {
//struct DmlStatistics {
//  std::string deleted_row_count;
//  std::string inserted_row_count;
//  std::string updated_row_count;
//};
//
//struct ErrorProto {};
//struct Job {};
//struct JobCreationReason {};
//struct JobReference {};
//struct QueryRequest {};
//struct SessionInfo {};
//struct TableDataInsertAllResponse {};
//struct TableSchema {};
//}
//
//// generated Jobs service specific protos
//namespace google::cloud::cpp::bigquery::jobs::v2 {
//struct InsertJobRequest {};
//struct GetQueryResultsRequest {};
//struct QueryRequest {};
//}
//
//// generated Tabledata service specific protos
//namespace google::cloud::cpp::bigquery::tabledata::v2 {
//struct ListTabledataRequest {};
//}
//
//// BigQuery Storage protos
//namespace google::cloud::bigquery::storage::v1 {
//  struct ArrowSchema{};
//  struct ReadRowsResponse{};
//  struct TableModifiers {};
//  struct TableReadOptions {};
//  enum AppendRowsRequest_MissingValueInterpretation {};
//}
#endif

// fields only found in QueryResponse proto returned from Jobs.Query
struct QueryResponseMetadata {
  absl::optional<google::cloud::cpp::bigquery::v2::JobCreationReason> job_creation_reason;
  absl::optional<std::string> query_id;
  absl::optional<google::cloud::cpp::bigquery::v2::SessionInfo> session_info;
  absl::optional<google::cloud::cpp::bigquery::v2::DmlStatistics> dml_stats;
};

// output fields from BigQuery Storage Read
struct ReadMetadata {
  std::string session_name;
  google::protobuf::Timestamp expire_time;
  std::string table_name;
  std::int64_t estimated_total_bytes_scanned;
  std::int64_t estimated_total_physical_file_size;  // BigLake only
  std::int64_t estimated_row_count;
  std::string trace_id;
};

struct QueryResultsMetadata {
  // these are fields preset in both
  // GetQueryResultsResponse proto and
  // QueryResponse proto
  bool cache_hit;
  std::vector<google::cloud::cpp::bigquery::v2::ErrorProto> errors;
  std::string etag;
  bool job_complete;
  google::cloud::cpp::bigquery::v2::JobReference job_reference;
  absl::optional<std::string> num_dml_affected_rows;
  absl::optional<google::cloud::cpp::bigquery::v2::TableSchema> schema;
  std::string total_bytes_processed;
  // unlcear if total_rows is populated for DML queries
  std::string total_rows;
  absl::optional<QueryResponseMetadata> query_response_metadata;
  absl::optional<ReadMetadata> read_metadata;
};

// By returning a vector of readers, the user can then distribute them across threads
// as they desire.
struct ArrowData {
  // The serialized schema is available in the ReadSession from the CreateReadSession rpc
  std::shared_ptr<google::cloud::bigquery::storage::v1::ArrowSchema const> arrow_schema;
  // The vector is populated with the results from calling ReadRows on each of the streams
  // in the ReadSession from the CreateReadSession rpc
  std::vector<StreamRange<google::cloud::bigquery::storage::v1::ReadRowsResponse>> readers;
};

struct QueryResults {
  QueryResultsMetadata metadata;
  absl::variant<RowStream, ArrowData> data;
};

// This is the format the user gets the data in, not necessarily what transport is used.
// The library could potentially get the data via BigQuery Storage Read, as
// arrow::RecordBatch, then turn it into native c++ types.
enum class DataFormat {
    kNativeCpp = 0,  // default
    kArrowData = 1
};

// This option can be set at the Client, Connection, or per Call, to select how
// the query results/table data is returned.
struct DataFormatOption {
  using Type = DataFormat;
};

// By default, the BigQuery library uses the BigQuery Storage service to read and write data
// where possible, this options forces the library to only use the JSON/REST endpoint.
struct ForceRestOption {
  using Type = bool;  // default is false
};

//
// Jobs methods
//

// Inserts a Job and sets the promise associate with the future when the Job completes.
// Uses a CompletionQueue to perform polling and retrival of the Job from the service.
// Immediately returns a JobReference that can be used in another process to resume.
// These methods are in addition to existing Jobs methods.
std::pair<StatusOr<google::cloud::cpp::bigquery::v2::JobReference>,
          future<StatusOr<google::cloud::cpp::bigquery::v2::Job>>> AsyncInsertJob(
      std::string const& project_id,
      google::cloud::cpp::bigquery::v2::Job const& job_resource,
      Options opts = {});
std::pair<StatusOr<google::cloud::cpp::bigquery::v2::JobReference>,
          future<StatusOr<google::cloud::cpp::bigquery::v2::Job>>> AsyncInsertJob(
      google::cloud::cpp::bigquery::jobs::v2::InsertJobRequest const& request,
      Options opts = {});

// This reason this method exists is to make fast queries resulting in small set of
// rows in exactly one rpc call.
// Executes the query immediately and only returns the first page of result rows.
// Response contains a JobReference that can be passed to GetQueryResults to
// retrieve all the rows resulting from the query.
// Ignores DataFormatOptions other than DataFormat::kNativeCpp
// Replaces Jobs.Query
StatusOr<QueryResults>Query(
    std::string const& project_id,
    google::cloud::cpp::bigquery::v2::QueryRequest const& query_request_resource,
    Options opts = {});


//
// Data reading methods
//

// Options made available by BigQuery Storage Read
struct TableModifiersOption {
    using Type = google::cloud::bigquery::storage::v1::TableModifiers;
};

struct TabelReadOption {
  using Type = google::cloud::bigquery::storage::v1::TableReadOptions;
};

// Allows full specification of request
// Replaces Jobs.GetQueryResults
StatusOr<QueryResults> GetQueryResults(
    google::cloud::cpp::bigquery::jobs::v2::GetQueryResultsRequest const&,
    Options opts = {});
// Intended to be used to get remaining rows from a Jobs.Query call or
// from an AsyncInsertJob call across processes.
future<StatusOr<QueryResults>> GetQueryResults(
    google::cloud::cpp::bigquery::v2::JobReference,
    Options opts = {});
// Extracts the necessary fields from the Job parameter, intended to be used as a
// continuation for an AsyncInsertJob.
// Could also be used following a GetJob call.
// Replaces Jobs.GetQueryResults
StatusOr<QueryResults> GetQueryResults(google::cloud::cpp::bigquery::v2::Job const&,
    Options opts = {});


struct TableReadMetadata {
  std::string etag;
  std::string total_rows;

  // output fields from BigQuery Storage Read
  std::string session_name;
  google::protobuf::Timestamp expire_time;
  std::string table_name;
  std::int64_t estimated_total_bytes_scanned;
  std::int64_t estimated_total_physical_file_size;  // BigLake only
  std::int64_t estimated_row_count;
  std::string trace_id;
};

struct TableReadResults {
  TableReadMetadata metadata;
  absl::variant<RowStream, ArrowData> data;
};

// Reads rows from a Table
// Replaces Tabledata.ListTabledata
StatusOr<TableReadResults> ListTabledata(
    google::cloud::cpp::bigquery::tabledata::v2::ListTabledataRequest const&,
    Options opts = {});
// Replaces Tabledata.ListTabledata
StatusOr<TableReadResults> ListTabledata(
    std::string const& project_id,
    std::string const& dataset_id,
    std::string const& table_id,
    Options opts = {});


//
// Data writing methods
//

// There's a lot of knobs that can be adjusted for BigQuery Storage Write. We can either
// tuck them in an Option or create more overloads for the different flavors. We may have to
// do some of both.
struct WriteTraceIdOption {
    using Type = std::string;
};

struct MissingValueInterpretationOption {
    using Type = std::unordered_map<std::string,
      google::cloud::bigquery::storage::v1::AppendRowsRequest_MissingValueInterpretation>;
};

struct DefaultMissingValueInterpretationOption {
  using Type = google::cloud::bigquery::storage::v1::AppendRowsRequest_MissingValueInterpretation;
};

// Writes rows into a Table from data present in json_rows
// Replaces Tabledata.InsertAll
// Does not support TableDataInsertAllRequest.template_suffix field (at present)
// This function would need to contruct a protobuf schema from the TableSchema returned
// from GetWriteStream rpc and then translate the json into protobuf message, serialize, and
// send out the wire.
// Uses the CompletionQueue and its BackgroundThreads to spool up multiple writers if needed and
// threads are available.
StatusOr<google::cloud::cpp::bigquery::v2::TableDataInsertAllResponse>
InsertAll(std::string const& project_id, std::string const& dataset_id,
        std::string const& table_id,
        std::vector<std::string> const& json_rows,
        Options opts = {});
// Writes rows into a Table from data present in proto_rows
// Replaces Tabledata.InsertAll
// Does not support TableDataInsertAllRequest.template_suffix field (at present)
// This function would need to sanitize the Message::Descriptor before sending.
// Uses the CompletionQueue and its BackgroundThreads to spool up multiple writers if needed and
// threads are available.
StatusOr<google::cloud::cpp::bigquery::v2::TableDataInsertAllResponse>
InsertAll(std::string const& project_id, std::string const& dataset_id,
        std::string const& table_id,
        std::vector<google::protobuf::Message> const& proto_rows,
        Options opts = {});

// writing from a vector is fine for small writes, what if all the data to be written can't fit
// into memory... GCS does this via ObjectWriteStream, we would need something similar.

// needs a method to keep a bidir stream open to write to forever and ever
// likely the same solution as writing more data than can fit into memory.


#if 0
// Helper functions
// Reads serialized bytes into an arrow::Schema
StatusOr<std::shared_ptr<arrow::Schema>> ReadArrowSchema(
    std::shared_ptr<google::cloud::bigquery::storage::v1::ArrowSchema const> arrow_schema) {
  arrow::io::BufferReader schema_buffer_reader(arrow_schema.serialized_schema());
  arrow::ipc::DictionaryMemo dictionary_memo;
  auto result =
      arrow::ipc::ReadSchema(&schema_buffer_reader, dictionary_memo.get());
  if (!result.ok()) {
      return google::cloud::internal::InternalError("arrow error");
    }
  std::shared_ptr<arrow::Schema> schema = result.ValueOrDie();
  return schema;
}

// iterates through a ReadStream and creates arrow::RecordBatch elements from the serialized
// bytes.
StatusOr<std::vector<std::shared_ptr<arrow::RecordBatch>>> ReadArrowDataStream(
    std::shared_ptr<arrow::Schema const> arrow_schema,
    StreamRange<google::cloud::bigquery::storage::v1::ReadRowsResponse> reader) {
  std::vector<std::shared_ptr<arrow::RecordBatch>> batches;
  arrow::ipc::IpcReadOptions read_options;
  arrow::ipc::DictionaryMemo dictionary_memo;
  for (auto const& record_batch_bytes : reader) {
    arrow::io::BufferReader record_buffer_reader(
        record_batch_bytes->arrow_record_batch().serialized_record_batch());

    auto record_batch = arrow::ipc::ReadRecordBatch(
        arrow_schema, dictionary_memo.get(), read_options, &record_buffer_reader);
    if (!record_batch.ok()) {
      return google::cloud::internal::InternalError("arrow error");
    }
    batches.push_back(std::move(record_batch.ValueOrDie()));
  }
  return batches;
}
#endif




GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigquery_enhanced_v2
}  // namespace cloud
}  // namespace google
#endif
#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BIGQUERY_ENHANCED_V2_BIGQUERY_ENHANCED_H
