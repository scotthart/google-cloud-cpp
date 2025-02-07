// Copyright 2024 Google LLC
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

//! [START bigquerystorage_quickstart] [all]
#include "google/cloud/bigquery/datasets/v2/datasets_client.h"
//#include "google/cloud/bigquery/tables/v2/tables_client.h"
//#include "google/cloud/bigquery/tabledata/v2/tabledata_client.h"
#include "google/cloud/bigquery/jobs/v2/jobs_client.h"
#include "google/cloud/internal/make_status.h"
#include <google/protobuf/util/json_util.h>
#include <arrow/array/array_nested.h>
#include <arrow/array/data.h>
#include <arrow/io/memory.h>
#include <arrow/ipc/api.h>
#include <arrow/ipc/reader.h>
#include <arrow/record_batch.h>
#include <iostream>

namespace {
#if 0
auto constexpr kResponseJson = R"""({
  "kind": "bigquery#queryResponse",
  "schema": {
    "fields": [
      {
        "name": "state",
        "type": "STRING",
        "mode": "NULLABLE"
      },
      {
        "name": "gender",
        "type": "STRING",
        "mode": "NULLABLE"
      },
      {
        "name": "year",
        "type": "INTEGER",
        "mode": "NULLABLE"
      },
      {
        "name": "name",
        "type": "STRING",
        "mode": "NULLABLE"
      },
      {
        "name": "number",
        "type": "INTEGER",
        "mode": "NULLABLE"
      }
    ]
  },
  "jobReference": {
    "projectId": "",
    "jobId": "job_gJ9O1OfnkP28zDDCsiZKbPcT2jO4",
    "location": "US"
  },
  "totalRows": "5552452",
  "pageToken": "BFHPQC33RUAQAAASA4EAAEEAQCAAKGQEBAARAAJAWCXBKSVSAIFHSCRGBINWG3DPOVSC2Y3QOAWXIZLTORUW4ZZNOJSXG33VOJRWK4YRYIFKH6WZAAAAAERJL5SGCZRSMRSDKZBQGZRGKYZQHEZTKN3EG4YDGMBXMU3DKNJRGQ2DSMBXMQYGKNZYHENCIMRWMY2GMMJQGUWTEMZVGIWTINJVGQWTQMBSMYWTGNJXMRQTKMZXGAYDINQSIRQW433OME4WGNJUGE3TONRYME2GCMTEHEYTKZBUMJQWMZTFGE2TMZLGGM2WKZDDHFSDCMBZGZRGEZRUHA4GMNZZME4DGOJTHA3GKZBVMIYGMMI2N5QTSYZVGQYTONZWHBQTIYJSMQ4TCNLEGRRGCZTGMUYTKNTFMYZTKZLEMM4WIMJQHE3GEYTGGQ4DQZRXHFQTQMZZGM4DMZLEGVRDAZRRENSXMX3LINVVSSDYFUZVGSZTLFVFKTBXIFLHK4KTKRYTASDLPFLHOR3DMRTTS4SLNBSEQWLQOVEQ====",
  "rows": [
    {
      "f": [
        {
          "v": "AL"
        },
        {
          "v": "F"
        },
        {
          "v": "1916"
        },
        {
          "v": "Bessie"
        },
        {
          "v": "256"
        }
      ]
    }
  ],
  "totalBytesProcessed": "0",
  "jobComplete": true,
  "cacheHit": true,
  "queryId": "job_gJ9O1OfnkP28zDDCsiZKbPcT2jO4",
  "jobCreationReason": {
    "code": "REQUESTED"
  }
}
)""";
#endif
// json_output={
// "v":{
//  "@type":"type.googleapis.com/google.cloud.cpp.bigquery.v2.StringCell",
//  "sc":"Bessie"
// }
// }

#if 0
google::cloud::StatusOr<std::shared_ptr<arrow::RecordBatch>>
ProcessRowsInArrowFormat(
    ::google::cloud::cpp::bigquery::v2::ArrowSchema const& schema_data,
    std::int64_t row_count,
    ::google::cloud::cpp::bigquery::v2::ArrowRecordBatch const&
        record_batch_data) {
  std::string buf = schema_data.serialized_schema();
  std::cout << "buf.size()=" << buf.size() << "\n";
  std::cout << "buf=" << buf << "\n";
  arrow::io::BufferReader schema_buffer_reader(
      reinterpret_cast<uint8_t const*>(buf.data()), buf.size());
  arrow::ipc::DictionaryMemo dictionary_memo;
  auto result = arrow::ipc::ReadSchema(&schema_buffer_reader, &dictionary_memo);
  if (!result.ok()) {
    std::cout << result.status().ToString() << std::endl;
    throw result.status();
  }
  std::shared_ptr<arrow::Schema> schema = result.ValueOrDie();
    std::cout << schema->ToString() << std::endl;

//  arrow::io::BufferReader record_buffer_reader(
//      record_batch_data.serialized_record_batch());
//
//  arrow::ipc::IpcReadOptions read_options;
//  auto rb_result = arrow::ipc::ReadRecordBatch(
//      schema, &dictionary_memo, read_options, &record_buffer_reader);
//  if (!rb_result.ok())
//    return google::cloud::internal::InternalError("arrow error");
//  std::shared_ptr<arrow::RecordBatch> rb = rb_result.ValueOrDie();
  std::shared_ptr<arrow::RecordBatch> rb;
  //  std::cout << rb->ToString() << "\n";
  //  std::cout << "num_rows=" << rb->num_rows() << "\n";
  return rb;

}
#endif

//void CreateDataset() {
//  namespace datasets = ::google::cloud::bigquery_datasets_v2;
//  namespace tables = ::google::cloud::bigquery_tables_v2;
//  namespace bigquery_proto = ::google::cloud::cpp::bigquery::v2;
//
//  auto client = datasets::DatasetsClient(datasets::MakeDatasetsConnectionRest());
//  bigquery_proto::Dataset dataset;
//  dataset.mutable_dataset_reference()->set_project_id("my-project");
//  dataset.mutable_dataset_reference()->set_dataset_id("my-dataset");
//  auto d = client.InsertDataset("my-project", dataset);
//}
//
//google::cloud::cpp::bigquery::v2::TableSchema MakeSchema() {
//  return {};
//}

//void CreateTable() {
//  namespace datasets = ::google::cloud::bigquery_datasets_v2;
////  namespace tables = ::google::cloud::bigquery_tables_v2;
//  namespace bigquery_proto = ::google::cloud::cpp::bigquery::v2;
//
//  auto client = tables::TablesClient(tables::MakeTablesConnectionRest());
//  bigquery_proto::Table table;
//  table.mutable_table_reference()->set_project_id("my-project");
//  table.mutable_table_reference()->set_dataset_id("my-dataset");
//  table.mutable_table_reference()->set_table_id("my-table");
//  *table.mutable_schema() = MakeSchema();
//  auto t = client.InsertTable("my-project", "my-dataset", table);
//}

//void CreateJob() {
//  namespace jobs = ::google::cloud::bigquery_jobs_v2;
//  namespace bigquery_proto = ::google::cloud::cpp::bigquery::v2;
//
//  auto client = jobs::JobsClient(jobs::MakeJobsConnectionRest());
//  bigquery_proto::JobConfigurationQuery query;
//  query.set_query("SELECT name, state, year, sum(number) as total "
//      "FROM bigquery-public-data.usa_names.usa_1910_2013 "
//      "GROUP BY name, state, year");
//  bigquery_proto::JobConfiguration config;
//  *config.mutable_query() = query;
//  bigquery_proto::Job job;
//  *job.mutable_configuration() = config;
//  auto result = client.InsertJob("my-project", job);
//}
//
//struct RowStream {
//
//};
//
//struct QueryResultsMetadata {
//  google::cloud::cpp::bigquery::v2::JobReference job_reference;
//};
//
//struct QueryResults {
//  RowStream rows;
//  QueryResultsMetadata metadata;
//};
//
//void Query() {
//  namespace jobs = ::google::cloud::bigquery_jobs_v2;
//  namespace bigquery_proto = ::google::cloud::cpp::bigquery::v2;
//  using google::cloud::StatusOr;
//
//  auto client = jobs::JobsClient(jobs::MakeJobsConnectionRest());
//  bigquery_proto::QueryRequest request;
//  request.set_query("SELECT name, state, year, sum(number) as total "
//      "FROM bigquery-public-data.usa_names.usa_1910_2013 "
//      "GROUP BY name, state, year");
//  StatusOr<QueryResults> result =
//      client.Query("my-project", request);
//  using MyRow = std::tuple<std::string, std::string, std::int64_t, std::int64_t>;
//  std::vector<MyRow> first_page_of_rows;
//  for (auto& r : result->rows()) {
//    first_page_of_rows.push_back(std::move(r));
//  }
//  bigquery_proto::JobReference query_results = result->metadata.job_reference;
//}

#if 0
void ReadQueryResultsSimple() {
  namespace jobs = ::google::cloud::bigquery_jobs_v2;
  namespace bigquery_proto = ::google::cloud::cpp::bigquery::v2;

  auto client = jobs::JobsClient(jobs::MakeJobsConnectionRest());
  bigquery_proto::JobReference job_reference;
  StaturOr<QueryResults> result = client.GetQueryResults(job_reference);
  // Definition of C++ types for the returned rows.
  using MyRow = std::tuple<std::string, std::string, std::int64_t, std::int64_t>;
  std::print("Name\t\t\t\tState\tYear\tTotal");
  for (auto const& r : result->rows()) {
    std::print("{0}\t\t\t\t{1}\t{2}\t{3}\n", r.get<0>(), r.get<1>(), r.get<2>(), r.get<3>());
  }
}
#endif

//void ReadQueryResultsComplicated() {
//  namespace jobs = ::google::cloud::bigquery_jobs_v2;
//  namespace bigquery_proto = ::google::cloud::cpp::bigquery::v2;
//  google::cloud::cpp::bigquery::jobs::v2::GetQueryResultsRequest request;
////  namespace bigquery_read = ::google::cloud::bigquery::storage::v1;
//
//
//  auto client = jobs::JobsClient(jobs::MakeJobsConnectionRest());
//  bigquery_proto::JobReference job_reference;
//  auto result = client.GetQueryResults(request);
//  auto dictionary_memo = std::make_shared<arrow::ipc::DictionaryMemo>();
//  arrow::io::BufferReader schema_buffer_reader(result->serialized_schema());
//  auto schema_result = arrow::ipc::ReadSchema(
//      &schema_buffer_reader, dictionary_memo.get());
//  if (!schema_result.ok()) throw result.status();
//  std::shared_ptr<arrow::Schema> schema = schema_result.ValueOrDie();
//  StreamRange<bigquery_read::ReadRowsResponse> row_reader = result->reader();
//  arrow::ipc::IpcReadOptions read_options;
//  std::print("Name\t\t\t\tState\tYear\tTotal");
//  for (auto const& row_batch : row_reader) {
//    if (row_batch.ok()) {
//      arrow::io::BufferReader record_buffer_reader(row_batch.serialized_record_batch());
//      auto read_result = arrow::ipc::ReadRecordBatch(
//          schema, dictionary_memo.get(), read_options, &record_buffer_reader);
//      if (!read_result.ok()) throw read_result.status();
//      std::shared_ptr<arrow::RecordBatch> record_batch = read_result.ValueOrDie();
//      auto name = record_batch->column(0);
//      auto state = record_batch->column(1);
//      auto year = record_batch->column(2);
//      auto total = record_batch->column(3);
//      for (int i = 0; i += record_batch->num_rows(); ++i) {
//        std::print("{0}\t\t\t\t{1}\t{2}\t{3}\n", name->GetScalar(i), state->GetScalar(i), year->GetScalar(i), total->GetScalar(i));
//      }
//    }
//  }
//
////  std::print("Name\t\t\t\tState\tYear\tTotal");
////  for (auto const& r : result->rows()) {
////    std::print("{0}\t\t\t\t{1}\t{2}\t{3}\n", r.get<0>(), r.get<1>(), r.get<2>(), r.get<3>());
////  }
//}
//
//void Write() {
//  namespace tabledata = ::google::cloud::bigquery_tabledata_v2;
//  namespace bigquery_proto = ::google::cloud::cpp::bigquery::v2;
//  namespace bigquery_write = ::google::cloud::bigquery::storage::v1;
//
//
//  auto client = tabledata::TabledataClient(tabledata::MakeTabledataConnectionRest());
//  std::vector<nlohmann::json> json_rows = GetMyJsonData();
//  auto writer = client.CreateTableWriter("my-project", "my-dataset", "my-table");
//  auto result = writer.AppendRows(json_rows);
//  std::print("Wrote {0} rows.\n", result->rows_inserted());
//}


}  // namespace

int main(int argc, char* argv[]) try {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <project-id> <table-name>\n";
    return 1;
  }

  // project_name should be in the format "projects/<your-gcp-project>"
  std::string const project_name = "projects/" + std::string(argv[1]);
  // table_name should be in the format:
  // "projects/<project-table-resides-in>/datasets/<dataset-table_resides-in>/tables/<table
  // name>" The project values in project_name and table_name do not have to be
  // identical.
  std::string const table_name = argv[2];

  // Create a namespace alias to make the code easier to read.
  //  namespace datasets = ::google::cloud::bigquery_datasets_v2;
  namespace jobs = ::google::cloud::bigquery_jobs_v2;

  //  google::protobuf::util::JsonParseOptions parse_options;
  //  parse_options.ignore_unknown_fields = true;
  //  std::string json_response{kResponseJson};

  //  google::cloud::cpp::bigquery::v2::QueryResponse qr;
  //  auto json_to_proto_status = google::protobuf::util::JsonStringToMessage(
  //      json_response, &qr, parse_options);
  //
  //  if (!json_to_proto_status.ok()) {
  //    throw google::cloud::Status(
  //        static_cast<google::cloud::StatusCode>(json_to_proto_status.code()),
  //        std::string(json_to_proto_status.message()),
  //        GCP_ERROR_INFO()
  //            .WithReason("Failure creating proto Message from Json")
  //            .WithMetadata("message_type", qr.GetTypeName())
  //            .WithMetadata("json_string", json_response)
  //            .Build(static_cast<google::cloud::StatusCode>(json_to_proto_status.code())));
  //  }
  //  std::cout << qr.DebugString() << "\n";

  //  google::cloud::cpp::bigquery::v2::StringCell sc;
  //  sc.set_sc("Bessie");
  //  google::cloud::cpp::bigquery::v2::TableCell tc;
  //  tc.mutable_v()->PackFrom(sc);
  //
  //  std::string json_output;
  //  auto message_to_json =
  //      google::protobuf::util::MessageToJsonString(tc, &json_output);
  //  if (!message_to_json.ok()) {
  //    throw google::cloud::Status(
  //        static_cast<google::cloud::StatusCode>(message_to_json.code()),
  //        std::string(message_to_json.message()),
  //        GCP_ERROR_INFO()
  //            .WithReason("Failure creating proto Message from Json")
  //            .WithMetadata("message_type", tc.GetTypeName())
  //            //            .WithMetadata("json_string", json_response)
  //            .Build(static_cast<google::cloud::StatusCode>(
  //                message_to_json.code())));
  //  }
  //  std::cout << "json_output=" << json_output << "\n";

  //  auto datasets_client = datasets::DatasetsClient(
  //      datasets::MakeDatasetsConnectionRest());
  //
  //  auto get_dataset = datasets_client.GetDataset("bigquery-public-data",
  //  "usa_names"); if (!get_dataset) throw std::move(get_dataset).status();
  //  std::cout << get_dataset->DebugString() << "\n";

  google::cloud::cpp::bigquery::v2::DatasetReference dataset_reference;
  dataset_reference.set_project_id("bigquery-public-data");
  dataset_reference.set_dataset_id("usa_names");
  google::cloud::cpp::bigquery::v2::QueryRequest query_request;

  *query_request.mutable_default_dataset() = dataset_reference;
  query_request.set_query("select * from usa_1910_2013 limit 1");
  query_request.set_max_results(100);
  auto jobs_client = jobs::JobsClient(jobs::MakeJobsConnectionRest());

  google::cloud::cpp::bigquery::jobs::v2::QueryRequest request;
  request.set_project_id(std::string(argv[1]));
  *request.mutable_query_request_resource() = query_request;
  auto query_result = jobs_client.Query(request);
  if (!query_result) throw std::move(query_result).status();
  google::cloud::cpp::bigquery::v2::QueryResponse response =
      *std::move(query_result);
  std::cout << response.DebugString() << "\n";

  //  ProcessRowsInArrowFormat(response.arrow_schema(),
  //  response.rows_in_batch(),
  //                           response.arrow_record_batch());

  return 0;
} catch (google::cloud::Status const& status) {
  std::cerr << "google::cloud::Status thrown: " << status << "\n";
  return 1;
}
//! [END bigquerystorage_quickstart] [all]
