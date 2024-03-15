# Google Cloud BigQuery C++ Client Library

This directory contains an idiomatic C++ client library for interacting with
[Cloud BigQuery](https://cloud.google.com/bigquery/).

While this library is **GA**, please note that the Google Cloud C++ client
libraries do **not** follow [Semantic Versioning](https://semver.org/).

## Quickstart

The [quickstart/](quickstart/README.md) directory contains a minimal environment
to get started using this client library in a larger project. The following
"Hello World" program is used in this quickstart, and should give you a taste of
this library.

For detailed instructions on how to build and install this library, see the
top-level [README](/README.md#building-and-installing).

<!-- inject-quickstart-start -->

```cc
#include "google/cloud/bigquery/storage/v1/bigquery_read_client.h"
#include "google/cloud/internal/absl_str_cat_quiet.h"
#include "google/cloud/internal/make_status.h"
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

google::cloud::StatusOr<std::int64_t> ProcessRowsInArrowFormat(
    std::shared_ptr<arrow::Schema> schema,
    std::shared_ptr<arrow::ipc::DictionaryMemo> dictionary_memo,
    std::int64_t row_count,
    ::google::cloud::bigquery::storage::v1::ArrowRecordBatch const&
        record_batch_data) {
  arrow::io::BufferReader record_buffer_reader(
      record_batch_data.serialized_record_batch());

  arrow::ipc::IpcReadOptions read_options;
  auto rb_result = arrow::ipc::ReadRecordBatch(
      schema, dictionary_memo.get(), read_options, &record_buffer_reader);
  if (!rb_result.ok())
    return google::cloud::internal::InternalError("arrow error");
  std::shared_ptr<arrow::RecordBatch> rb = rb_result.ValueOrDie();
  std::cout << rb->ToString() << "\n";
  //  std::cout << "num_rows=" << rb->num_rows() << "\n";
  return rb->num_rows();
}

std::shared_ptr<arrow::Schema> GetArrowSchema(
    ::google::cloud::bigquery::storage::v1::ArrowSchema const& schema_data,
    std::shared_ptr<arrow::ipc::DictionaryMemo> dictionary_memo) {
  arrow::io::BufferReader schema_buffer_reader(schema_data.serialized_schema());
  //  arrow::ipc::DictionaryMemo dictionary_memo;
  auto result =
      arrow::ipc::ReadSchema(&schema_buffer_reader, dictionary_memo.get());
  if (!result.ok()) throw result.status();
  std::shared_ptr<arrow::Schema> schema = result.ValueOrDie();
  return schema;
}

#if 0
google::cloud::StatusOr<std::shared_ptr<arrow::RecordBatch>>
ProcessRowsInArrowFormat(
    ::google::cloud::bigquery::storage::v1::ArrowSchema const& schema_data,
    std::int64_t row_count,
    ::google::cloud::bigquery::storage::v1::ArrowRecordBatch const&
        record_batch_data) {
  arrow::io::BufferReader schema_buffer_reader(schema_data.serialized_schema());
  arrow::ipc::DictionaryMemo dictionary_memo;
  auto result = arrow::ipc::ReadSchema(&schema_buffer_reader, &dictionary_memo);
  if (!result.ok()) throw result.status();
  std::shared_ptr<arrow::Schema> schema = result.ValueOrDie();
  //  std::cout << schema->ToString() << "\n";

  arrow::io::BufferReader record_buffer_reader(
      record_batch_data.serialized_record_batch());

  arrow::ipc::IpcReadOptions read_options;
  auto rb_result = arrow::ipc::ReadRecordBatch(
      schema, &dictionary_memo, read_options, &record_buffer_reader);
  if (!rb_result.ok())
    return google::cloud::internal::InternalError("arrow error");
  std::shared_ptr<arrow::RecordBatch> rb = rb_result.ValueOrDie();
  //  std::cout << rb->ToString() << "\n";
  //  std::cout << "num_rows=" << rb->num_rows() << "\n";
  return rb;
}
#endif
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
  // Create the ReadSession.
  auto client = bigquery_storage::BigQueryReadClient(
      bigquery_storage::MakeBigQueryReadConnection());
  ::google::cloud::bigquery::storage::v1::ReadSession read_session;
  //  read_session.set_data_format(
  //      google::cloud::bigquery::storage::v1::DataFormat::AVRO);
  read_session.set_data_format(
      google::cloud::bigquery::storage::v1::DataFormat::ARROW);
  read_session.set_table(table_name);
  google::cloud::bigquery::storage::v1::CreateReadSessionRequest request;
  request.set_parent(project_name);
  *request.mutable_read_session() = read_session;
  request.set_max_stream_count(20);
  //  request.set_preferred_min_stream_count(20);
  auto session = client.CreateReadSession(request);
  if (!session) throw std::move(session).status();

  std::cout << " num streams=" << session->streams().size() << "\n";
  // Read rows from the ReadSession.
  constexpr int kRowOffset = 0;
  //  auto row_reader = client.ReadRows(session->streams(0).name(), kRowOffset);

  auto dictionary_memo = std::make_shared<arrow::ipc::DictionaryMemo>();
  auto schema = GetArrowSchema(session->arrow_schema(), dictionary_memo);

  std::vector<std::int64_t> num_rows;
  num_rows.reserve(session->streams().size());

  auto fn = [](auto row_reader, std::int64_t* num_rows,
               std::shared_ptr<arrow::Schema> schema,
               std::shared_ptr<arrow::ipc::DictionaryMemo> dictionary_memo) {
    *num_rows = 0;
    for (auto const& row_batch : row_reader) {
      if (row_batch.ok()) {
        *num_rows += row_batch->row_count();
        ProcessRowsInArrowFormat(schema, dictionary_memo,
                                 row_batch->row_count(),
                                 row_batch->arrow_record_batch());
      }
    }
  };

  std::vector<std::future<void>> tasks;
  for (int i = 0; i != session->streams().size(); ++i) {
    auto row_reader = client.ReadRows(session->streams(i).name(), kRowOffset);

    tasks.push_back(std::async(std::launch::async, fn, std::move(row_reader),
                               &num_rows[i], schema, dictionary_memo));
  }

  for (auto& t : tasks) {
    t.get();
  }

  std::int64_t total_rows = 0;
  for (int i = 0; i != session->streams().size(); ++i) {
    total_rows += num_rows[i];
  }

  std::cout << total_rows << " rows read from table: " << table_name << "\n";
  return 0;
} catch (google::cloud::Status const& status) {
  std::cerr << "google::cloud::Status thrown: " << status << "\n";
  return 1;
}
```

<!-- inject-quickstart-end -->

## More Information

- Official documentation about the [Cloud BigQuery][cloud-bigquery-docs] service
- [Reference doxygen documentation][doxygen-link] for each release of this
  client library
- Detailed header comments in our [public `.h`][source-link] files

[cloud-bigquery-docs]: https://cloud.google.com/bigquery/docs/
[doxygen-link]: https://cloud.google.com/cpp/docs/reference/bigquery/latest/
[source-link]: https://github.com/googleapis/google-cloud-cpp/tree/main/google/cloud/bigquery
