// Copyright 2023 Google LLC
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

// Generated by the Codegen C++ plugin.
// If you make any local changes, they will be lost.
// source: google/cloud/compute/snapshot_settings/v1/snapshot_settings.proto

#include "google/cloud/compute/snapshot_settings/v1/snapshot_settings_connection_idempotency_policy.h"
#include <memory>

namespace google {
namespace cloud {
namespace compute_snapshot_settings_v1 {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

using ::google::cloud::Idempotency;

SnapshotSettingsConnectionIdempotencyPolicy::
    ~SnapshotSettingsConnectionIdempotencyPolicy() = default;

std::unique_ptr<SnapshotSettingsConnectionIdempotencyPolicy>
SnapshotSettingsConnectionIdempotencyPolicy::clone() const {
  return std::make_unique<SnapshotSettingsConnectionIdempotencyPolicy>(*this);
}

Idempotency SnapshotSettingsConnectionIdempotencyPolicy::GetSnapshotSettings(
    google::cloud::cpp::compute::snapshot_settings::v1::
        GetSnapshotSettingsRequest const&) {
  return Idempotency::kIdempotent;
}

Idempotency SnapshotSettingsConnectionIdempotencyPolicy::PatchSnapshotSettings(
    google::cloud::cpp::compute::snapshot_settings::v1::
        PatchSnapshotSettingsRequest const&) {
  return Idempotency::kNonIdempotent;
}

std::unique_ptr<SnapshotSettingsConnectionIdempotencyPolicy>
MakeDefaultSnapshotSettingsConnectionIdempotencyPolicy() {
  return std::make_unique<SnapshotSettingsConnectionIdempotencyPolicy>();
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace compute_snapshot_settings_v1
}  // namespace cloud
}  // namespace google
