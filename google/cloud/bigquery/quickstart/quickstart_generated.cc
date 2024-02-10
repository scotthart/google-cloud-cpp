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
#include "google/cloud/bigquery/jobs/v2/jobs_client.h"
#include <google/protobuf/util/json_util.h>
#include "google/cloud/internal/make_status.h"
#include <iostream>

namespace {

auto constexpr kResponseJson=R"""({
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
    "projectId": "cloud-cpp-testing-resources",
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
// json_output={
// "v":{
//  "@type":"type.googleapis.com/google.cloud.cpp.bigquery.v2.StringCell",
//  "sc":"Bessie"
// }
// }

}

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
  namespace datasets = ::google::cloud::bigquery_datasets_v2;
  namespace jobs = ::google::cloud::bigquery_jobs_v2;

  google::protobuf::util::JsonParseOptions parse_options;
  parse_options.ignore_unknown_fields = true;
  std::string json_response{kResponseJson};

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

  google::cloud::cpp::bigquery::v2::StringCell sc;
  sc.set_sc("Bessie");
  google::cloud::cpp::bigquery::v2::TableCell tc;
  tc.mutable_v()->PackFrom(sc);

  std::string json_output;
  auto message_to_json = google::protobuf::util::MessageToJsonString(tc, &json_output);
  if (!message_to_json.ok()) {
    throw google::cloud::Status(
        static_cast<google::cloud::StatusCode>(message_to_json.code()),
        std::string(message_to_json.message()),
        GCP_ERROR_INFO()
            .WithReason("Failure creating proto Message from Json")
            .WithMetadata("message_type", tc.GetTypeName())
//            .WithMetadata("json_string", json_response)
            .Build(static_cast<google::cloud::StatusCode>(message_to_json.code())));
  }
  std::cout << "json_output=" << json_output << "\n";


//  auto datasets_client = datasets::DatasetsClient(
//      datasets::MakeDatasetsConnectionRest());
//
//  auto get_dataset = datasets_client.GetDataset("bigquery-public-data", "usa_names");
//  if (!get_dataset) throw std::move(get_dataset).status();
//  std::cout << get_dataset->DebugString() << "\n";


  google::cloud::cpp::bigquery::v2::DatasetReference dataset_reference;
  dataset_reference.set_project_id("bigquery-public-data");
  dataset_reference.set_dataset_id("usa_names");
  google::cloud::cpp::bigquery::v2::QueryRequest query_request;

  *query_request.mutable_default_dataset() = dataset_reference;
  query_request.set_query("select * from usa_1910_2013");
  query_request.set_max_results(1);
  auto jobs_client = jobs::JobsClient(
      jobs::MakeJobsConnectionRest());

  google::cloud::cpp::bigquery::jobs::v2::QueryRequest request;
  request.set_project_id("cloud-cpp-testing-resources");
  *request.mutable_query_request_resource() = query_request;
  auto query_result = jobs_client.Query(request);
  if (!query_result) throw std::move(query_result).status();
  std::cout << query_result->DebugString() << "\n";

  return 0;
} catch (google::cloud::Status const& status) {
  std::cerr << "google::cloud::Status thrown: " << status << "\n";
  return 1;
}
//! [END bigquerystorage_quickstart] [all]
