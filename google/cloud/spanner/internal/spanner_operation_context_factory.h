// Copyright 2026 Google LLC
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

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_SPANNER_INTERNAL_SPANNER_OPERATION_CONTEXT_FACTORY_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_SPANNER_INTERNAL_SPANNER_OPERATION_CONTEXT_FACTORY_H

#include "google/cloud/spanner/internal/spanner_operation_context.h"
#include "google/cloud/spanner/version.h"
#include <atomic>
#include <cstdint>
#include <memory>
#include <mutex>
#include <string>
#ifndef _WIN32
#include <unistd.h>
#endif

namespace google {
namespace cloud {
namespace spanner_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

class SpannerOperationContextFactory {
 public:
  virtual ~SpannerOperationContextFactory() = default;

  // User-facing RPC context factories (use next_user_request_index_)
  virtual SpannerOperationContext CreateSession() = 0;
  virtual SpannerOperationContext BatchCreateSessions() = 0;
  virtual SpannerOperationContext GetSession() = 0;
  virtual SpannerOperationContext ListSessions() = 0;
  virtual SpannerOperationContext DeleteSession() = 0;
  virtual SpannerOperationContext ExecuteSql() = 0;
  virtual SpannerOperationContext ExecuteStreamingSql() = 0;
  virtual SpannerOperationContext ExecuteBatchDml() = 0;
  virtual SpannerOperationContext StreamingRead() = 0;
  virtual SpannerOperationContext BeginTransaction() = 0;
  virtual SpannerOperationContext Commit() = 0;
  virtual SpannerOperationContext Rollback() = 0;
  virtual SpannerOperationContext PartitionQuery() = 0;
  virtual SpannerOperationContext PartitionRead() = 0;
  virtual SpannerOperationContext BatchWrite() = 0;

  // Background maintenance context factories (use next_background_request_index_)
  virtual SpannerOperationContext BackgroundCreateSession() = 0;
  virtual SpannerOperationContext BackgroundBatchCreateSessions() = 0;
  virtual SpannerOperationContext BackgroundDeleteSession() = 0;
  virtual SpannerOperationContext BackgroundRefreshSession() = 0;
};

class DefaultSpannerOperationContextFactory
    : public SpannerOperationContextFactory {
 public:
  // Explicit constructor without default arguments per internal guidelines.
  DefaultSpannerOperationContextFactory(
      std::uint64_t client_id,
      std::shared_ptr<std::string const> process_random_id);

  SpannerOperationContext CreateSession() override;
  SpannerOperationContext BatchCreateSessions() override;
  SpannerOperationContext GetSession() override;
  SpannerOperationContext ListSessions() override;
  SpannerOperationContext DeleteSession() override;
  SpannerOperationContext ExecuteSql() override;
  SpannerOperationContext ExecuteStreamingSql() override;
  SpannerOperationContext ExecuteBatchDml() override;
  SpannerOperationContext StreamingRead() override;
  SpannerOperationContext BeginTransaction() override;
  SpannerOperationContext Commit() override;
  SpannerOperationContext Rollback() override;
  SpannerOperationContext PartitionQuery() override;
  SpannerOperationContext PartitionRead() override;
  SpannerOperationContext BatchWrite() override;

  SpannerOperationContext BackgroundCreateSession() override;
  SpannerOperationContext BackgroundBatchCreateSessions() override;
  SpannerOperationContext BackgroundDeleteSession() override;
  SpannerOperationContext BackgroundRefreshSession() override;

 private:
  std::shared_ptr<std::string const> StaticPrefix();
  std::uint64_t NextUserRequestIndex();
  std::uint64_t NextBackgroundRequestIndex();

  std::uint64_t client_id_;
  std::shared_ptr<std::string const> process_random_id_;
  std::shared_ptr<std::string const> static_prefix_;
#ifndef _WIN32
  pid_t cached_pid_;
#endif
  std::mutex mu_;
  std::atomic<std::uint64_t> next_user_request_index_{1};
  std::atomic<std::uint64_t> next_background_request_index_{1};
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace spanner_internal
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_SPANNER_INTERNAL_SPANNER_OPERATION_CONTEXT_FACTORY_H
