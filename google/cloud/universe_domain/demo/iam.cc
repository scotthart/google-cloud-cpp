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

#include "google/cloud/iam/v2/policies_client.h"
#include "google/cloud/iam/v2/policies_options.h"
#include "google/cloud/internal/getenv.h"
#include "google/cloud/internal/rest_options.h"
#include "google/cloud/universe_domain.h"
#include "google/cloud/universe_domain_options.h"
#include "google/cloud/internal/absl_str_cat_quiet.h"
#include <iostream>
#include <thread>


int main(int argc, char* argv[]) try {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " project-id zone-id\n";
    return 1;
  }
  std::string const project_id = argv[1];
  std::string const zone_id = argv[2];

  // Create aliases to make the code easier to read.
  namespace iam_v2 = ::google::cloud::iam_v2;
  auto options =
      google::cloud::AddUniverseDomainOption(google::cloud::ExperimentalTag{});
  if (!options.ok()) throw std::move(options).status();

  // Override retry policy to quickly exit if there's a failure.
  options->set<iam_v2::PoliciesRetryPolicyOption>(
      std::make_shared<iam_v2::PoliciesLimitedErrorCountRetryPolicy>(3));
  auto client = iam_v2::PoliciesClient(iam_v2::MakePoliciesConnection(*options));

  std::cout << "iam.ListPolicies:\n";
  for (auto p : client.ListPolicies("policies/*/*")) {
    if (!p) throw std::move(p).status();
    std::cout << p->DebugString() << "\n";
  }


  google::iam::v2::Policy policy;
  policy.set_name("demo-test-policy");
  google::iam::v2::CreatePolicyRequest request;
  // policies/cloudresourcemanager.googleapis.com%2Fprojects%2Fmy-project/denypolicies
  request.set_parent(absl::StrCat(
      R"""(policies/cloudresourcemanager.googleapis.com%2Fprojects%2F)""",
      project_id,
      R"""(/denypolicies)"""
      ));
  request.set_policy_id("demo");
  *request.mutable_policy() = policy;

  std::cout << "iam.ListPoicies:\n";
  auto create_policy = client.CreatePolicy(request).get();
  if (!create_policy.ok()) throw std::move(create_policy).status();
  std::cout << "Created IAM Policy: " << create_policy->DebugString() << "\n";

  auto delete_policy = client.DeletePolicy(create_policy->name()).get();
  if (!delete_policy.ok()) throw std::move(delete_policy).status();
  std::cout << "Deleted IAM Policy: " << create_policy->name() << "\n";

#if 0
  google::cloud::cpp::compute::v1::Disk disk;
  disk.set_name("demo-test-disk");
  disk.set_size_gb("10");
  (*disk.mutable_labels())["test"] = "test";
  auto result = client.InsertDisk(project_id, zone_id, disk).get();
  if (!result.ok()) throw std::move(result).status();
  std::cout << "Created Disk: " << disk.name() << "\n";

  google::cloud::StatusOr<google::cloud::cpp::compute::v1::Disk> get_disk;
  for (auto wait_time : {5, 10, 30, 60}) {
    get_disk = client.GetDisk(project_id, zone_id, disk.name());
    if (get_disk.ok()) break;
    std::this_thread::sleep_for(std::chrono::seconds(wait_time));
  }
  if (!get_disk.ok()) throw std::move(get_disk).status();
  std::cout << "Get Disk: " << get_disk->DebugString() << "\n";

  auto delete_disk = client.DeleteDisk(project_id, zone_id, get_disk->name()).get();
  if (!delete_disk.ok()) throw std::move(delete_disk).status();
  std::cout << "Disk Deleted: " << get_disk->name() << "\n";
#if 0
  std::cout << "compute.ListDisks:\n";
  for (auto disk : client.ListDisks(project_id, zone_id)) {
    if (!disk) throw std::move(disk).status();
    std::cout << disk->DebugString() << "\n";
  }
#endif
#endif
  return 0;
} catch (google::cloud::Status const& status) {
  std::cerr << "google::cloud::Status thrown: " << status << "\n";
  return 1;
}
