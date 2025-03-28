// Copyright 2022 Google LLC
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
// source: google/cloud/dialogflow/cx/v3/environment.proto

#include "google/cloud/dialogflow_cx/internal/environments_stub.h"
#include "google/cloud/grpc_error_delegate.h"
#include "google/cloud/status_or.h"
#include <google/cloud/dialogflow/cx/v3/environment.grpc.pb.h>
#include <google/longrunning/operations.grpc.pb.h>
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace dialogflow_cx_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

EnvironmentsStub::~EnvironmentsStub() = default;

StatusOr<google::cloud::dialogflow::cx::v3::ListEnvironmentsResponse>
DefaultEnvironmentsStub::ListEnvironments(
    grpc::ClientContext& context, Options const&,
    google::cloud::dialogflow::cx::v3::ListEnvironmentsRequest const& request) {
  google::cloud::dialogflow::cx::v3::ListEnvironmentsResponse response;
  auto status = grpc_stub_->ListEnvironments(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::dialogflow::cx::v3::Environment>
DefaultEnvironmentsStub::GetEnvironment(
    grpc::ClientContext& context, Options const&,
    google::cloud::dialogflow::cx::v3::GetEnvironmentRequest const& request) {
  google::cloud::dialogflow::cx::v3::Environment response;
  auto status = grpc_stub_->GetEnvironment(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

future<StatusOr<google::longrunning::Operation>>
DefaultEnvironmentsStub::AsyncCreateEnvironment(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions,
    google::cloud::dialogflow::cx::v3::CreateEnvironmentRequest const&
        request) {
  return internal::MakeUnaryRpcImpl<
      google::cloud::dialogflow::cx::v3::CreateEnvironmentRequest,
      google::longrunning::Operation>(
      cq,
      [this](grpc::ClientContext* context,
             google::cloud::dialogflow::cx::v3::CreateEnvironmentRequest const&
                 request,
             grpc::CompletionQueue* cq) {
        return grpc_stub_->AsyncCreateEnvironment(context, request, cq);
      },
      request, std::move(context));
}

StatusOr<google::longrunning::Operation>
DefaultEnvironmentsStub::CreateEnvironment(
    grpc::ClientContext& context, Options,
    google::cloud::dialogflow::cx::v3::CreateEnvironmentRequest const&
        request) {
  google::longrunning::Operation response;
  auto status = grpc_stub_->CreateEnvironment(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

future<StatusOr<google::longrunning::Operation>>
DefaultEnvironmentsStub::AsyncUpdateEnvironment(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions,
    google::cloud::dialogflow::cx::v3::UpdateEnvironmentRequest const&
        request) {
  return internal::MakeUnaryRpcImpl<
      google::cloud::dialogflow::cx::v3::UpdateEnvironmentRequest,
      google::longrunning::Operation>(
      cq,
      [this](grpc::ClientContext* context,
             google::cloud::dialogflow::cx::v3::UpdateEnvironmentRequest const&
                 request,
             grpc::CompletionQueue* cq) {
        return grpc_stub_->AsyncUpdateEnvironment(context, request, cq);
      },
      request, std::move(context));
}

StatusOr<google::longrunning::Operation>
DefaultEnvironmentsStub::UpdateEnvironment(
    grpc::ClientContext& context, Options,
    google::cloud::dialogflow::cx::v3::UpdateEnvironmentRequest const&
        request) {
  google::longrunning::Operation response;
  auto status = grpc_stub_->UpdateEnvironment(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

Status DefaultEnvironmentsStub::DeleteEnvironment(
    grpc::ClientContext& context, Options const&,
    google::cloud::dialogflow::cx::v3::DeleteEnvironmentRequest const&
        request) {
  google::protobuf::Empty response;
  auto status = grpc_stub_->DeleteEnvironment(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return google::cloud::Status();
}

StatusOr<google::cloud::dialogflow::cx::v3::LookupEnvironmentHistoryResponse>
DefaultEnvironmentsStub::LookupEnvironmentHistory(
    grpc::ClientContext& context, Options const&,
    google::cloud::dialogflow::cx::v3::LookupEnvironmentHistoryRequest const&
        request) {
  google::cloud::dialogflow::cx::v3::LookupEnvironmentHistoryResponse response;
  auto status =
      grpc_stub_->LookupEnvironmentHistory(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

future<StatusOr<google::longrunning::Operation>>
DefaultEnvironmentsStub::AsyncRunContinuousTest(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions,
    google::cloud::dialogflow::cx::v3::RunContinuousTestRequest const&
        request) {
  return internal::MakeUnaryRpcImpl<
      google::cloud::dialogflow::cx::v3::RunContinuousTestRequest,
      google::longrunning::Operation>(
      cq,
      [this](grpc::ClientContext* context,
             google::cloud::dialogflow::cx::v3::RunContinuousTestRequest const&
                 request,
             grpc::CompletionQueue* cq) {
        return grpc_stub_->AsyncRunContinuousTest(context, request, cq);
      },
      request, std::move(context));
}

StatusOr<google::longrunning::Operation>
DefaultEnvironmentsStub::RunContinuousTest(
    grpc::ClientContext& context, Options,
    google::cloud::dialogflow::cx::v3::RunContinuousTestRequest const&
        request) {
  google::longrunning::Operation response;
  auto status = grpc_stub_->RunContinuousTest(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::dialogflow::cx::v3::ListContinuousTestResultsResponse>
DefaultEnvironmentsStub::ListContinuousTestResults(
    grpc::ClientContext& context, Options const&,
    google::cloud::dialogflow::cx::v3::ListContinuousTestResultsRequest const&
        request) {
  google::cloud::dialogflow::cx::v3::ListContinuousTestResultsResponse response;
  auto status =
      grpc_stub_->ListContinuousTestResults(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

future<StatusOr<google::longrunning::Operation>>
DefaultEnvironmentsStub::AsyncDeployFlow(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions,
    google::cloud::dialogflow::cx::v3::DeployFlowRequest const& request) {
  return internal::MakeUnaryRpcImpl<
      google::cloud::dialogflow::cx::v3::DeployFlowRequest,
      google::longrunning::Operation>(
      cq,
      [this](
          grpc::ClientContext* context,
          google::cloud::dialogflow::cx::v3::DeployFlowRequest const& request,
          grpc::CompletionQueue* cq) {
        return grpc_stub_->AsyncDeployFlow(context, request, cq);
      },
      request, std::move(context));
}

StatusOr<google::longrunning::Operation> DefaultEnvironmentsStub::DeployFlow(
    grpc::ClientContext& context, Options,
    google::cloud::dialogflow::cx::v3::DeployFlowRequest const& request) {
  google::longrunning::Operation response;
  auto status = grpc_stub_->DeployFlow(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::location::ListLocationsResponse>
DefaultEnvironmentsStub::ListLocations(
    grpc::ClientContext& context, Options const&,
    google::cloud::location::ListLocationsRequest const& request) {
  google::cloud::location::ListLocationsResponse response;
  auto status = locations_stub_->ListLocations(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::location::Location>
DefaultEnvironmentsStub::GetLocation(
    grpc::ClientContext& context, Options const&,
    google::cloud::location::GetLocationRequest const& request) {
  google::cloud::location::Location response;
  auto status = locations_stub_->GetLocation(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::longrunning::ListOperationsResponse>
DefaultEnvironmentsStub::ListOperations(
    grpc::ClientContext& context, Options const&,
    google::longrunning::ListOperationsRequest const& request) {
  google::longrunning::ListOperationsResponse response;
  auto status = operations_stub_->ListOperations(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::longrunning::Operation> DefaultEnvironmentsStub::GetOperation(
    grpc::ClientContext& context, Options const&,
    google::longrunning::GetOperationRequest const& request) {
  google::longrunning::Operation response;
  auto status = operations_stub_->GetOperation(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

Status DefaultEnvironmentsStub::CancelOperation(
    grpc::ClientContext& context, Options const&,
    google::longrunning::CancelOperationRequest const& request) {
  google::protobuf::Empty response;
  auto status = operations_stub_->CancelOperation(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return google::cloud::Status();
}

future<StatusOr<google::longrunning::Operation>>
DefaultEnvironmentsStub::AsyncGetOperation(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    google::cloud::internal::ImmutableOptions,
    google::longrunning::GetOperationRequest const& request) {
  return internal::MakeUnaryRpcImpl<google::longrunning::GetOperationRequest,
                                    google::longrunning::Operation>(
      cq,
      [this](grpc::ClientContext* context,
             google::longrunning::GetOperationRequest const& request,
             grpc::CompletionQueue* cq) {
        return operations_stub_->AsyncGetOperation(context, request, cq);
      },
      request, std::move(context));
}

future<Status> DefaultEnvironmentsStub::AsyncCancelOperation(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    google::cloud::internal::ImmutableOptions,
    google::longrunning::CancelOperationRequest const& request) {
  return internal::MakeUnaryRpcImpl<google::longrunning::CancelOperationRequest,
                                    google::protobuf::Empty>(
             cq,
             [this](grpc::ClientContext* context,
                    google::longrunning::CancelOperationRequest const& request,
                    grpc::CompletionQueue* cq) {
               return operations_stub_->AsyncCancelOperation(context, request,
                                                             cq);
             },
             request, std::move(context))
      .then([](future<StatusOr<google::protobuf::Empty>> f) {
        return f.get().status();
      });
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace dialogflow_cx_internal
}  // namespace cloud
}  // namespace google
