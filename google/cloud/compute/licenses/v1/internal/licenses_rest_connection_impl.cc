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
// source: google/cloud/compute/licenses/v1/licenses.proto

#include "google/cloud/compute/licenses/v1/internal/licenses_rest_connection_impl.h"
#include "google/cloud/compute/licenses/v1/internal/licenses_rest_stub_factory.h"
#include "google/cloud/common_options.h"
#include "google/cloud/credentials.h"
#include "google/cloud/internal/async_rest_long_running_operation_custom.h"
#include "google/cloud/internal/extract_long_running_result.h"
#include "google/cloud/internal/pagination_range.h"
#include "google/cloud/internal/rest_lro_helpers.h"
#include "google/cloud/internal/rest_retry_loop.h"
#include "google/cloud/rest_options.h"
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace compute_licenses_v1_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

LicensesRestConnectionImpl::LicensesRestConnectionImpl(
    std::unique_ptr<google::cloud::BackgroundThreads> background,
    std::shared_ptr<compute_licenses_v1_internal::LicensesRestStub> stub,
    Options options)
    : background_(std::move(background)),
      stub_(std::move(stub)),
      options_(internal::MergeOptions(std::move(options),
                                      LicensesConnection::options())) {}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
LicensesRestConnectionImpl::DeleteLicense(
    google::cloud::cpp::compute::licenses::v1::DeleteLicenseRequest const&
        request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return rest_internal::AsyncRestLongRunningOperation<
      google::cloud::cpp::compute::v1::Operation,
      google::cloud::cpp::compute::v1::Operation,
      google::cloud::cpp::compute::global_operations::v1::GetOperationRequest,
      google::cloud::cpp::compute::global_operations::v1::
          DeleteOperationRequest>(
      background_->cq(), current, request,
      [stub = stub_](
          CompletionQueue& cq,
          std::unique_ptr<rest_internal::RestContext> context,
          google::cloud::internal::ImmutableOptions options,
          google::cloud::cpp::compute::licenses::v1::DeleteLicenseRequest const&
              request) {
        return stub->AsyncDeleteLicense(cq, std::move(context),
                                        std::move(options), request);
      },
      [stub = stub_](CompletionQueue& cq,
                     std::unique_ptr<rest_internal::RestContext> context,
                     google::cloud::internal::ImmutableOptions options,
                     google::cloud::cpp::compute::global_operations::v1::
                         GetOperationRequest const& request) {
        return stub->AsyncGetOperation(cq, std::move(context),
                                       std::move(options), request);
      },
      [stub = stub_](CompletionQueue& cq,
                     std::unique_ptr<rest_internal::RestContext> context,
                     google::cloud::internal::ImmutableOptions options,
                     google::cloud::cpp::compute::global_operations::v1::
                         DeleteOperationRequest const& request) {
        return stub->AsyncCancelOperation(cq, std::move(context),
                                          std::move(options), request);
      },
      [](StatusOr<google::cloud::cpp::compute::v1::Operation> op,
         std::string const&) { return op; },
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->DeleteLicense(request),
      polling_policy(*current), __func__,
      [](google::cloud::cpp::compute::v1::Operation const& op) {
        return op.status() == "DONE";
      },
      [request](std::string const& op,
                google::cloud::cpp::compute::global_operations::v1::
                    GetOperationRequest& r) {
        r.set_project(request.project());
        r.set_operation(op);
      },
      [request](std::string const& op,
                google::cloud::cpp::compute::global_operations::v1::
                    DeleteOperationRequest& r) {
        r.set_project(request.project());
        r.set_operation(op);
      });
}

StatusOr<google::cloud::cpp::compute::v1::Operation>
LicensesRestConnectionImpl::DeleteLicense(
    NoAwaitTag,
    google::cloud::cpp::compute::licenses::v1::DeleteLicenseRequest const&
        request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::rest_internal::RestRetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->DeleteLicense(request),
      [this](
          rest_internal::RestContext& rest_context, Options const& options,
          google::cloud::cpp::compute::licenses::v1::DeleteLicenseRequest const&
              request) {
        return stub_->DeleteLicense(rest_context, options, request);
      },
      *current, request, __func__);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
LicensesRestConnectionImpl::DeleteLicense(
    google::cloud::cpp::compute::v1::Operation const& operation) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return rest_internal::AsyncRestAwaitLongRunningOperation<
      google::cloud::cpp::compute::v1::Operation,
      google::cloud::cpp::compute::v1::Operation,
      google::cloud::cpp::compute::global_operations::v1::GetOperationRequest,
      google::cloud::cpp::compute::global_operations::v1::
          DeleteOperationRequest>(
      background_->cq(), current, operation,
      [stub = stub_](CompletionQueue& cq,
                     std::unique_ptr<rest_internal::RestContext> context,
                     google::cloud::internal::ImmutableOptions options,
                     google::cloud::cpp::compute::global_operations::v1::
                         GetOperationRequest const& request) {
        return stub->AsyncGetOperation(cq, std::move(context),
                                       std::move(options), request);
      },
      [stub = stub_](CompletionQueue& cq,
                     std::unique_ptr<rest_internal::RestContext> context,
                     google::cloud::internal::ImmutableOptions options,
                     google::cloud::cpp::compute::global_operations::v1::
                         DeleteOperationRequest const& request) {
        return stub->AsyncCancelOperation(cq, std::move(context),
                                          std::move(options), request);
      },
      [](StatusOr<google::cloud::cpp::compute::v1::Operation> op,
         std::string const&) { return op; },
      polling_policy(*current), __func__,
      [](google::cloud::cpp::compute::v1::Operation const& op) {
        return op.status() == "DONE";
      },
      [operation](std::string const&,
                  google::cloud::cpp::compute::global_operations::v1::
                      GetOperationRequest& r) {
        auto info = google::cloud::rest_internal::ParseComputeOperationInfo(
            operation.self_link());

        r.set_project(info.project);
        r.set_operation(info.operation);
      },
      [operation](std::string const&,
                  google::cloud::cpp::compute::global_operations::v1::
                      DeleteOperationRequest& r) {
        auto info = google::cloud::rest_internal::ParseComputeOperationInfo(
            operation.self_link());

        r.set_project(info.project);
        r.set_operation(info.operation);
      });
}

StatusOr<google::cloud::cpp::compute::v1::License>
LicensesRestConnectionImpl::GetLicense(
    google::cloud::cpp::compute::licenses::v1::GetLicenseRequest const&
        request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::rest_internal::RestRetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->GetLicense(request),
      [this](rest_internal::RestContext& rest_context, Options const& options,
             google::cloud::cpp::compute::licenses::v1::GetLicenseRequest const&
                 request) {
        return stub_->GetLicense(rest_context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::cloud::cpp::compute::v1::Policy>
LicensesRestConnectionImpl::GetIamPolicy(
    google::cloud::cpp::compute::licenses::v1::GetIamPolicyRequest const&
        request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::rest_internal::RestRetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->GetIamPolicy(request),
      [this](
          rest_internal::RestContext& rest_context, Options const& options,
          google::cloud::cpp::compute::licenses::v1::GetIamPolicyRequest const&
              request) {
        return stub_->GetIamPolicy(rest_context, options, request);
      },
      *current, request, __func__);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
LicensesRestConnectionImpl::InsertLicense(
    google::cloud::cpp::compute::licenses::v1::InsertLicenseRequest const&
        request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return rest_internal::AsyncRestLongRunningOperation<
      google::cloud::cpp::compute::v1::Operation,
      google::cloud::cpp::compute::v1::Operation,
      google::cloud::cpp::compute::global_operations::v1::GetOperationRequest,
      google::cloud::cpp::compute::global_operations::v1::
          DeleteOperationRequest>(
      background_->cq(), current, request,
      [stub = stub_](
          CompletionQueue& cq,
          std::unique_ptr<rest_internal::RestContext> context,
          google::cloud::internal::ImmutableOptions options,
          google::cloud::cpp::compute::licenses::v1::InsertLicenseRequest const&
              request) {
        return stub->AsyncInsertLicense(cq, std::move(context),
                                        std::move(options), request);
      },
      [stub = stub_](CompletionQueue& cq,
                     std::unique_ptr<rest_internal::RestContext> context,
                     google::cloud::internal::ImmutableOptions options,
                     google::cloud::cpp::compute::global_operations::v1::
                         GetOperationRequest const& request) {
        return stub->AsyncGetOperation(cq, std::move(context),
                                       std::move(options), request);
      },
      [stub = stub_](CompletionQueue& cq,
                     std::unique_ptr<rest_internal::RestContext> context,
                     google::cloud::internal::ImmutableOptions options,
                     google::cloud::cpp::compute::global_operations::v1::
                         DeleteOperationRequest const& request) {
        return stub->AsyncCancelOperation(cq, std::move(context),
                                          std::move(options), request);
      },
      [](StatusOr<google::cloud::cpp::compute::v1::Operation> op,
         std::string const&) { return op; },
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->InsertLicense(request),
      polling_policy(*current), __func__,
      [](google::cloud::cpp::compute::v1::Operation const& op) {
        return op.status() == "DONE";
      },
      [request](std::string const& op,
                google::cloud::cpp::compute::global_operations::v1::
                    GetOperationRequest& r) {
        r.set_project(request.project());
        r.set_operation(op);
      },
      [request](std::string const& op,
                google::cloud::cpp::compute::global_operations::v1::
                    DeleteOperationRequest& r) {
        r.set_project(request.project());
        r.set_operation(op);
      });
}

StatusOr<google::cloud::cpp::compute::v1::Operation>
LicensesRestConnectionImpl::InsertLicense(
    NoAwaitTag,
    google::cloud::cpp::compute::licenses::v1::InsertLicenseRequest const&
        request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::rest_internal::RestRetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->InsertLicense(request),
      [this](
          rest_internal::RestContext& rest_context, Options const& options,
          google::cloud::cpp::compute::licenses::v1::InsertLicenseRequest const&
              request) {
        return stub_->InsertLicense(rest_context, options, request);
      },
      *current, request, __func__);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
LicensesRestConnectionImpl::InsertLicense(
    google::cloud::cpp::compute::v1::Operation const& operation) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return rest_internal::AsyncRestAwaitLongRunningOperation<
      google::cloud::cpp::compute::v1::Operation,
      google::cloud::cpp::compute::v1::Operation,
      google::cloud::cpp::compute::global_operations::v1::GetOperationRequest,
      google::cloud::cpp::compute::global_operations::v1::
          DeleteOperationRequest>(
      background_->cq(), current, operation,
      [stub = stub_](CompletionQueue& cq,
                     std::unique_ptr<rest_internal::RestContext> context,
                     google::cloud::internal::ImmutableOptions options,
                     google::cloud::cpp::compute::global_operations::v1::
                         GetOperationRequest const& request) {
        return stub->AsyncGetOperation(cq, std::move(context),
                                       std::move(options), request);
      },
      [stub = stub_](CompletionQueue& cq,
                     std::unique_ptr<rest_internal::RestContext> context,
                     google::cloud::internal::ImmutableOptions options,
                     google::cloud::cpp::compute::global_operations::v1::
                         DeleteOperationRequest const& request) {
        return stub->AsyncCancelOperation(cq, std::move(context),
                                          std::move(options), request);
      },
      [](StatusOr<google::cloud::cpp::compute::v1::Operation> op,
         std::string const&) { return op; },
      polling_policy(*current), __func__,
      [](google::cloud::cpp::compute::v1::Operation const& op) {
        return op.status() == "DONE";
      },
      [operation](std::string const&,
                  google::cloud::cpp::compute::global_operations::v1::
                      GetOperationRequest& r) {
        auto info = google::cloud::rest_internal::ParseComputeOperationInfo(
            operation.self_link());

        r.set_project(info.project);
        r.set_operation(info.operation);
      },
      [operation](std::string const&,
                  google::cloud::cpp::compute::global_operations::v1::
                      DeleteOperationRequest& r) {
        auto info = google::cloud::rest_internal::ParseComputeOperationInfo(
            operation.self_link());

        r.set_project(info.project);
        r.set_operation(info.operation);
      });
}

StreamRange<google::cloud::cpp::compute::v1::License>
LicensesRestConnectionImpl::ListLicenses(
    google::cloud::cpp::compute::licenses::v1::ListLicensesRequest request) {
  request.clear_page_token();
  auto current = google::cloud::internal::SaveCurrentOptions();
  auto idempotency = idempotency_policy(*current)->ListLicenses(request);
  char const* function_name = __func__;
  return google::cloud::internal::MakePaginationRange<
      StreamRange<google::cloud::cpp::compute::v1::License>>(
      current, std::move(request),
      [idempotency, function_name, stub = stub_,
       retry = std::shared_ptr<compute_licenses_v1::LicensesRetryPolicy>(
           retry_policy(*current)),
       backoff = std::shared_ptr<BackoffPolicy>(backoff_policy(*current))](
          Options const& options,
          google::cloud::cpp::compute::licenses::v1::ListLicensesRequest const&
              r) {
        return google::cloud::rest_internal::RestRetryLoop(
            retry->clone(), backoff->clone(), idempotency,
            [stub](rest_internal::RestContext& rest_context,
                   Options const& options,
                   google::cloud::cpp::compute::licenses::v1::
                       ListLicensesRequest const& request) {
              return stub->ListLicenses(rest_context, options, request);
            },
            options, r, function_name);
      },
      [](google::cloud::cpp::compute::v1::LicensesListResponse r) {
        std::vector<google::cloud::cpp::compute::v1::License> result(
            r.items().size());
        auto& messages = *r.mutable_items();
        std::move(messages.begin(), messages.end(), result.begin());
        return result;
      });
}

StatusOr<google::cloud::cpp::compute::v1::Policy>
LicensesRestConnectionImpl::SetIamPolicy(
    google::cloud::cpp::compute::licenses::v1::SetIamPolicyRequest const&
        request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::rest_internal::RestRetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->SetIamPolicy(request),
      [this](
          rest_internal::RestContext& rest_context, Options const& options,
          google::cloud::cpp::compute::licenses::v1::SetIamPolicyRequest const&
              request) {
        return stub_->SetIamPolicy(rest_context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::cloud::cpp::compute::v1::TestPermissionsResponse>
LicensesRestConnectionImpl::TestIamPermissions(
    google::cloud::cpp::compute::licenses::v1::TestIamPermissionsRequest const&
        request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::rest_internal::RestRetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->TestIamPermissions(request),
      [this](rest_internal::RestContext& rest_context, Options const& options,
             google::cloud::cpp::compute::licenses::v1::
                 TestIamPermissionsRequest const& request) {
        return stub_->TestIamPermissions(rest_context, options, request);
      },
      *current, request, __func__);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
LicensesRestConnectionImpl::UpdateLicense(
    google::cloud::cpp::compute::licenses::v1::UpdateLicenseRequest const&
        request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return rest_internal::AsyncRestLongRunningOperation<
      google::cloud::cpp::compute::v1::Operation,
      google::cloud::cpp::compute::v1::Operation,
      google::cloud::cpp::compute::global_operations::v1::GetOperationRequest,
      google::cloud::cpp::compute::global_operations::v1::
          DeleteOperationRequest>(
      background_->cq(), current, request,
      [stub = stub_](
          CompletionQueue& cq,
          std::unique_ptr<rest_internal::RestContext> context,
          google::cloud::internal::ImmutableOptions options,
          google::cloud::cpp::compute::licenses::v1::UpdateLicenseRequest const&
              request) {
        return stub->AsyncUpdateLicense(cq, std::move(context),
                                        std::move(options), request);
      },
      [stub = stub_](CompletionQueue& cq,
                     std::unique_ptr<rest_internal::RestContext> context,
                     google::cloud::internal::ImmutableOptions options,
                     google::cloud::cpp::compute::global_operations::v1::
                         GetOperationRequest const& request) {
        return stub->AsyncGetOperation(cq, std::move(context),
                                       std::move(options), request);
      },
      [stub = stub_](CompletionQueue& cq,
                     std::unique_ptr<rest_internal::RestContext> context,
                     google::cloud::internal::ImmutableOptions options,
                     google::cloud::cpp::compute::global_operations::v1::
                         DeleteOperationRequest const& request) {
        return stub->AsyncCancelOperation(cq, std::move(context),
                                          std::move(options), request);
      },
      [](StatusOr<google::cloud::cpp::compute::v1::Operation> op,
         std::string const&) { return op; },
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->UpdateLicense(request),
      polling_policy(*current), __func__,
      [](google::cloud::cpp::compute::v1::Operation const& op) {
        return op.status() == "DONE";
      },
      [request](std::string const& op,
                google::cloud::cpp::compute::global_operations::v1::
                    GetOperationRequest& r) {
        r.set_project(request.project());
        r.set_operation(op);
      },
      [request](std::string const& op,
                google::cloud::cpp::compute::global_operations::v1::
                    DeleteOperationRequest& r) {
        r.set_project(request.project());
        r.set_operation(op);
      });
}

StatusOr<google::cloud::cpp::compute::v1::Operation>
LicensesRestConnectionImpl::UpdateLicense(
    NoAwaitTag,
    google::cloud::cpp::compute::licenses::v1::UpdateLicenseRequest const&
        request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::rest_internal::RestRetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->UpdateLicense(request),
      [this](
          rest_internal::RestContext& rest_context, Options const& options,
          google::cloud::cpp::compute::licenses::v1::UpdateLicenseRequest const&
              request) {
        return stub_->UpdateLicense(rest_context, options, request);
      },
      *current, request, __func__);
}

future<StatusOr<google::cloud::cpp::compute::v1::Operation>>
LicensesRestConnectionImpl::UpdateLicense(
    google::cloud::cpp::compute::v1::Operation const& operation) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return rest_internal::AsyncRestAwaitLongRunningOperation<
      google::cloud::cpp::compute::v1::Operation,
      google::cloud::cpp::compute::v1::Operation,
      google::cloud::cpp::compute::global_operations::v1::GetOperationRequest,
      google::cloud::cpp::compute::global_operations::v1::
          DeleteOperationRequest>(
      background_->cq(), current, operation,
      [stub = stub_](CompletionQueue& cq,
                     std::unique_ptr<rest_internal::RestContext> context,
                     google::cloud::internal::ImmutableOptions options,
                     google::cloud::cpp::compute::global_operations::v1::
                         GetOperationRequest const& request) {
        return stub->AsyncGetOperation(cq, std::move(context),
                                       std::move(options), request);
      },
      [stub = stub_](CompletionQueue& cq,
                     std::unique_ptr<rest_internal::RestContext> context,
                     google::cloud::internal::ImmutableOptions options,
                     google::cloud::cpp::compute::global_operations::v1::
                         DeleteOperationRequest const& request) {
        return stub->AsyncCancelOperation(cq, std::move(context),
                                          std::move(options), request);
      },
      [](StatusOr<google::cloud::cpp::compute::v1::Operation> op,
         std::string const&) { return op; },
      polling_policy(*current), __func__,
      [](google::cloud::cpp::compute::v1::Operation const& op) {
        return op.status() == "DONE";
      },
      [operation](std::string const&,
                  google::cloud::cpp::compute::global_operations::v1::
                      GetOperationRequest& r) {
        auto info = google::cloud::rest_internal::ParseComputeOperationInfo(
            operation.self_link());

        r.set_project(info.project);
        r.set_operation(info.operation);
      },
      [operation](std::string const&,
                  google::cloud::cpp::compute::global_operations::v1::
                      DeleteOperationRequest& r) {
        auto info = google::cloud::rest_internal::ParseComputeOperationInfo(
            operation.self_link());

        r.set_project(info.project);
        r.set_operation(info.operation);
      });
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace compute_licenses_v1_internal
}  // namespace cloud
}  // namespace google
