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
// source: google/cloud/compute/network_profiles/v1/network_profiles.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_COMPUTE_NETWORK_PROFILES_V1_NETWORK_PROFILES_CLIENT_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_COMPUTE_NETWORK_PROFILES_V1_NETWORK_PROFILES_CLIENT_H

#include "google/cloud/compute/network_profiles/v1/network_profiles_rest_connection.h"
#include "google/cloud/future.h"
#include "google/cloud/options.h"
#include "google/cloud/polling_policy.h"
#include "google/cloud/status_or.h"
#include "google/cloud/version.h"
#include <memory>
#include <string>

namespace google {
namespace cloud {
namespace compute_network_profiles_v1 {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

///
/// Service for the networkProfiles resource.
/// https://cloud.google.com/compute/docs/reference/rest/v1/networkProfiles
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
class NetworkProfilesClient {
 public:
  explicit NetworkProfilesClient(
      std::shared_ptr<NetworkProfilesConnection> connection, Options opts = {});
  ~NetworkProfilesClient();

  ///@{
  /// @name Copy and move support
  NetworkProfilesClient(NetworkProfilesClient const&) = default;
  NetworkProfilesClient& operator=(NetworkProfilesClient const&) = default;
  NetworkProfilesClient(NetworkProfilesClient&&) = default;
  NetworkProfilesClient& operator=(NetworkProfilesClient&&) = default;
  ///@}

  ///@{
  /// @name Equality
  friend bool operator==(NetworkProfilesClient const& a,
                         NetworkProfilesClient const& b) {
    return a.connection_ == b.connection_;
  }
  friend bool operator!=(NetworkProfilesClient const& a,
                         NetworkProfilesClient const& b) {
    return !(a == b);
  }
  ///@}

  // clang-format off
  ///
  /// Returns the specified network profile.
  /// https://cloud.google.com/compute/docs/reference/rest/v1/networkProfiles/get
  ///
  /// @param project  Project ID for this request.
  /// @param network_profile  Name of the network profile to return.
  /// @param opts Optional. Override the class-level options, such as retry and
  ///     backoff policies.
  /// @return the result of the RPC. The response message type
  ///     ([google.cloud.cpp.compute.v1.NetworkProfile])
  ///     is mapped to a C++ class using the [Protobuf mapping rules].
  ///     If the request fails, the [`StatusOr`] contains the error details.
  ///
  /// [Protobuf mapping rules]: https://protobuf.dev/reference/cpp/cpp-generated/
  /// [input iterator requirements]: https://en.cppreference.com/w/cpp/named_req/InputIterator
  /// [`std::string`]: https://en.cppreference.com/w/cpp/string/basic_string
  /// [`future`]: @ref google::cloud::future
  /// [`StatusOr`]: @ref google::cloud::StatusOr
  /// [`Status`]: @ref google::cloud::Status
  /// [google.cloud.cpp.compute.network_profiles.v1.GetNetworkProfileRequest]: @cloud_cpp_reference_link{google/cloud/compute/network_profiles/v1/network_profiles.proto#L60}
  /// [google.cloud.cpp.compute.v1.NetworkProfile]: @cloud_cpp_reference_link{google/cloud/compute/v1/internal/common_087.proto#L25}
  ///
  // clang-format on
  StatusOr<google::cloud::cpp::compute::v1::NetworkProfile> GetNetworkProfile(
      std::string const& project, std::string const& network_profile,
      Options opts = {});

  // clang-format off
  ///
  /// Returns the specified network profile.
  /// https://cloud.google.com/compute/docs/reference/rest/v1/networkProfiles/get
  ///
  /// @param request Unary RPCs, such as the one wrapped by this
  ///     function, receive a single `request` proto message which includes all
  ///     the inputs for the RPC. In this case, the proto message is a
  ///     [google.cloud.cpp.compute.network_profiles.v1.GetNetworkProfileRequest].
  ///     Proto messages are converted to C++ classes by Protobuf, using the
  ///     [Protobuf mapping rules].
  /// @param opts Optional. Override the class-level options, such as retry and
  ///     backoff policies.
  /// @return the result of the RPC. The response message type
  ///     ([google.cloud.cpp.compute.v1.NetworkProfile])
  ///     is mapped to a C++ class using the [Protobuf mapping rules].
  ///     If the request fails, the [`StatusOr`] contains the error details.
  ///
  /// [Protobuf mapping rules]: https://protobuf.dev/reference/cpp/cpp-generated/
  /// [input iterator requirements]: https://en.cppreference.com/w/cpp/named_req/InputIterator
  /// [`std::string`]: https://en.cppreference.com/w/cpp/string/basic_string
  /// [`future`]: @ref google::cloud::future
  /// [`StatusOr`]: @ref google::cloud::StatusOr
  /// [`Status`]: @ref google::cloud::Status
  /// [google.cloud.cpp.compute.network_profiles.v1.GetNetworkProfileRequest]: @cloud_cpp_reference_link{google/cloud/compute/network_profiles/v1/network_profiles.proto#L60}
  /// [google.cloud.cpp.compute.v1.NetworkProfile]: @cloud_cpp_reference_link{google/cloud/compute/v1/internal/common_087.proto#L25}
  ///
  // clang-format on
  StatusOr<google::cloud::cpp::compute::v1::NetworkProfile> GetNetworkProfile(
      google::cloud::cpp::compute::network_profiles::v1::
          GetNetworkProfileRequest const& request,
      Options opts = {});

  // clang-format off
  ///
  /// Retrieves a list of network profiles available to the specified project.
  /// https://cloud.google.com/compute/docs/reference/rest/v1/networkProfiles/list
  ///
  /// @param project  Project ID for this request.
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
  ///     [google.cloud.cpp.compute.v1.NetworkProfile], or rather,
  ///     the C++ class generated by Protobuf from that type. Please consult the
  ///     Protobuf documentation for details on the [Protobuf mapping rules].
  ///
  /// [Protobuf mapping rules]: https://protobuf.dev/reference/cpp/cpp-generated/
  /// [input iterator requirements]: https://en.cppreference.com/w/cpp/named_req/InputIterator
  /// [`std::string`]: https://en.cppreference.com/w/cpp/string/basic_string
  /// [`future`]: @ref google::cloud::future
  /// [`StatusOr`]: @ref google::cloud::StatusOr
  /// [`Status`]: @ref google::cloud::Status
  /// [google.cloud.cpp.compute.network_profiles.v1.ListNetworkProfilesRequest]: @cloud_cpp_reference_link{google/cloud/compute/network_profiles/v1/network_profiles.proto#L71}
  /// [google.cloud.cpp.compute.v1.NetworkProfile]: @cloud_cpp_reference_link{google/cloud/compute/v1/internal/common_087.proto#L25}
  ///
  // clang-format on
  StreamRange<google::cloud::cpp::compute::v1::NetworkProfile>
  ListNetworkProfiles(std::string const& project, Options opts = {});

  // clang-format off
  ///
  /// Retrieves a list of network profiles available to the specified project.
  /// https://cloud.google.com/compute/docs/reference/rest/v1/networkProfiles/list
  ///
  /// @param request Unary RPCs, such as the one wrapped by this
  ///     function, receive a single `request` proto message which includes all
  ///     the inputs for the RPC. In this case, the proto message is a
  ///     [google.cloud.cpp.compute.network_profiles.v1.ListNetworkProfilesRequest].
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
  ///     [google.cloud.cpp.compute.v1.NetworkProfile], or rather,
  ///     the C++ class generated by Protobuf from that type. Please consult the
  ///     Protobuf documentation for details on the [Protobuf mapping rules].
  ///
  /// [Protobuf mapping rules]: https://protobuf.dev/reference/cpp/cpp-generated/
  /// [input iterator requirements]: https://en.cppreference.com/w/cpp/named_req/InputIterator
  /// [`std::string`]: https://en.cppreference.com/w/cpp/string/basic_string
  /// [`future`]: @ref google::cloud::future
  /// [`StatusOr`]: @ref google::cloud::StatusOr
  /// [`Status`]: @ref google::cloud::Status
  /// [google.cloud.cpp.compute.network_profiles.v1.ListNetworkProfilesRequest]: @cloud_cpp_reference_link{google/cloud/compute/network_profiles/v1/network_profiles.proto#L71}
  /// [google.cloud.cpp.compute.v1.NetworkProfile]: @cloud_cpp_reference_link{google/cloud/compute/v1/internal/common_087.proto#L25}
  ///
  // clang-format on
  StreamRange<google::cloud::cpp::compute::v1::NetworkProfile>
  ListNetworkProfiles(google::cloud::cpp::compute::network_profiles::v1::
                          ListNetworkProfilesRequest request,
                      Options opts = {});

 private:
  std::shared_ptr<NetworkProfilesConnection> connection_;
  Options options_;
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace compute_network_profiles_v1
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_COMPUTE_NETWORK_PROFILES_V1_NETWORK_PROFILES_CLIENT_H
