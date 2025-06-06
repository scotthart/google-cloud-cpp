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
// source: google/cloud/talent/v4/company_service.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_TALENT_V4_COMPANY_CLIENT_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_TALENT_V4_COMPANY_CLIENT_H

#include "google/cloud/talent/v4/company_connection.h"
#include "google/cloud/future.h"
#include "google/cloud/options.h"
#include "google/cloud/polling_policy.h"
#include "google/cloud/status_or.h"
#include "google/cloud/version.h"
#include <memory>
#include <string>

namespace google {
namespace cloud {
namespace talent_v4 {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

///
/// A service that handles company management, including CRUD and enumeration.
///
/// @par Equality
///
/// Instances of this class created via copy-construction or copy-assignment
/// always compare equal. Instances created with equal
/// `std::shared_ptr<*Connection>` objects compare equal. Objects that compare
/// equal share the same underlying resources.
///
/// @par Performance
///
/// Creating a new instance of this class is a relatively expensive operation,
/// new objects establish new connections to the service. In contrast,
/// copy-construction, move-construction, and the corresponding assignment
/// operations are relatively efficient as the copies share all underlying
/// resources.
///
/// @par Thread Safety
///
/// Concurrent access to different instances of this class, even if they compare
/// equal, is guaranteed to work. Two or more threads operating on the same
/// instance of this class is not guaranteed to work. Since copy-construction
/// and move-construction is a relatively efficient operation, consider using
/// such a copy when using this class from multiple threads.
///
class CompanyServiceClient {
 public:
  explicit CompanyServiceClient(
      std::shared_ptr<CompanyServiceConnection> connection, Options opts = {});
  ~CompanyServiceClient();

  ///@{
  /// @name Copy and move support
  CompanyServiceClient(CompanyServiceClient const&) = default;
  CompanyServiceClient& operator=(CompanyServiceClient const&) = default;
  CompanyServiceClient(CompanyServiceClient&&) = default;
  CompanyServiceClient& operator=(CompanyServiceClient&&) = default;
  ///@}

  ///@{
  /// @name Equality
  friend bool operator==(CompanyServiceClient const& a,
                         CompanyServiceClient const& b) {
    return a.connection_ == b.connection_;
  }
  friend bool operator!=(CompanyServiceClient const& a,
                         CompanyServiceClient const& b) {
    return !(a == b);
  }
  ///@}

  // clang-format off
  ///
  /// Creates a new company entity.
  ///
  /// @param parent  Required. Resource name of the tenant under which the company is created.
  ///  @n
  ///  The format is "projects/{project_id}/tenants/{tenant_id}", for example,
  ///  "projects/foo/tenants/bar".
  /// @param company  Required. The company to be created.
  /// @param opts Optional. Override the class-level options, such as retry and
  ///     backoff policies.
  /// @return the result of the RPC. The response message type
  ///     ([google.cloud.talent.v4.Company])
  ///     is mapped to a C++ class using the [Protobuf mapping rules].
  ///     If the request fails, the [`StatusOr`] contains the error details.
  ///
  /// [Protobuf mapping rules]: https://protobuf.dev/reference/cpp/cpp-generated/
  /// [input iterator requirements]: https://en.cppreference.com/w/cpp/named_req/InputIterator
  /// [`std::string`]: https://en.cppreference.com/w/cpp/string/basic_string
  /// [`future`]: @ref google::cloud::future
  /// [`StatusOr`]: @ref google::cloud::StatusOr
  /// [`Status`]: @ref google::cloud::Status
  /// [google.cloud.talent.v4.Company]: @googleapis_reference_link{google/cloud/talent/v4/company.proto#L32}
  /// [google.cloud.talent.v4.CreateCompanyRequest]: @googleapis_reference_link{google/cloud/talent/v4/company_service.proto#L86}
  ///
  // clang-format on
  StatusOr<google::cloud::talent::v4::Company> CreateCompany(
      std::string const& parent,
      google::cloud::talent::v4::Company const& company, Options opts = {});

  // clang-format off
  ///
  /// Creates a new company entity.
  ///
  /// @param request Unary RPCs, such as the one wrapped by this
  ///     function, receive a single `request` proto message which includes all
  ///     the inputs for the RPC. In this case, the proto message is a
  ///     [google.cloud.talent.v4.CreateCompanyRequest].
  ///     Proto messages are converted to C++ classes by Protobuf, using the
  ///     [Protobuf mapping rules].
  /// @param opts Optional. Override the class-level options, such as retry and
  ///     backoff policies.
  /// @return the result of the RPC. The response message type
  ///     ([google.cloud.talent.v4.Company])
  ///     is mapped to a C++ class using the [Protobuf mapping rules].
  ///     If the request fails, the [`StatusOr`] contains the error details.
  ///
  /// [Protobuf mapping rules]: https://protobuf.dev/reference/cpp/cpp-generated/
  /// [input iterator requirements]: https://en.cppreference.com/w/cpp/named_req/InputIterator
  /// [`std::string`]: https://en.cppreference.com/w/cpp/string/basic_string
  /// [`future`]: @ref google::cloud::future
  /// [`StatusOr`]: @ref google::cloud::StatusOr
  /// [`Status`]: @ref google::cloud::Status
  /// [google.cloud.talent.v4.Company]: @googleapis_reference_link{google/cloud/talent/v4/company.proto#L32}
  /// [google.cloud.talent.v4.CreateCompanyRequest]: @googleapis_reference_link{google/cloud/talent/v4/company_service.proto#L86}
  ///
  // clang-format on
  StatusOr<google::cloud::talent::v4::Company> CreateCompany(
      google::cloud::talent::v4::CreateCompanyRequest const& request,
      Options opts = {});

  // clang-format off
  ///
  /// Retrieves specified company.
  ///
  /// @param name  Required. The resource name of the company to be retrieved.
  ///  @n
  ///  The format is
  ///  "projects/{project_id}/tenants/{tenant_id}/companies/{company_id}", for
  ///  example, "projects/api-test-project/tenants/foo/companies/bar".
  /// @param opts Optional. Override the class-level options, such as retry and
  ///     backoff policies.
  /// @return the result of the RPC. The response message type
  ///     ([google.cloud.talent.v4.Company])
  ///     is mapped to a C++ class using the [Protobuf mapping rules].
  ///     If the request fails, the [`StatusOr`] contains the error details.
  ///
  /// [Protobuf mapping rules]: https://protobuf.dev/reference/cpp/cpp-generated/
  /// [input iterator requirements]: https://en.cppreference.com/w/cpp/named_req/InputIterator
  /// [`std::string`]: https://en.cppreference.com/w/cpp/string/basic_string
  /// [`future`]: @ref google::cloud::future
  /// [`StatusOr`]: @ref google::cloud::StatusOr
  /// [`Status`]: @ref google::cloud::Status
  /// [google.cloud.talent.v4.Company]: @googleapis_reference_link{google/cloud/talent/v4/company.proto#L32}
  /// [google.cloud.talent.v4.GetCompanyRequest]: @googleapis_reference_link{google/cloud/talent/v4/company_service.proto#L101}
  ///
  // clang-format on
  StatusOr<google::cloud::talent::v4::Company> GetCompany(
      std::string const& name, Options opts = {});

  // clang-format off
  ///
  /// Retrieves specified company.
  ///
  /// @param request Unary RPCs, such as the one wrapped by this
  ///     function, receive a single `request` proto message which includes all
  ///     the inputs for the RPC. In this case, the proto message is a
  ///     [google.cloud.talent.v4.GetCompanyRequest].
  ///     Proto messages are converted to C++ classes by Protobuf, using the
  ///     [Protobuf mapping rules].
  /// @param opts Optional. Override the class-level options, such as retry and
  ///     backoff policies.
  /// @return the result of the RPC. The response message type
  ///     ([google.cloud.talent.v4.Company])
  ///     is mapped to a C++ class using the [Protobuf mapping rules].
  ///     If the request fails, the [`StatusOr`] contains the error details.
  ///
  /// [Protobuf mapping rules]: https://protobuf.dev/reference/cpp/cpp-generated/
  /// [input iterator requirements]: https://en.cppreference.com/w/cpp/named_req/InputIterator
  /// [`std::string`]: https://en.cppreference.com/w/cpp/string/basic_string
  /// [`future`]: @ref google::cloud::future
  /// [`StatusOr`]: @ref google::cloud::StatusOr
  /// [`Status`]: @ref google::cloud::Status
  /// [google.cloud.talent.v4.Company]: @googleapis_reference_link{google/cloud/talent/v4/company.proto#L32}
  /// [google.cloud.talent.v4.GetCompanyRequest]: @googleapis_reference_link{google/cloud/talent/v4/company_service.proto#L101}
  ///
  // clang-format on
  StatusOr<google::cloud::talent::v4::Company> GetCompany(
      google::cloud::talent::v4::GetCompanyRequest const& request,
      Options opts = {});

  // clang-format off
  ///
  /// Updates specified company.
  ///
  /// @param company  Required. The company resource to replace the current resource in the
  ///  system.
  /// @param update_mask  Strongly recommended for the best service experience.
  ///  @n
  ///  If [update_mask][google.cloud.talent.v4.UpdateCompanyRequest.update_mask]
  ///  is provided, only the specified fields in
  ///  [company][google.cloud.talent.v4.UpdateCompanyRequest.company] are updated.
  ///  Otherwise all the fields are updated.
  ///  @n
  ///  A field mask to specify the company fields to be updated. Only
  ///  top level fields of [Company][google.cloud.talent.v4.Company] are
  ///  supported.
  /// @param opts Optional. Override the class-level options, such as retry and
  ///     backoff policies.
  /// @return the result of the RPC. The response message type
  ///     ([google.cloud.talent.v4.Company])
  ///     is mapped to a C++ class using the [Protobuf mapping rules].
  ///     If the request fails, the [`StatusOr`] contains the error details.
  ///
  /// [Protobuf mapping rules]: https://protobuf.dev/reference/cpp/cpp-generated/
  /// [input iterator requirements]: https://en.cppreference.com/w/cpp/named_req/InputIterator
  /// [`std::string`]: https://en.cppreference.com/w/cpp/string/basic_string
  /// [`future`]: @ref google::cloud::future
  /// [`StatusOr`]: @ref google::cloud::StatusOr
  /// [`Status`]: @ref google::cloud::Status
  /// [google.cloud.talent.v4.Company]: @googleapis_reference_link{google/cloud/talent/v4/company.proto#L32}
  /// [google.cloud.talent.v4.UpdateCompanyRequest]: @googleapis_reference_link{google/cloud/talent/v4/company_service.proto#L114}
  /// [google.cloud.talent.v4.UpdateCompanyRequest.company]: @googleapis_reference_link{google/cloud/talent/v4/company_service.proto#L117}
  /// [google.cloud.talent.v4.UpdateCompanyRequest.update_mask]: @googleapis_reference_link{google/cloud/talent/v4/company_service.proto#L129}
  ///
  // clang-format on
  StatusOr<google::cloud::talent::v4::Company> UpdateCompany(
      google::cloud::talent::v4::Company const& company,
      google::protobuf::FieldMask const& update_mask, Options opts = {});

  // clang-format off
  ///
  /// Updates specified company.
  ///
  /// @param request Unary RPCs, such as the one wrapped by this
  ///     function, receive a single `request` proto message which includes all
  ///     the inputs for the RPC. In this case, the proto message is a
  ///     [google.cloud.talent.v4.UpdateCompanyRequest].
  ///     Proto messages are converted to C++ classes by Protobuf, using the
  ///     [Protobuf mapping rules].
  /// @param opts Optional. Override the class-level options, such as retry and
  ///     backoff policies.
  /// @return the result of the RPC. The response message type
  ///     ([google.cloud.talent.v4.Company])
  ///     is mapped to a C++ class using the [Protobuf mapping rules].
  ///     If the request fails, the [`StatusOr`] contains the error details.
  ///
  /// [Protobuf mapping rules]: https://protobuf.dev/reference/cpp/cpp-generated/
  /// [input iterator requirements]: https://en.cppreference.com/w/cpp/named_req/InputIterator
  /// [`std::string`]: https://en.cppreference.com/w/cpp/string/basic_string
  /// [`future`]: @ref google::cloud::future
  /// [`StatusOr`]: @ref google::cloud::StatusOr
  /// [`Status`]: @ref google::cloud::Status
  /// [google.cloud.talent.v4.Company]: @googleapis_reference_link{google/cloud/talent/v4/company.proto#L32}
  /// [google.cloud.talent.v4.UpdateCompanyRequest]: @googleapis_reference_link{google/cloud/talent/v4/company_service.proto#L114}
  ///
  // clang-format on
  StatusOr<google::cloud::talent::v4::Company> UpdateCompany(
      google::cloud::talent::v4::UpdateCompanyRequest const& request,
      Options opts = {});

  // clang-format off
  ///
  /// Deletes specified company.
  /// Prerequisite: The company has no jobs associated with it.
  ///
  /// @param name  Required. The resource name of the company to be deleted.
  ///  @n
  ///  The format is
  ///  "projects/{project_id}/tenants/{tenant_id}/companies/{company_id}", for
  ///  example, "projects/foo/tenants/bar/companies/baz".
  /// @param opts Optional. Override the class-level options, such as retry and
  ///     backoff policies.
  /// @return a [`Status`] object. If the request failed, the
  ///     status contains the details of the failure.
  ///
  /// [Protobuf mapping rules]: https://protobuf.dev/reference/cpp/cpp-generated/
  /// [input iterator requirements]: https://en.cppreference.com/w/cpp/named_req/InputIterator
  /// [`std::string`]: https://en.cppreference.com/w/cpp/string/basic_string
  /// [`future`]: @ref google::cloud::future
  /// [`StatusOr`]: @ref google::cloud::StatusOr
  /// [`Status`]: @ref google::cloud::Status
  /// [google.cloud.talent.v4.DeleteCompanyRequest]: @googleapis_reference_link{google/cloud/talent/v4/company_service.proto#L133}
  ///
  // clang-format on
  Status DeleteCompany(std::string const& name, Options opts = {});

  // clang-format off
  ///
  /// Deletes specified company.
  /// Prerequisite: The company has no jobs associated with it.
  ///
  /// @param request Unary RPCs, such as the one wrapped by this
  ///     function, receive a single `request` proto message which includes all
  ///     the inputs for the RPC. In this case, the proto message is a
  ///     [google.cloud.talent.v4.DeleteCompanyRequest].
  ///     Proto messages are converted to C++ classes by Protobuf, using the
  ///     [Protobuf mapping rules].
  /// @param opts Optional. Override the class-level options, such as retry and
  ///     backoff policies.
  /// @return a [`Status`] object. If the request failed, the
  ///     status contains the details of the failure.
  ///
  /// [Protobuf mapping rules]: https://protobuf.dev/reference/cpp/cpp-generated/
  /// [input iterator requirements]: https://en.cppreference.com/w/cpp/named_req/InputIterator
  /// [`std::string`]: https://en.cppreference.com/w/cpp/string/basic_string
  /// [`future`]: @ref google::cloud::future
  /// [`StatusOr`]: @ref google::cloud::StatusOr
  /// [`Status`]: @ref google::cloud::Status
  /// [google.cloud.talent.v4.DeleteCompanyRequest]: @googleapis_reference_link{google/cloud/talent/v4/company_service.proto#L133}
  ///
  // clang-format on
  Status DeleteCompany(
      google::cloud::talent::v4::DeleteCompanyRequest const& request,
      Options opts = {});

  // clang-format off
  ///
  /// Lists all companies associated with the project.
  ///
  /// @param parent  Required. Resource name of the tenant under which the company is created.
  ///  @n
  ///  The format is "projects/{project_id}/tenants/{tenant_id}", for example,
  ///  "projects/foo/tenants/bar".
  /// @param opts Optional. Override the class-level options, such as retry and
  ///     backoff policies.
  /// @return a [StreamRange](@ref google::cloud::StreamRange)
  ///     to iterate of the results. See the documentation of this type for
  ///     details. In brief, this class has `begin()` and `end()` member
  ///     functions returning a iterator class meeting the
  ///     [input iterator requirements]. The value type for this iterator is a
  ///     [`StatusOr`] as the iteration may fail even after some values are
  ///     retrieved successfully, for example, if there is a network disconnect.
  ///     An empty set of results does not indicate an error, it indicates
  ///     that there are no resources meeting the request criteria.
  ///     On a successful iteration the `StatusOr<T>` contains elements of type
  ///     [google.cloud.talent.v4.Company], or rather,
  ///     the C++ class generated by Protobuf from that type. Please consult the
  ///     Protobuf documentation for details on the [Protobuf mapping rules].
  ///
  /// [Protobuf mapping rules]: https://protobuf.dev/reference/cpp/cpp-generated/
  /// [input iterator requirements]: https://en.cppreference.com/w/cpp/named_req/InputIterator
  /// [`std::string`]: https://en.cppreference.com/w/cpp/string/basic_string
  /// [`future`]: @ref google::cloud::future
  /// [`StatusOr`]: @ref google::cloud::StatusOr
  /// [`Status`]: @ref google::cloud::Status
  /// [google.cloud.talent.v4.Company]: @googleapis_reference_link{google/cloud/talent/v4/company.proto#L32}
  /// [google.cloud.talent.v4.ListCompaniesRequest]: @googleapis_reference_link{google/cloud/talent/v4/company_service.proto#L146}
  ///
  // clang-format on
  StreamRange<google::cloud::talent::v4::Company> ListCompanies(
      std::string const& parent, Options opts = {});

  // clang-format off
  ///
  /// Lists all companies associated with the project.
  ///
  /// @param request Unary RPCs, such as the one wrapped by this
  ///     function, receive a single `request` proto message which includes all
  ///     the inputs for the RPC. In this case, the proto message is a
  ///     [google.cloud.talent.v4.ListCompaniesRequest].
  ///     Proto messages are converted to C++ classes by Protobuf, using the
  ///     [Protobuf mapping rules].
  /// @param opts Optional. Override the class-level options, such as retry and
  ///     backoff policies.
  /// @return a [StreamRange](@ref google::cloud::StreamRange)
  ///     to iterate of the results. See the documentation of this type for
  ///     details. In brief, this class has `begin()` and `end()` member
  ///     functions returning a iterator class meeting the
  ///     [input iterator requirements]. The value type for this iterator is a
  ///     [`StatusOr`] as the iteration may fail even after some values are
  ///     retrieved successfully, for example, if there is a network disconnect.
  ///     An empty set of results does not indicate an error, it indicates
  ///     that there are no resources meeting the request criteria.
  ///     On a successful iteration the `StatusOr<T>` contains elements of type
  ///     [google.cloud.talent.v4.Company], or rather,
  ///     the C++ class generated by Protobuf from that type. Please consult the
  ///     Protobuf documentation for details on the [Protobuf mapping rules].
  ///
  /// [Protobuf mapping rules]: https://protobuf.dev/reference/cpp/cpp-generated/
  /// [input iterator requirements]: https://en.cppreference.com/w/cpp/named_req/InputIterator
  /// [`std::string`]: https://en.cppreference.com/w/cpp/string/basic_string
  /// [`future`]: @ref google::cloud::future
  /// [`StatusOr`]: @ref google::cloud::StatusOr
  /// [`Status`]: @ref google::cloud::Status
  /// [google.cloud.talent.v4.Company]: @googleapis_reference_link{google/cloud/talent/v4/company.proto#L32}
  /// [google.cloud.talent.v4.ListCompaniesRequest]: @googleapis_reference_link{google/cloud/talent/v4/company_service.proto#L146}
  ///
  // clang-format on
  StreamRange<google::cloud::talent::v4::Company> ListCompanies(
      google::cloud::talent::v4::ListCompaniesRequest request,
      Options opts = {});

  // clang-format off
  ///
  /// Gets the latest state of a long-running operation.  Clients can use this
  /// method to poll the operation result at intervals as recommended by the API
  /// service.
  ///
  /// @param name  The name of the operation resource.
  /// @param opts Optional. Override the class-level options, such as retry and
  ///     backoff policies.
  /// @return the result of the RPC. The response message type
  ///     ([google.longrunning.Operation])
  ///     is mapped to a C++ class using the [Protobuf mapping rules].
  ///     If the request fails, the [`StatusOr`] contains the error details.
  ///
  /// [Protobuf mapping rules]: https://protobuf.dev/reference/cpp/cpp-generated/
  /// [input iterator requirements]: https://en.cppreference.com/w/cpp/named_req/InputIterator
  /// [`std::string`]: https://en.cppreference.com/w/cpp/string/basic_string
  /// [`future`]: @ref google::cloud::future
  /// [`StatusOr`]: @ref google::cloud::StatusOr
  /// [`Status`]: @ref google::cloud::Status
  /// [google.longrunning.GetOperationRequest]: @googleapis_reference_link{google/longrunning/operations.proto#L160}
  /// [google.longrunning.Operation]: @googleapis_reference_link{google/longrunning/operations.proto#L121}
  ///
  // clang-format on
  StatusOr<google::longrunning::Operation> GetOperation(std::string const& name,
                                                        Options opts = {});

  // clang-format off
  ///
  /// Gets the latest state of a long-running operation.  Clients can use this
  /// method to poll the operation result at intervals as recommended by the API
  /// service.
  ///
  /// @param request Unary RPCs, such as the one wrapped by this
  ///     function, receive a single `request` proto message which includes all
  ///     the inputs for the RPC. In this case, the proto message is a
  ///     [google.longrunning.GetOperationRequest].
  ///     Proto messages are converted to C++ classes by Protobuf, using the
  ///     [Protobuf mapping rules].
  /// @param opts Optional. Override the class-level options, such as retry and
  ///     backoff policies.
  /// @return the result of the RPC. The response message type
  ///     ([google.longrunning.Operation])
  ///     is mapped to a C++ class using the [Protobuf mapping rules].
  ///     If the request fails, the [`StatusOr`] contains the error details.
  ///
  /// [Protobuf mapping rules]: https://protobuf.dev/reference/cpp/cpp-generated/
  /// [input iterator requirements]: https://en.cppreference.com/w/cpp/named_req/InputIterator
  /// [`std::string`]: https://en.cppreference.com/w/cpp/string/basic_string
  /// [`future`]: @ref google::cloud::future
  /// [`StatusOr`]: @ref google::cloud::StatusOr
  /// [`Status`]: @ref google::cloud::Status
  /// [google.longrunning.GetOperationRequest]: @googleapis_reference_link{google/longrunning/operations.proto#L160}
  /// [google.longrunning.Operation]: @googleapis_reference_link{google/longrunning/operations.proto#L121}
  ///
  // clang-format on
  StatusOr<google::longrunning::Operation> GetOperation(
      google::longrunning::GetOperationRequest const& request,
      Options opts = {});

 private:
  std::shared_ptr<CompanyServiceConnection> connection_;
  Options options_;
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace talent_v4
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_TALENT_V4_COMPANY_CLIENT_H
