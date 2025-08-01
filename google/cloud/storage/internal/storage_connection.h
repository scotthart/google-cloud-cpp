// Copyright 2018 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_STORAGE_INTERNAL_STORAGE_CONNECTION_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_STORAGE_INTERNAL_STORAGE_CONNECTION_H

#include "google/cloud/storage/bucket_metadata.h"
#include "google/cloud/storage/client_options.h"
#include "google/cloud/storage/internal/bucket_acl_requests.h"
#include "google/cloud/storage/internal/bucket_requests.h"
#include "google/cloud/storage/internal/default_object_acl_requests.h"
#include "google/cloud/storage/internal/empty_response.h"
#include "google/cloud/storage/internal/hash_validator.h"
#include "google/cloud/storage/internal/hmac_key_requests.h"
#include "google/cloud/storage/internal/notification_requests.h"
#include "google/cloud/storage/internal/object_acl_requests.h"
#include "google/cloud/storage/internal/object_read_source.h"
#include "google/cloud/storage/internal/object_requests.h"
#include "google/cloud/storage/internal/service_account_requests.h"
#include "google/cloud/storage/internal/sign_blob_requests.h"
#include "google/cloud/storage/oauth2/credentials.h"
#include "google/cloud/storage/object_metadata.h"
#include "google/cloud/storage/service_account.h"
#include "google/cloud/storage/version.h"
#include "google/cloud/options.h"
#include "google/cloud/status.h"
#include "google/cloud/status_or.h"
#include <memory>
#include <string>
#include <thread>
#include <vector>

namespace google {
namespace cloud {
namespace storage {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN
namespace internal {
class ParallelUploadFileShard;
class ObjectReadStreambuf;

/**
 * Defines the interface used to communicate with Google Cloud Storage.
 */
class StorageConnection {
 public:
  virtual ~StorageConnection() = default;

  virtual ClientOptions const& client_options() const = 0;

  virtual google::cloud::Options options() const { return {}; }

  ///@{
  /// @name Bucket resource operations
  virtual StatusOr<ListBucketsResponse> ListBuckets(
      ListBucketsRequest const& request) = 0;
  virtual StatusOr<BucketMetadata> CreateBucket(CreateBucketRequest const&) = 0;
  virtual StatusOr<BucketMetadata> GetBucketMetadata(
      GetBucketMetadataRequest const& request) = 0;
  virtual StatusOr<EmptyResponse> DeleteBucket(
      DeleteBucketRequest const& request) = 0;
  virtual StatusOr<BucketMetadata> UpdateBucket(UpdateBucketRequest const&) = 0;
  virtual StatusOr<BucketMetadata> PatchBucket(
      PatchBucketRequest const& request) = 0;
  virtual StatusOr<NativeIamPolicy> GetNativeBucketIamPolicy(
      GetBucketIamPolicyRequest const& request) = 0;
  virtual StatusOr<NativeIamPolicy> SetNativeBucketIamPolicy(
      SetNativeBucketIamPolicyRequest const& request) = 0;
  virtual StatusOr<TestBucketIamPermissionsResponse> TestBucketIamPermissions(
      TestBucketIamPermissionsRequest const& request) = 0;
  virtual StatusOr<BucketMetadata> LockBucketRetentionPolicy(
      LockBucketRetentionPolicyRequest const& request) = 0;
  ///@}

  ///@{
  /// @name Object resource operations
  virtual StatusOr<ObjectMetadata> InsertObjectMedia(
      InsertObjectMediaRequest const&) = 0;
  virtual StatusOr<ObjectMetadata> CopyObject(CopyObjectRequest const&) = 0;
  virtual StatusOr<ObjectMetadata> GetObjectMetadata(
      GetObjectMetadataRequest const& request) = 0;
  virtual StatusOr<std::unique_ptr<ObjectReadSource>> ReadObject(
      ReadObjectRangeRequest const&) = 0;
  virtual StatusOr<ListObjectsResponse> ListObjects(
      ListObjectsRequest const&) = 0;
  virtual StatusOr<EmptyResponse> DeleteObject(DeleteObjectRequest const&) = 0;
  virtual StatusOr<ObjectMetadata> UpdateObject(UpdateObjectRequest const&) = 0;
  virtual StatusOr<ObjectMetadata> MoveObject(MoveObjectRequest const&) = 0;
  virtual StatusOr<ObjectMetadata> PatchObject(PatchObjectRequest const&) = 0;
  virtual StatusOr<ObjectMetadata> ComposeObject(
      ComposeObjectRequest const&) = 0;
  virtual StatusOr<RewriteObjectResponse> RewriteObject(
      RewriteObjectRequest const&) = 0;
  virtual StatusOr<ObjectMetadata> RestoreObject(
      RestoreObjectRequest const&) = 0;

  virtual StatusOr<CreateResumableUploadResponse> CreateResumableUpload(
      ResumableUploadRequest const& request) = 0;
  virtual StatusOr<QueryResumableUploadResponse> QueryResumableUpload(
      QueryResumableUploadRequest const& request) = 0;
  virtual StatusOr<EmptyResponse> DeleteResumableUpload(
      DeleteResumableUploadRequest const& request) = 0;
  virtual StatusOr<QueryResumableUploadResponse> UploadChunk(
      UploadChunkRequest const& request) = 0;
  virtual StatusOr<std::unique_ptr<std::string>> UploadFileSimple(
      std::string const&, std::size_t, InsertObjectMediaRequest&) {
    return Status(StatusCode::kUnimplemented, "unimplemented");
  }
  virtual StatusOr<std::unique_ptr<std::istream>> UploadFileResumable(
      std::string const&, ResumableUploadRequest&) {
    return Status(StatusCode::kUnimplemented, "unimplemented");
  }
  virtual StatusOr<ObjectMetadata> ExecuteParallelUploadFile(
      std::vector<std::thread>, std::vector<ParallelUploadFileShard>, bool);
  ///@}

  ///@{
  /// @name BucketAccessControls resource operations
  virtual StatusOr<ListBucketAclResponse> ListBucketAcl(
      ListBucketAclRequest const&) = 0;
  virtual StatusOr<BucketAccessControl> CreateBucketAcl(
      CreateBucketAclRequest const&) = 0;
  virtual StatusOr<EmptyResponse> DeleteBucketAcl(
      DeleteBucketAclRequest const&) = 0;
  virtual StatusOr<BucketAccessControl> GetBucketAcl(
      GetBucketAclRequest const&) = 0;
  virtual StatusOr<BucketAccessControl> UpdateBucketAcl(
      UpdateBucketAclRequest const&) = 0;
  virtual StatusOr<BucketAccessControl> PatchBucketAcl(
      PatchBucketAclRequest const&) = 0;
  ///@}

  ///@{
  /// @name ObjectAccessControls operations
  virtual StatusOr<ListObjectAclResponse> ListObjectAcl(
      ListObjectAclRequest const&) = 0;
  virtual StatusOr<ObjectAccessControl> CreateObjectAcl(
      CreateObjectAclRequest const&) = 0;
  virtual StatusOr<EmptyResponse> DeleteObjectAcl(
      DeleteObjectAclRequest const&) = 0;
  virtual StatusOr<ObjectAccessControl> GetObjectAcl(
      GetObjectAclRequest const&) = 0;
  virtual StatusOr<ObjectAccessControl> UpdateObjectAcl(
      UpdateObjectAclRequest const&) = 0;
  virtual StatusOr<ObjectAccessControl> PatchObjectAcl(
      PatchObjectAclRequest const&) = 0;
  ///@}

  ///@{
  /// @name DefaultObjectAccessControls operations.
  virtual StatusOr<ListDefaultObjectAclResponse> ListDefaultObjectAcl(
      ListDefaultObjectAclRequest const&) = 0;
  virtual StatusOr<ObjectAccessControl> CreateDefaultObjectAcl(
      CreateDefaultObjectAclRequest const&) = 0;
  virtual StatusOr<EmptyResponse> DeleteDefaultObjectAcl(
      DeleteDefaultObjectAclRequest const&) = 0;
  virtual StatusOr<ObjectAccessControl> GetDefaultObjectAcl(
      GetDefaultObjectAclRequest const&) = 0;
  virtual StatusOr<ObjectAccessControl> UpdateDefaultObjectAcl(
      UpdateDefaultObjectAclRequest const&) = 0;
  virtual StatusOr<ObjectAccessControl> PatchDefaultObjectAcl(
      PatchDefaultObjectAclRequest const&) = 0;
  ///@}

  ///@{
  virtual StatusOr<ServiceAccount> GetServiceAccount(
      GetProjectServiceAccountRequest const&) = 0;
  virtual StatusOr<ListHmacKeysResponse> ListHmacKeys(
      ListHmacKeysRequest const&) = 0;
  virtual StatusOr<CreateHmacKeyResponse> CreateHmacKey(
      CreateHmacKeyRequest const&) = 0;
  virtual StatusOr<EmptyResponse> DeleteHmacKey(
      DeleteHmacKeyRequest const&) = 0;
  virtual StatusOr<HmacKeyMetadata> GetHmacKey(GetHmacKeyRequest const&) = 0;
  virtual StatusOr<HmacKeyMetadata> UpdateHmacKey(
      UpdateHmacKeyRequest const&) = 0;
  virtual StatusOr<SignBlobResponse> SignBlob(SignBlobRequest const&) = 0;
  ///@}

  ///@{
  virtual StatusOr<ListNotificationsResponse> ListNotifications(
      ListNotificationsRequest const&) = 0;
  virtual StatusOr<NotificationMetadata> CreateNotification(
      CreateNotificationRequest const&) = 0;
  virtual StatusOr<NotificationMetadata> GetNotification(
      GetNotificationRequest const&) = 0;
  virtual StatusOr<EmptyResponse> DeleteNotification(
      DeleteNotificationRequest const&) = 0;
  ///@}

  // Test-only. Returns the names of the decorator stack elements.
  virtual std::vector<std::string> InspectStackStructure() const;
};

/**
 * An alias for backwards compatibility.
 *
 * There is reason to believe that customers may have used `internal::RawClient`
 * in their unit tests. We provide a backwards compatibility alias to ease the
 * transition.
 */
using RawClient [[deprecated("Prefer using internal::StorageConnection")]] =
    StorageConnection;

struct CreateOrResumeResponse {
  std::string upload_id;
  std::uint64_t committed_size;
  absl::optional<ObjectMetadata> metadata;
};

StatusOr<CreateOrResumeResponse> CreateOrResume(
    StorageConnection& connection, ResumableUploadRequest const& request);

}  // namespace internal
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace storage
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_STORAGE_INTERNAL_STORAGE_CONNECTION_H
