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

#include "google/cloud/spanner/internal/spanner_operation_context_factory.h"
#include "google/cloud/spanner/internal/spanner_request_id.h"

namespace google {
namespace cloud {
namespace spanner_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

DefaultSpannerOperationContextFactory::DefaultSpannerOperationContextFactory(
    std::uint64_t client_id,
    std::shared_ptr<std::string const> process_random_id)
    : client_id_(client_id),
      process_random_id_(std::move(process_random_id)),
      static_prefix_(std::make_shared<std::string const>(
          FormatSpannerRequestStaticPrefix(1, *process_random_id_, client_id_)))
#ifndef _WIN32
      ,
      cached_pid_(getpid())
#endif
{
}

std::shared_ptr<std::string const>
DefaultSpannerOperationContextFactory::StaticPrefix() {
#ifndef _WIN32
  pid_t const current_pid = getpid();
  if (current_pid != cached_pid_) {
    std::scoped_lock lock(mu_);
    if (current_pid != cached_pid_) {
      process_random_id_ =
          std::make_shared<std::string const>(ProcessRandomId());
      static_prefix_ = std::make_shared<std::string const>(
          FormatSpannerRequestStaticPrefix(1, *process_random_id_, client_id_));
      cached_pid_ = current_pid;
    }
  }
#endif
  return static_prefix_;
}

std::uint64_t DefaultSpannerOperationContextFactory::NextUserRequestIndex() {
  return next_user_request_index_.fetch_add(1, std::memory_order_relaxed);
}

std::uint64_t
DefaultSpannerOperationContextFactory::NextBackgroundRequestIndex() {
  return next_background_request_index_.fetch_add(1, std::memory_order_relaxed);
}

SpannerOperationContext DefaultSpannerOperationContextFactory::CreateSession() {
  return SpannerOperationContext(StaticPrefix(), NextUserRequestIndex(),
                                 "CreateSession");
}

SpannerOperationContext
DefaultSpannerOperationContextFactory::BatchCreateSessions() {
  return SpannerOperationContext(StaticPrefix(), NextUserRequestIndex(),
                                 "BatchCreateSessions");
}

SpannerOperationContext DefaultSpannerOperationContextFactory::GetSession() {
  return SpannerOperationContext(StaticPrefix(), NextUserRequestIndex(),
                                 "GetSession");
}

SpannerOperationContext DefaultSpannerOperationContextFactory::ListSessions() {
  return SpannerOperationContext(StaticPrefix(), NextUserRequestIndex(),
                                 "ListSessions");
}

SpannerOperationContext DefaultSpannerOperationContextFactory::DeleteSession() {
  return SpannerOperationContext(StaticPrefix(), NextUserRequestIndex(),
                                 "DeleteSession");
}

SpannerOperationContext DefaultSpannerOperationContextFactory::ExecuteSql() {
  return SpannerOperationContext(StaticPrefix(), NextUserRequestIndex(),
                                 "ExecuteSql");
}

SpannerOperationContext
DefaultSpannerOperationContextFactory::ExecuteStreamingSql() {
  return SpannerOperationContext(StaticPrefix(), NextUserRequestIndex(),
                                 "ExecuteStreamingSql");
}

SpannerOperationContext
DefaultSpannerOperationContextFactory::ExecuteBatchDml() {
  return SpannerOperationContext(StaticPrefix(), NextUserRequestIndex(),
                                 "ExecuteBatchDml");
}

SpannerOperationContext DefaultSpannerOperationContextFactory::StreamingRead() {
  return SpannerOperationContext(StaticPrefix(), NextUserRequestIndex(),
                                 "StreamingRead");
}

SpannerOperationContext
DefaultSpannerOperationContextFactory::BeginTransaction() {
  return SpannerOperationContext(StaticPrefix(), NextUserRequestIndex(),
                                 "BeginTransaction");
}

SpannerOperationContext DefaultSpannerOperationContextFactory::Commit() {
  return SpannerOperationContext(StaticPrefix(), NextUserRequestIndex(),
                                 "Commit");
}

SpannerOperationContext DefaultSpannerOperationContextFactory::Rollback() {
  return SpannerOperationContext(StaticPrefix(), NextUserRequestIndex(),
                                 "Rollback");
}

SpannerOperationContext
DefaultSpannerOperationContextFactory::PartitionQuery() {
  return SpannerOperationContext(StaticPrefix(), NextUserRequestIndex(),
                                 "PartitionQuery");
}

SpannerOperationContext DefaultSpannerOperationContextFactory::PartitionRead() {
  return SpannerOperationContext(StaticPrefix(), NextUserRequestIndex(),
                                 "PartitionRead");
}

SpannerOperationContext DefaultSpannerOperationContextFactory::BatchWrite() {
  return SpannerOperationContext(StaticPrefix(), NextUserRequestIndex(),
                                 "BatchWrite");
}

SpannerOperationContext
DefaultSpannerOperationContextFactory::BackgroundCreateSession() {
  return SpannerOperationContext(StaticPrefix(), NextBackgroundRequestIndex(),
                                 "BackgroundCreateSession");
}

SpannerOperationContext
DefaultSpannerOperationContextFactory::BackgroundBatchCreateSessions() {
  return SpannerOperationContext(StaticPrefix(), NextBackgroundRequestIndex(),
                                 "BackgroundBatchCreateSessions");
}

SpannerOperationContext
DefaultSpannerOperationContextFactory::BackgroundDeleteSession() {
  return SpannerOperationContext(StaticPrefix(), NextBackgroundRequestIndex(),
                                 "BackgroundDeleteSession");
}

SpannerOperationContext
DefaultSpannerOperationContextFactory::BackgroundRefreshSession() {
  return SpannerOperationContext(StaticPrefix(), NextBackgroundRequestIndex(),
                                 "BackgroundRefreshSession");
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace spanner_internal
}  // namespace cloud
}  // namespace google
