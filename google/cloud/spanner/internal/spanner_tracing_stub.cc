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
// source: google/spanner/v1/spanner.proto

#include "google/cloud/spanner/internal/spanner_tracing_stub.h"
#include "google/cloud/internal/grpc_opentelemetry.h"
#include "google/cloud/internal/streaming_read_rpc_tracing.h"
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace spanner_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

#ifdef GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY

SpannerTracingStub::SpannerTracingStub(std::shared_ptr<SpannerStub> child)
    : child_(std::move(child)), propagator_(internal::MakePropagator()) {}

StatusOr<google::spanner::v1::Session> SpannerTracingStub::CreateSession(
    grpc::ClientContext& context, Options const& options,
    google::spanner::v1::CreateSessionRequest const& request) {
  auto span =
      internal::MakeSpanGrpc("google.spanner.v1.Spanner", "CreateSession");
  auto scope = opentelemetry::trace::Scope(span);
  internal::InjectTraceContext(context, *propagator_);
  return internal::EndSpan(context, *span,
                           child_->CreateSession(context, options, request));
}

StatusOr<google::spanner::v1::BatchCreateSessionsResponse>
SpannerTracingStub::BatchCreateSessions(
    grpc::ClientContext& context, Options const& options,
    google::spanner::v1::BatchCreateSessionsRequest const& request) {
  auto span = internal::MakeSpanGrpc("google.spanner.v1.Spanner",
                                     "BatchCreateSessions");
  auto scope = opentelemetry::trace::Scope(span);
  internal::InjectTraceContext(context, *propagator_);
  return internal::EndSpan(
      context, *span, child_->BatchCreateSessions(context, options, request));
}

Status SpannerTracingStub::DeleteSession(
    grpc::ClientContext& context, Options const& options,
    google::spanner::v1::DeleteSessionRequest const& request) {
  auto span =
      internal::MakeSpanGrpc("google.spanner.v1.Spanner", "DeleteSession");
  auto scope = opentelemetry::trace::Scope(span);
  internal::InjectTraceContext(context, *propagator_);
  return internal::EndSpan(context, *span,
                           child_->DeleteSession(context, options, request));
}

StatusOr<google::spanner::v1::ResultSet> SpannerTracingStub::ExecuteSql(
    grpc::ClientContext& context, Options const& options,
    google::spanner::v1::ExecuteSqlRequest const& request) {
  auto span = internal::MakeSpanGrpc("google.spanner.v1.Spanner", "ExecuteSql");
  auto scope = opentelemetry::trace::Scope(span);
  internal::InjectTraceContext(context, *propagator_);
  return internal::EndSpan(context, *span,
                           child_->ExecuteSql(context, options, request));
}

std::unique_ptr<google::cloud::internal::StreamingReadRpc<
    google::spanner::v1::PartialResultSet>>
SpannerTracingStub::ExecuteStreamingSql(
    std::shared_ptr<grpc::ClientContext> context, Options const& options,
    google::spanner::v1::ExecuteSqlRequest const& request) {
  auto span = internal::MakeSpanGrpc("google.spanner.v1.Spanner",
                                     "ExecuteStreamingSql");
  auto scope = opentelemetry::trace::Scope(span);
  internal::InjectTraceContext(*context, *propagator_);
  auto stream = child_->ExecuteStreamingSql(context, options, request);
  return std::make_unique<
      internal::StreamingReadRpcTracing<google::spanner::v1::PartialResultSet>>(
      std::move(context), std::move(stream), std::move(span));
}

StatusOr<google::spanner::v1::ExecuteBatchDmlResponse>
SpannerTracingStub::ExecuteBatchDml(
    grpc::ClientContext& context, Options const& options,
    google::spanner::v1::ExecuteBatchDmlRequest const& request) {
  auto span =
      internal::MakeSpanGrpc("google.spanner.v1.Spanner", "ExecuteBatchDml");
  auto scope = opentelemetry::trace::Scope(span);
  internal::InjectTraceContext(context, *propagator_);
  return internal::EndSpan(context, *span,
                           child_->ExecuteBatchDml(context, options, request));
}

std::unique_ptr<google::cloud::internal::StreamingReadRpc<
    google::spanner::v1::PartialResultSet>>
SpannerTracingStub::StreamingRead(
    std::shared_ptr<grpc::ClientContext> context, Options const& options,
    google::spanner::v1::ReadRequest const& request) {
  auto span =
      internal::MakeSpanGrpc("google.spanner.v1.Spanner", "StreamingRead");
  auto scope = opentelemetry::trace::Scope(span);
  internal::InjectTraceContext(*context, *propagator_);
  auto stream = child_->StreamingRead(context, options, request);
  return std::make_unique<
      internal::StreamingReadRpcTracing<google::spanner::v1::PartialResultSet>>(
      std::move(context), std::move(stream), std::move(span));
}

StatusOr<google::spanner::v1::Transaction> SpannerTracingStub::BeginTransaction(
    grpc::ClientContext& context, Options const& options,
    google::spanner::v1::BeginTransactionRequest const& request) {
  auto span =
      internal::MakeSpanGrpc("google.spanner.v1.Spanner", "BeginTransaction");
  auto scope = opentelemetry::trace::Scope(span);
  internal::InjectTraceContext(context, *propagator_);
  return internal::EndSpan(context, *span,
                           child_->BeginTransaction(context, options, request));
}

StatusOr<google::spanner::v1::CommitResponse> SpannerTracingStub::Commit(
    grpc::ClientContext& context, Options const& options,
    google::spanner::v1::CommitRequest const& request) {
  auto span = internal::MakeSpanGrpc("google.spanner.v1.Spanner", "Commit");
  auto scope = opentelemetry::trace::Scope(span);
  internal::InjectTraceContext(context, *propagator_);
  return internal::EndSpan(context, *span,
                           child_->Commit(context, options, request));
}

Status SpannerTracingStub::Rollback(
    grpc::ClientContext& context, Options const& options,
    google::spanner::v1::RollbackRequest const& request) {
  auto span = internal::MakeSpanGrpc("google.spanner.v1.Spanner", "Rollback");
  auto scope = opentelemetry::trace::Scope(span);
  internal::InjectTraceContext(context, *propagator_);
  return internal::EndSpan(context, *span,
                           child_->Rollback(context, options, request));
}

StatusOr<google::spanner::v1::PartitionResponse>
SpannerTracingStub::PartitionQuery(
    grpc::ClientContext& context, Options const& options,
    google::spanner::v1::PartitionQueryRequest const& request) {
  auto span =
      internal::MakeSpanGrpc("google.spanner.v1.Spanner", "PartitionQuery");
  auto scope = opentelemetry::trace::Scope(span);
  internal::InjectTraceContext(context, *propagator_);
  return internal::EndSpan(context, *span,
                           child_->PartitionQuery(context, options, request));
}

StatusOr<google::spanner::v1::PartitionResponse>
SpannerTracingStub::PartitionRead(
    grpc::ClientContext& context, Options const& options,
    google::spanner::v1::PartitionReadRequest const& request) {
  auto span =
      internal::MakeSpanGrpc("google.spanner.v1.Spanner", "PartitionRead");
  auto scope = opentelemetry::trace::Scope(span);
  internal::InjectTraceContext(context, *propagator_);
  return internal::EndSpan(context, *span,
                           child_->PartitionRead(context, options, request));
}

std::unique_ptr<google::cloud::internal::StreamingReadRpc<
    google::spanner::v1::BatchWriteResponse>>
SpannerTracingStub::BatchWrite(
    std::shared_ptr<grpc::ClientContext> context, Options const& options,
    google::spanner::v1::BatchWriteRequest const& request) {
  auto span = internal::MakeSpanGrpc("google.spanner.v1.Spanner", "BatchWrite");
  auto scope = opentelemetry::trace::Scope(span);
  internal::InjectTraceContext(*context, *propagator_);
  auto stream = child_->BatchWrite(context, options, request);
  return std::make_unique<internal::StreamingReadRpcTracing<
      google::spanner::v1::BatchWriteResponse>>(
      std::move(context), std::move(stream), std::move(span));
}

future<StatusOr<google::spanner::v1::Session>>
SpannerTracingStub::AsyncCreateSession(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::spanner::v1::CreateSessionRequest const& request) {
  auto span =
      internal::MakeSpanGrpc("google.spanner.v1.Spanner", "CreateSession");
  internal::OTelScope scope(span);
  internal::InjectTraceContext(*context, *propagator_);
  auto f = child_->AsyncCreateSession(cq, context, std::move(options), request);
  return internal::EndSpan(std::move(context), std::move(span), std::move(f));
}

future<StatusOr<google::spanner::v1::BatchCreateSessionsResponse>>
SpannerTracingStub::AsyncBatchCreateSessions(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::spanner::v1::BatchCreateSessionsRequest const& request) {
  auto span = internal::MakeSpanGrpc("google.spanner.v1.Spanner",
                                     "BatchCreateSessions");
  internal::OTelScope scope(span);
  internal::InjectTraceContext(*context, *propagator_);
  auto f = child_->AsyncBatchCreateSessions(cq, context, std::move(options),
                                            request);
  return internal::EndSpan(std::move(context), std::move(span), std::move(f));
}

future<Status> SpannerTracingStub::AsyncDeleteSession(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::spanner::v1::DeleteSessionRequest const& request) {
  auto span =
      internal::MakeSpanGrpc("google.spanner.v1.Spanner", "DeleteSession");
  internal::OTelScope scope(span);
  internal::InjectTraceContext(*context, *propagator_);
  auto f = child_->AsyncDeleteSession(cq, context, std::move(options), request);
  return internal::EndSpan(std::move(context), std::move(span), std::move(f));
}

future<StatusOr<google::spanner::v1::ResultSet>>
SpannerTracingStub::AsyncExecuteSql(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::spanner::v1::ExecuteSqlRequest const& request) {
  auto span = internal::MakeSpanGrpc("google.spanner.v1.Spanner", "ExecuteSql");
  internal::OTelScope scope(span);
  internal::InjectTraceContext(*context, *propagator_);
  auto f = child_->AsyncExecuteSql(cq, context, std::move(options), request);
  return internal::EndSpan(std::move(context), std::move(span), std::move(f));
}

#endif  // GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY

std::shared_ptr<SpannerStub> MakeSpannerTracingStub(
    std::shared_ptr<SpannerStub> stub) {
#ifdef GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY
  return std::make_shared<SpannerTracingStub>(std::move(stub));
#else
  return stub;
#endif  // GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace spanner_internal
}  // namespace cloud
}  // namespace google
