#include "base/init_google.h"
#include "third_party/cloud_cpp/google/cloud/bigtable/table.h"
#include "third_party/cloud_cpp/google/cloud/bigtable/table_admin.h"

// This example uses Application Default Credentials to connect to
// Cloud Bigtable. You need to set GRPC_DEFAULT_SSL_ROOTS_FILE_PATH:
//
//   export GRPC_DEFAULT_SSL_ROOTS_FILE_PATH=.../third_party/grpc/etc/roots.pem
//
// and login using gcloud:
//
//   gcloud auth application-default login
//
int main(int argc, char* argv[]) {
  InitGoogle(argv[0], &argc, &argv, true);
  if (argc != 4) {
    std::string const cmd = argv[0];
    auto last_slash = std::string(cmd).find_last_of('/');
    std::cerr << "Usage: " << cmd.substr(last_slash + 1)
              << " <project_id> <instance_id> <table_id>\n";
    return 1;
  }

  std::string const project_id = argv[1];
  std::string const instance_id = argv[2];
  std::string const table_id = argv[3];

  // Connect to the Cloud Bigtable Admin API.
  google::cloud::bigtable::TableAdmin table_admin(
      google::cloud::bigtable::CreateDefaultAdminClient(
          project_id, google::cloud::bigtable::ClientOptions()),
      instance_id);

  // Define the desired schema for the Table.
  auto gc_rule = google::cloud::bigtable::GcRule::MaxNumVersions(1);
  google::cloud::bigtable::TableConfig schema({{"family", gc_rule}}, {});

  auto returned_schema = table_admin.CreateTable(table_id, schema);
  if (!returned_schema.status().ok()) {
    std::cerr << "Cannot create table " << table_id << ": "
              << returned_schema.status().message() << "\n";
    return 1;
  }

  // Create an object to access the Cloud Bigtable Data API.
  google::cloud::bigtable::Table table(
      google::cloud::bigtable::CreateDefaultDataClient(
          project_id, instance_id, google::cloud::bigtable::ClientOptions()),
      table_id);

  // Modify (and create if necessary) a row.
  std::vector<std::string> greetings{"Hello World!", "Hello Cloud Bigtable!",
                                     "Hello C++!"};
  int i = 0;
  for (auto const& greeting : greetings) {
    // Each row has a unique row key.
    //
    // Note: This example uses sequential numeric IDs for simplicity, but
    // this can result in poor performance in a production application.
    // Since rows are stored in sorted order by key, sequential keys can
    // result in poor distribution of operations across nodes.
    //
    // For more information about how to design a Bigtable schema for the
    // best performance, see the documentation:
    //
    //     https://cloud.google.com/bigtable/docs/schema-design
    std::string row_key = "key-" + std::to_string(i);
    auto apply_status = table.Apply(google::cloud::bigtable::SingleRowMutation(
        row_key, google::cloud::bigtable::SetCell("family", "c0", greeting)));
    if (!apply_status.ok()) {
      std::cerr << "Failure in table.Apply() " << table_id << ":\n";
      std::cerr << "  " << row_key << ": " << apply_status.message() << "\n";
      return 1;
    }
    ++i;
  }

  // Read a single row.
  auto result = table.ReadRow(
      "key-0",
      google::cloud::bigtable::Filter::ColumnRangeClosed("family", "c0", "c0"));
  if (!result.status().ok()) {
    std::cerr << "Failure in table.ReadRow() " << table_id << ": "
              << result.status().message() << "\n";
    return 1;
  }
  if (!result->first) {
    std::cout << "Cannot find row 'key-0' in the table: " << table.table_name()
              << "\n";
    return 0;
  }
  auto const& cell = result->second.cells().front();
  std::cout << cell.family_name() << ":" << cell.column_qualifier() << "    @ "
            << cell.timestamp().count() << "us\n"
            << '"' << cell.value() << '"' << "\n";

  // Read a single row.
  auto reader =
      table.ReadRows(google::cloud::bigtable::RowRange::InfiniteRange(),
                     google::cloud::bigtable::Filter::PassAllFilter());
  for (auto& row : reader) {
    if (!row) {
      std::cerr << "Failure in table.ReadRows() " << table_id << ": "
                << row.status().message() << "\n";
      return 1;
    }
    std::cout << row->row_key() << ":\n";
    for (auto& cell : row->cells()) {
      std::cout << "\t" << cell.family_name() << ":" << cell.column_qualifier()
                << "    @ " << cell.timestamp().count() << "us\n"
                << "\t\"" << cell.value() << '"' << "\n";
    }
  }

  // Delete the table
  auto status = table_admin.DeleteTable(table_id);
  if (!status.ok()) {
    std::cerr << "Failure in table.DeleteTable() " << table_id << ": "
              << status.message() << "\n";
    return 1;
  }

  return 0;
}
