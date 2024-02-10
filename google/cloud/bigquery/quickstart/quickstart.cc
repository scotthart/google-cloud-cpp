// Copyright 2021 Google LLC
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
#include "google/cloud/bigquery/storage/v1/bigquery_read_client.h"
#include "google/cloud/internal/absl_str_cat_quiet.h"
#include <arrow/array/array_nested.h>
#include <arrow/array/data.h>
#include <arrow/io/memory.h>
#include <arrow/ipc/api.h>
#include <arrow/ipc/reader.h>
#include <arrow/record_batch.h>
#include <iostream>

namespace {
// void ProcessRowsInAvroFormat(
//     ::google::cloud::bigquery::storage::v1::AvroSchema const&,
//     ::google::cloud::bigquery::storage::v1::AvroRows const&) {
//   // Code to deserialize avro rows should be added here.
// }

void ProcessRowsInArrowFormat(
    ::google::cloud::bigquery::storage::v1::ArrowSchema const& schema_data,
    std::int64_t row_count,
    ::google::cloud::bigquery::storage::v1::ArrowRecordBatch const&
        record_batch_data) {
  arrow::io::BufferReader schema_buffer_reader(schema_data.serialized_schema());
  arrow::ipc::DictionaryMemo dictionary_memo;
  auto result = arrow::ipc::ReadSchema(&schema_buffer_reader, &dictionary_memo);
  if (!result.ok()) throw result.status();
  std::shared_ptr<arrow::Schema> schema = result.ValueOrDie();
  std::cout << schema->ToString() << "\n";

  arrow::io::BufferReader record_buffer_reader(
      record_batch_data.serialized_record_batch());

  arrow::ipc::IpcReadOptions read_options;
  auto rb_result = arrow::ipc::ReadRecordBatch(
      schema, &dictionary_memo, read_options, &record_buffer_reader);
  if (!rb_result.ok()) throw rb_result.status();
  std::shared_ptr<arrow::RecordBatch> rb = rb_result.ValueOrDie();
  std::cout << rb->ToString() << "\n";
  std::cout << "num_rows=" << rb->num_rows() << "\n";
}

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
  namespace bigquery_storage = ::google::cloud::bigquery_storage_v1;
  constexpr int kMaxReadStreams = 1;
  // Create the ReadSession.
  auto client = bigquery_storage::BigQueryReadClient(
      bigquery_storage::MakeBigQueryReadConnection());
  ::google::cloud::bigquery::storage::v1::ReadSession read_session;
  //  read_session.set_data_format(
  //      google::cloud::bigquery::storage::v1::DataFormat::AVRO);
  read_session.set_data_format(
      google::cloud::bigquery::storage::v1::DataFormat::ARROW);
  read_session.set_table(table_name);
  auto session =
      client.CreateReadSession(project_name, read_session, kMaxReadStreams);
  if (!session) throw std::move(session).status();

  // Read rows from the ReadSession.
  constexpr int kRowOffset = 0;
  auto read_rows = client.ReadRows(session->streams(0).name(), kRowOffset);

  std::int64_t num_rows = 0;
  int i = 0;
  for (auto const& row : read_rows) {
    if (row.ok()) {
      ++i;
      num_rows += row->row_count();
      //      ProcessRowsInAvroFormat(session->avro_schema(), row->avro_rows());
      ProcessRowsInArrowFormat(session->arrow_schema(), row->row_count(),
                               row->arrow_record_batch());
    }
  }

  std::cout << i << " iterations through StreamRange\n";
  std::cout << num_rows << " rows read from table: " << table_name << "\n";
  return 0;
} catch (google::cloud::Status const& status) {
  std::cerr << "google::cloud::Status thrown: " << status << "\n";
  return 1;
}
//! [END bigquerystorage_quickstart] [all]
