// Copyright 2025 Google LLC
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
// source: google/cloud/storagebatchoperations/v1/storage_batch_operations.proto

#include "google/cloud/storagebatchoperations/v1/internal/storage_batch_operations_tracing_stub.h"
#include "google/cloud/internal/grpc_opentelemetry.h"
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace storagebatchoperations_v1_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

#ifdef GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY

StorageBatchOperationsTracingStub::StorageBatchOperationsTracingStub(
    std::shared_ptr<StorageBatchOperationsStub> child)
    : child_(std::move(child)), propagator_(internal::MakePropagator()) {}

StatusOr<google::cloud::storagebatchoperations::v1::ListJobsResponse>
StorageBatchOperationsTracingStub::ListJobs(
    grpc::ClientContext& context, Options const& options,
    google::cloud::storagebatchoperations::v1::ListJobsRequest const& request) {
  auto span = internal::MakeSpanGrpc(
      "google.cloud.storagebatchoperations.v1.StorageBatchOperations",
      "ListJobs");
  auto scope = opentelemetry::trace::Scope(span);
  internal::InjectTraceContext(context, *propagator_);
  return internal::EndSpan(context, *span,
                           child_->ListJobs(context, options, request));
}

StatusOr<google::cloud::storagebatchoperations::v1::Job>
StorageBatchOperationsTracingStub::GetJob(
    grpc::ClientContext& context, Options const& options,
    google::cloud::storagebatchoperations::v1::GetJobRequest const& request) {
  auto span = internal::MakeSpanGrpc(
      "google.cloud.storagebatchoperations.v1.StorageBatchOperations",
      "GetJob");
  auto scope = opentelemetry::trace::Scope(span);
  internal::InjectTraceContext(context, *propagator_);
  return internal::EndSpan(context, *span,
                           child_->GetJob(context, options, request));
}

future<StatusOr<google::longrunning::Operation>>
StorageBatchOperationsTracingStub::AsyncCreateJob(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::cloud::storagebatchoperations::v1::CreateJobRequest const&
        request) {
  auto span = internal::MakeSpanGrpc(
      "google.cloud.storagebatchoperations.v1.StorageBatchOperations",
      "CreateJob");
  internal::OTelScope scope(span);
  internal::InjectTraceContext(*context, *propagator_);
  auto f = child_->AsyncCreateJob(cq, context, std::move(options), request);
  return internal::EndSpan(std::move(context), std::move(span), std::move(f));
}

StatusOr<google::longrunning::Operation>
StorageBatchOperationsTracingStub::CreateJob(
    grpc::ClientContext& context, Options options,
    google::cloud::storagebatchoperations::v1::CreateJobRequest const&
        request) {
  auto span = internal::MakeSpanGrpc(
      "google.cloud.storagebatchoperations.v1.StorageBatchOperations",
      "CreateJob");
  auto scope = opentelemetry::trace::Scope(span);
  internal::InjectTraceContext(context, *propagator_);
  return internal::EndSpan(context, *span,
                           child_->CreateJob(context, options, request));
}

Status StorageBatchOperationsTracingStub::DeleteJob(
    grpc::ClientContext& context, Options const& options,
    google::cloud::storagebatchoperations::v1::DeleteJobRequest const&
        request) {
  auto span = internal::MakeSpanGrpc(
      "google.cloud.storagebatchoperations.v1.StorageBatchOperations",
      "DeleteJob");
  auto scope = opentelemetry::trace::Scope(span);
  internal::InjectTraceContext(context, *propagator_);
  return internal::EndSpan(context, *span,
                           child_->DeleteJob(context, options, request));
}

StatusOr<google::cloud::storagebatchoperations::v1::CancelJobResponse>
StorageBatchOperationsTracingStub::CancelJob(
    grpc::ClientContext& context, Options const& options,
    google::cloud::storagebatchoperations::v1::CancelJobRequest const&
        request) {
  auto span = internal::MakeSpanGrpc(
      "google.cloud.storagebatchoperations.v1.StorageBatchOperations",
      "CancelJob");
  auto scope = opentelemetry::trace::Scope(span);
  internal::InjectTraceContext(context, *propagator_);
  return internal::EndSpan(context, *span,
                           child_->CancelJob(context, options, request));
}

StatusOr<google::cloud::location::ListLocationsResponse>
StorageBatchOperationsTracingStub::ListLocations(
    grpc::ClientContext& context, Options const& options,
    google::cloud::location::ListLocationsRequest const& request) {
  auto span = internal::MakeSpanGrpc(
      "google.cloud.storagebatchoperations.v1.StorageBatchOperations",
      "ListLocations");
  auto scope = opentelemetry::trace::Scope(span);
  internal::InjectTraceContext(context, *propagator_);
  return internal::EndSpan(context, *span,
                           child_->ListLocations(context, options, request));
}

StatusOr<google::cloud::location::Location>
StorageBatchOperationsTracingStub::GetLocation(
    grpc::ClientContext& context, Options const& options,
    google::cloud::location::GetLocationRequest const& request) {
  auto span = internal::MakeSpanGrpc(
      "google.cloud.storagebatchoperations.v1.StorageBatchOperations",
      "GetLocation");
  auto scope = opentelemetry::trace::Scope(span);
  internal::InjectTraceContext(context, *propagator_);
  return internal::EndSpan(context, *span,
                           child_->GetLocation(context, options, request));
}

StatusOr<google::longrunning::ListOperationsResponse>
StorageBatchOperationsTracingStub::ListOperations(
    grpc::ClientContext& context, Options const& options,
    google::longrunning::ListOperationsRequest const& request) {
  auto span = internal::MakeSpanGrpc(
      "google.cloud.storagebatchoperations.v1.StorageBatchOperations",
      "ListOperations");
  auto scope = opentelemetry::trace::Scope(span);
  internal::InjectTraceContext(context, *propagator_);
  return internal::EndSpan(context, *span,
                           child_->ListOperations(context, options, request));
}

StatusOr<google::longrunning::Operation>
StorageBatchOperationsTracingStub::GetOperation(
    grpc::ClientContext& context, Options const& options,
    google::longrunning::GetOperationRequest const& request) {
  auto span = internal::MakeSpanGrpc(
      "google.cloud.storagebatchoperations.v1.StorageBatchOperations",
      "GetOperation");
  auto scope = opentelemetry::trace::Scope(span);
  internal::InjectTraceContext(context, *propagator_);
  return internal::EndSpan(context, *span,
                           child_->GetOperation(context, options, request));
}

Status StorageBatchOperationsTracingStub::DeleteOperation(
    grpc::ClientContext& context, Options const& options,
    google::longrunning::DeleteOperationRequest const& request) {
  auto span = internal::MakeSpanGrpc(
      "google.cloud.storagebatchoperations.v1.StorageBatchOperations",
      "DeleteOperation");
  auto scope = opentelemetry::trace::Scope(span);
  internal::InjectTraceContext(context, *propagator_);
  return internal::EndSpan(context, *span,
                           child_->DeleteOperation(context, options, request));
}

Status StorageBatchOperationsTracingStub::CancelOperation(
    grpc::ClientContext& context, Options const& options,
    google::longrunning::CancelOperationRequest const& request) {
  auto span = internal::MakeSpanGrpc(
      "google.cloud.storagebatchoperations.v1.StorageBatchOperations",
      "CancelOperation");
  auto scope = opentelemetry::trace::Scope(span);
  internal::InjectTraceContext(context, *propagator_);
  return internal::EndSpan(context, *span,
                           child_->CancelOperation(context, options, request));
}

future<StatusOr<google::longrunning::Operation>>
StorageBatchOperationsTracingStub::AsyncGetOperation(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::longrunning::GetOperationRequest const& request) {
  auto span =
      internal::MakeSpanGrpc("google.longrunning.Operations", "GetOperation");
  internal::OTelScope scope(span);
  internal::InjectTraceContext(*context, *propagator_);
  auto f = child_->AsyncGetOperation(cq, context, std::move(options), request);
  return internal::EndSpan(std::move(context), std::move(span), std::move(f));
}

future<Status> StorageBatchOperationsTracingStub::AsyncCancelOperation(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::longrunning::CancelOperationRequest const& request) {
  auto span = internal::MakeSpanGrpc("google.longrunning.Operations",
                                     "CancelOperation");
  internal::OTelScope scope(span);
  internal::InjectTraceContext(*context, *propagator_);
  auto f =
      child_->AsyncCancelOperation(cq, context, std::move(options), request);
  return internal::EndSpan(std::move(context), std::move(span), std::move(f));
}

#endif  // GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY

std::shared_ptr<StorageBatchOperationsStub>
MakeStorageBatchOperationsTracingStub(
    std::shared_ptr<StorageBatchOperationsStub> stub) {
#ifdef GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY
  return std::make_shared<StorageBatchOperationsTracingStub>(std::move(stub));
#else
  return stub;
#endif  // GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace storagebatchoperations_v1_internal
}  // namespace cloud
}  // namespace google
