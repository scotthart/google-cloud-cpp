# ~~~
# Copyright 2024 Google LLC
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

# Defines a bigquery service library and installs the headers.
function (bigquery_service_library dir library)
    cmake_parse_arguments(_opt "" "" "DEPS" ${ARGN})
    file(
        GLOB service_source_files
        LIST_DIRECTORIES false
        RELATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}" "${dir}*.h" "${dir}*.cc"
        "${dir}internal/*")
    list(SORT service_source_files)

    add_library(${library} ${service_source_files})
    set_target_properties(${library} PROPERTIES OUTPUT_NAME
                                                "google_cloud_cpp_${library}")
    target_include_directories(
        ${library}
        PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
               $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
               $<INSTALL_INTERFACE:include>)

    target_link_libraries(${library} PUBLIC ${_opt_DEPS})

    google_cloud_cpp_add_common_options(${library})
    set_target_properties(
        ${library}
        PROPERTIES EXPORT_NAME google-cloud-cpp::${library}
                   VERSION "${PROJECT_VERSION}"
                   SOVERSION "${PROJECT_VERSION_MAJOR}")
    target_compile_options(${library}
                           PUBLIC ${GOOGLE_CLOUD_CPP_EXCEPTIONS_FLAG})
    google_cloud_cpp_install_headers(${library} "include/google/cloud/bigquery")

    add_library(google-cloud-cpp::${library} ALIAS ${library})
endfunction ()

include(GoogleapisConfig)
include(CreateBazelConfig)
include(${CMAKE_CURRENT_SOURCE_DIR}/service_dirs.cmake)
export_list_to_bazel("service_dirs.bzl" YEAR 2024 service_dirs
                     operation_service_dirs)

include(GoogleCloudCppCommon)

set(DOXYGEN_PROJECT_NAME "Cloud BigQuery API C++ Client")
set(DOXYGEN_PROJECT_BRIEF "A C++ Client Library for the Cloud BigQuery API")
set(DOXYGEN_PROJECT_NUMBER "${PROJECT_VERSION} (Experimental)")
set(DOXYGEN_EXCLUDE_SYMBOLS "internal")
foreach (dir IN LISTS service_dirs operation_service_dirs)
    list(APPEND DOXYGEN_EXAMPLE_PATH
         "${CMAKE_CURRENT_SOURCE_DIR}/${dir}samples")
endforeach ()
list(APPEND DOXYGEN_EXAMPLE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/samples"
     "${CMAKE_CURRENT_SOURCE_DIR}/quickstart")
include(GoogleCloudCppDoxygen)

foreach (dir IN LISTS service_dirs operation_service_dirs)
    string(REPLACE "/v2/" "" short_dir "${dir}")
    list(APPEND bigquery_proto_lib_targets "bigquery_${short_dir}_protos")
endforeach ()

set(GOOGLE_CLOUD_CPP_DOXYGEN_EXTRA_INCLUDES
    "${PROJECT_BINARY_DIR}/protos/google/cloud/bigquery")
google_cloud_cpp_doxygen_targets("bigquery" THREADED DEPENDS cloud-docs
                                 ${bigquery_proto_lib_targets})

foreach (dir IN LISTS operation_service_dirs)
    string(REPLACE "/v2/" "" short_dir "${dir}")
    bigquery_service_library(
        ${dir} bigquery_${short_dir} DEPS
        google-cloud-cpp::rest_protobuf_internal
        google-cloud-cpp::bigquery_${short_dir}_protos)
    list(APPEND bigquery_operation_lib_targets "bigquery_${short_dir}")
endforeach ()

foreach (dir IN LISTS service_dirs)
    string(REPLACE "/v2/" "" short_dir "${dir}")
    bigquery_service_library(
        ${dir}
        bigquery_${short_dir}
        DEPS
        google-cloud-cpp::bigquery_${short_dir}_protos)
    list(APPEND bigquery_lib_targets "bigquery_${short_dir}")
endforeach ()

add_library(google_cloud_cpp_bigquery_generated INTERFACE)
target_link_libraries(
    google_cloud_cpp_bigquery_generated
    PUBLIC
    INTERFACE ${bigquery_lib_targets})
set_target_properties(google_cloud_cpp_bigquery_generated
                      PROPERTIES EXPORT_NAME "google-cloud-cpp::bigquery_generated")
add_library(google-cloud-cpp::bigquery_generated ALIAS google_cloud_cpp_bigquery_generated)

# Create a header-only library for the mocks. We use a CMake `INTERFACE` library
# for these, a regular library would not work on macOS (where the library needs
# at least one .o file). Unfortunately INTERFACE libraries are a bit weird in
# that they need absolute paths for their sources.
foreach (dir IN LISTS service_dirs operation_service_dirs)
    string(REPLACE "/v2/" "" short_dir "${dir}")
    file(
        GLOB ${short_dir}_relative_mock_files
        LIST_DIRECTORIES false
        RELATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}" "${dir}mocks/*.h")
    list(SORT ${short_dir}_relative_mock_files)
    set(mock_files)
    foreach (file IN LISTS ${short_dir}_relative_mock_files)
        list(APPEND mock_files "${file}")
    endforeach ()
    add_library(google_cloud_cpp_bigquery_${short_dir}_mocks INTERFACE)
    target_sources(google_cloud_cpp_bigquery_${short_dir}_mocks
                   INTERFACE ${mock_files})
    target_link_libraries(
        google_cloud_cpp_bigquery_${short_dir}_mocks
        INTERFACE google-cloud-cpp::bigquery-${short_dir} GTest::gmock_main
                  GTest::gmock GTest::gtest)
    set_target_properties(
        google_cloud_cpp_bigquery_${short_dir}_mocks
        PROPERTIES EXPORT_NAME google-cloud-cpp::bigquery-${short_dir}_mocks)
    target_include_directories(
        google_cloud_cpp_bigquery_${short_dir}_mocks
        INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
                  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
                  $<INSTALL_INTERFACE:include>)
    target_compile_options(google_cloud_cpp_bigquery_${short_dir}_mocks
                           INTERFACE ${GOOGLE_CLOUD_CPP_EXCEPTIONS_FLAG})
    google_cloud_cpp_install_headers(
        "google_cloud_cpp_bigquery_${short_dir}_mocks"
        "include/google/cloud/bigquery")
endforeach ()

#if (BUILD_TESTING AND GOOGLE_CLOUD_CPP_ENABLE_CXX_EXCEPTIONS)
#    add_executable(bigquery_quickstart "quickstart/quickstart.cc")
#    target_link_libraries(bigquery_quickstart
#                          PRIVATE google-cloud-cpp::bigquery_disks)
#    google_cloud_cpp_add_common_options(bigquery_quickstart)
#    add_test(
#        NAME bigquery_quickstart
#        COMMAND
#            cmake -P "${PROJECT_SOURCE_DIR}/cmake/quickstart-runner.cmake"
#            $<TARGET_FILE:bigquery_quickstart> GOOGLE_CLOUD_PROJECT
#            GOOGLE_CLOUD_CPP_TEST_ZONE)
#    set_tests_properties(bigquery_quickstart
#                         PROPERTIES LABELS "integration-test;quickstart")
#    add_subdirectory(integration_tests)
#endif ()

# Get the destination directories based on the GNU recommendations.
include(GNUInstallDirs)

# Export the CMake targets to make it easy to create configuration files.
install(
    EXPORT google_cloud_cpp_bigquery_generated-targets
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/google_cloud_cpp_bigquery_generated"
    COMPONENT google_cloud_cpp_development)

# Install the libraries and headers in the locations determined by
# GNUInstallDirs
install(
    TARGETS google_cloud_cpp_bigquery_generated ${bigquery_lib_targets}
            ${bigquery_operation_lib_targets}
    EXPORT google_cloud_cpp_bigquery_generated-targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            COMPONENT google_cloud_cpp_runtime
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT google_cloud_cpp_runtime
            NAMELINK_COMPONENT google_cloud_cpp_development
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT google_cloud_cpp_development)

# Create and install the CMake configuration files.
include(CMakePackageConfigHelpers)
configure_file("config.cmake.in" "google_cloud_cpp_bigquery_generated-config.cmake" @ONLY)
write_basic_package_version_file(
    "google_cloud_cpp_bigquery_generated-config-version.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY ExactVersion)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/google_cloud_cpp_bigquery_generated-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/google_cloud_cpp_bigquery_generated-config-version.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/google_cloud_cpp_bigquery_generated"
    COMPONENT google_cloud_cpp_development)

foreach (dir IN LISTS operation_service_dirs)
    string(REPLACE "/v2/" "" short_dir "${dir}")
    google_cloud_cpp_add_pkgconfig(
        "bigquery_${short_dir}"
        "The Cloud BigQuery API C++ Client Library"
        "Provides C++ APIs to use the Cloud BigQuery API."
        WITH_SHORT_TARGET
        "google_cloud_cpp_rest_internal"
        "google_cloud_cpp_rest_protobuf_internal"
        "google_cloud_cpp_grpc_utils"
        "google_cloud_cpp_common"
        "google_cloud_cpp_bigquery_${short_dir}_protos")
endforeach ()

foreach (dir IN LISTS service_dirs)
    string(REPLACE "/v2/" "" short_dir "${dir}")
    google_cloud_cpp_add_pkgconfig(
        "bigquery_${short_dir}"
        "The Cloud BigQuery API C++ Client Library"
        "Provides C++ APIs to use the Cloud BigQuery API."
        WITH_SHORT_TARGET
        "google_cloud_cpp_bigquery_global_operations"
        "google_cloud_cpp_bigquery_global_organization_operations"
        "google_cloud_cpp_bigquery_region_operations"
        "google_cloud_cpp_bigquery_zone_operations"
        "google_cloud_cpp_bigquery_${short_dir}_protos")
endforeach ()

set(bigquery_pc_modules ${bigquery_lib_targets})
list(TRANSFORM bigquery_pc_modules PREPEND "google_cloud_cpp_")
google_cloud_cpp_add_pkgconfig(
    "bigquery" "The Cloud BigQuery API C++ Client Library"
    "Provides C++ APIs to use the Cloud BigQuery API." ${bigquery_pc_modules})
