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
// source: google/iam/v3/policy_bindings_service.proto

#include "google/cloud/iam/v3/internal/policy_bindings_auth_decorator.h"
#include <google/iam/v3/policy_bindings_service.grpc.pb.h>
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace iam_v3_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

PolicyBindingsAuth::PolicyBindingsAuth(
    std::shared_ptr<google::cloud::internal::GrpcAuthenticationStrategy> auth,
    std::shared_ptr<PolicyBindingsStub> child)
    : auth_(std::move(auth)), child_(std::move(child)) {}

future<StatusOr<google::longrunning::Operation>>
PolicyBindingsAuth::AsyncCreatePolicyBinding(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::iam::v3::CreatePolicyBindingRequest const& request) {
  using ReturnType = StatusOr<google::longrunning::Operation>;
  return auth_->AsyncConfigureContext(std::move(context))
      .then([cq, child = child_, options = std::move(options),
             request](future<StatusOr<std::shared_ptr<grpc::ClientContext>>>
                          f) mutable {
        auto context = f.get();
        if (!context) {
          return make_ready_future(ReturnType(std::move(context).status()));
        }
        return child->AsyncCreatePolicyBinding(cq, *std::move(context),
                                               std::move(options), request);
      });
}

StatusOr<google::longrunning::Operation>
PolicyBindingsAuth::CreatePolicyBinding(
    grpc::ClientContext& context, Options options,
    google::iam::v3::CreatePolicyBindingRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->CreatePolicyBinding(context, options, request);
}

StatusOr<google::iam::v3::PolicyBinding> PolicyBindingsAuth::GetPolicyBinding(
    grpc::ClientContext& context, Options const& options,
    google::iam::v3::GetPolicyBindingRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->GetPolicyBinding(context, options, request);
}

future<StatusOr<google::longrunning::Operation>>
PolicyBindingsAuth::AsyncUpdatePolicyBinding(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::iam::v3::UpdatePolicyBindingRequest const& request) {
  using ReturnType = StatusOr<google::longrunning::Operation>;
  return auth_->AsyncConfigureContext(std::move(context))
      .then([cq, child = child_, options = std::move(options),
             request](future<StatusOr<std::shared_ptr<grpc::ClientContext>>>
                          f) mutable {
        auto context = f.get();
        if (!context) {
          return make_ready_future(ReturnType(std::move(context).status()));
        }
        return child->AsyncUpdatePolicyBinding(cq, *std::move(context),
                                               std::move(options), request);
      });
}

StatusOr<google::longrunning::Operation>
PolicyBindingsAuth::UpdatePolicyBinding(
    grpc::ClientContext& context, Options options,
    google::iam::v3::UpdatePolicyBindingRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->UpdatePolicyBinding(context, options, request);
}

future<StatusOr<google::longrunning::Operation>>
PolicyBindingsAuth::AsyncDeletePolicyBinding(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::iam::v3::DeletePolicyBindingRequest const& request) {
  using ReturnType = StatusOr<google::longrunning::Operation>;
  return auth_->AsyncConfigureContext(std::move(context))
      .then([cq, child = child_, options = std::move(options),
             request](future<StatusOr<std::shared_ptr<grpc::ClientContext>>>
                          f) mutable {
        auto context = f.get();
        if (!context) {
          return make_ready_future(ReturnType(std::move(context).status()));
        }
        return child->AsyncDeletePolicyBinding(cq, *std::move(context),
                                               std::move(options), request);
      });
}

StatusOr<google::longrunning::Operation>
PolicyBindingsAuth::DeletePolicyBinding(
    grpc::ClientContext& context, Options options,
    google::iam::v3::DeletePolicyBindingRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->DeletePolicyBinding(context, options, request);
}

StatusOr<google::iam::v3::ListPolicyBindingsResponse>
PolicyBindingsAuth::ListPolicyBindings(
    grpc::ClientContext& context, Options const& options,
    google::iam::v3::ListPolicyBindingsRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->ListPolicyBindings(context, options, request);
}

StatusOr<google::iam::v3::SearchTargetPolicyBindingsResponse>
PolicyBindingsAuth::SearchTargetPolicyBindings(
    grpc::ClientContext& context, Options const& options,
    google::iam::v3::SearchTargetPolicyBindingsRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->SearchTargetPolicyBindings(context, options, request);
}

StatusOr<google::longrunning::Operation> PolicyBindingsAuth::GetOperation(
    grpc::ClientContext& context, Options const& options,
    google::longrunning::GetOperationRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->GetOperation(context, options, request);
}

future<StatusOr<google::longrunning::Operation>>
PolicyBindingsAuth::AsyncGetOperation(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::longrunning::GetOperationRequest const& request) {
  using ReturnType = StatusOr<google::longrunning::Operation>;
  return auth_->AsyncConfigureContext(std::move(context))
      .then([cq, child = child_, options = std::move(options),
             request](future<StatusOr<std::shared_ptr<grpc::ClientContext>>>
                          f) mutable {
        auto context = f.get();
        if (!context) {
          return make_ready_future(ReturnType(std::move(context).status()));
        }
        return child->AsyncGetOperation(cq, *std::move(context),
                                        std::move(options), request);
      });
}

future<Status> PolicyBindingsAuth::AsyncCancelOperation(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions options,
    google::longrunning::CancelOperationRequest const& request) {
  return auth_->AsyncConfigureContext(std::move(context))
      .then([cq, child = child_, options = std::move(options),
             request](future<StatusOr<std::shared_ptr<grpc::ClientContext>>>
                          f) mutable {
        auto context = f.get();
        if (!context) return make_ready_future(std::move(context).status());
        return child->AsyncCancelOperation(cq, *std::move(context),
                                           std::move(options), request);
      });
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace iam_v3_internal
}  // namespace cloud
}  // namespace google
