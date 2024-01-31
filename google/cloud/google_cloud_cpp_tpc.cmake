# ~~~
# Copyright 2023 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ~~~

# find_package(OpenSSL REQUIRED)

# the client library
add_library(google_cloud_cpp_tpc # cmake-format: sort
            internal/service_endpoint_tpc.cc tpc_options.cc tpc_options.h)
target_link_libraries(
    google_cloud_cpp_tpc PUBLIC google-cloud-cpp::common
                                google-cloud-cpp::rest_internal absl::optional)

google_cloud_cpp_add_common_options(google_cloud_cpp_tpc)
target_include_directories(
    google_cloud_cpp_tpc PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
                                $<INSTALL_INTERFACE:include>)

# We're putting generated code into ${PROJECT_BINARY_DIR} (e.g. compiled
# protobufs or build info), so we need it on the include path, however we don't
# want it checked by linters so we mark it as SYSTEM.
target_include_directories(google_cloud_cpp_tpc SYSTEM
                           PUBLIC $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>)
target_compile_options(google_cloud_cpp_tpc
                       PUBLIC ${GOOGLE_CLOUD_CPP_EXCEPTIONS_FLAG})

set_target_properties(
    google_cloud_cpp_tpc
    PROPERTIES EXPORT_NAME "google-cloud-cpp::tpc"
               VERSION ${PROJECT_VERSION}
               SOVERSION ${PROJECT_VERSION_MAJOR})
add_library(google-cloud-cpp::tpc ALIAS google_cloud_cpp_tpc)

create_bazel_config(google_cloud_cpp_tpc YEAR 2023)

# Export the CMake targets to make it easy to create configuration files.
install(
    EXPORT google_cloud_cpp_tpc-targets
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/google_cloud_cpp_tpc"
    COMPONENT google_cloud_cpp_development)

# Install the libraries and headers in the locations determined by
# GNUInstallDirs
install(
    TARGETS google_cloud_cpp_tpc
    EXPORT google_cloud_cpp_tpc-targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            COMPONENT google_cloud_cpp_runtime
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT google_cloud_cpp_runtime
            NAMELINK_COMPONENT google_cloud_cpp_development
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT google_cloud_cpp_development)

google_cloud_cpp_install_headers(google_cloud_cpp_tpc include/google/cloud)

google_cloud_cpp_add_pkgconfig(
    "tpc" "Google Cloud C++ Client Library Trusted Partner Cloud Support"
    "TPC Components used by the Google Cloud C++ Client Libraries."
    "absl_optional")

# Create and install the CMake configuration files.
configure_file("config.cmake.in" "google_cloud_cpp_tpc-config.cmake" @ONLY)
write_basic_package_version_file(
    "google_cloud_cpp_tpc-config-version.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY ExactVersion)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/google_cloud_cpp_tpc-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/google_cloud_cpp_tpc-config-version.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/google_cloud_cpp_tpc"
    COMPONENT google_cloud_cpp_development)

# if (BUILD_TESTING AND GOOGLE_CLOUD_CPP_ENABLE_CXX_EXCEPTIONS)
# google_cloud_cpp_add_samples_relative("common" "samples/") endif ()
