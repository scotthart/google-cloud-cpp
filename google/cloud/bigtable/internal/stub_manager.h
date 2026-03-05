// Copyright 2026 Google LLC
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

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BIGTABLE_INTERNAL_STUB_MANAGER_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BIGTABLE_INTERNAL_STUB_MANAGER_H

#include "google/cloud/bigtable/data_connection.h"
#include "google/cloud/bigtable/internal/bigtable_stub.h"
#include "google/cloud/bigtable/internal/mutate_rows_limiter.h"
#include "google/cloud/bigtable/internal/operation_context_factory.h"
#include "google/cloud/bigtable/internal/partial_result_set_reader.h"
#include "google/cloud/bigtable/prepared_query.h"
#include "google/cloud/bigtable/result_source_interface.h"
#include "google/cloud/background_threads.h"
#include "google/cloud/options.h"
#include "google/cloud/status_or.h"
#include "google/cloud/version.h"
#include <memory>

namespace google {
namespace cloud {
namespace bigtable_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

class StubManager {
 public:
  enum class Priming { kNoPriming, kSynchronousPriming };

  // This function must not send any RPCs as it is called while a lock is held.
  // This means channels cannot be primed as part of construction, but instead
  // must be scheduled to be primed asynchronously.
  using StubCreationFn = std::function<std::shared_ptr<BigtableStub>(
      std::string const& instance_name, Priming priming)>;

  enum class Mode {
    kNoAffinity,
    kInstanceAffinity,
  };

  explicit StubManager(std::shared_ptr<BigtableStub> stub)
      : mode_(Mode::kNoAffinity), stub_(std::move(stub)) {}

  StubManager(absl::flat_hash_map<std::string, std::shared_ptr<BigtableStub>>
                  affinity_stubs,
              StubCreationFn stub_creation_fn)
      : mode_(Mode::kInstanceAffinity),
        stub_creation_fn_(std::move(stub_creation_fn)),
        affinity_stubs_(std::move(affinity_stubs)) {}

  std::shared_ptr<BigtableStub> GetStub(absl::string_view instance_name) {
    if (mode_ == Mode::kNoAffinity) return stub_;

    std::lock_guard<std::mutex> lk(mu_);
    auto iter = affinity_stubs_.find(instance_name);
    if (iter != affinity_stubs_.end()) return iter->second;

    auto inserted = affinity_stubs_.insert(std::make_pair(
        std::string{instance_name},
        stub_creation_fn_(std::string{instance_name}, Priming::kNoPriming)));
    return inserted.first->second;
  }

 private:
  std::mutex mu_;
  Mode mode_;
  StubCreationFn stub_creation_fn_;
  std::shared_ptr<BigtableStub> stub_;
  absl::flat_hash_map<std::string, std::shared_ptr<BigtableStub>>
      affinity_stubs_;
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigtable_internal
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BIGTABLE_INTERNAL_STUB_MANAGER_H
