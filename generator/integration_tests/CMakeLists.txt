# ~~~
# Copyright 2020 Google LLC
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

# Only define the tests if testing is enabled. Package maintainers may not want
# to build all the tests everytime they create a new package or when the package
# is installed from source.
if (NOT BUILD_TESTING)
    return()
endif ()

include(CompileProtos)
google_cloud_cpp_find_proto_include_dir(PROTO_INCLUDE_DIR)

google_cloud_cpp_grpcpp_library(
    google_cloud_cpp_generator_golden_protos
    ${PROJECT_SOURCE_DIR}/generator/integration_tests/backup.proto
    ${PROJECT_SOURCE_DIR}/generator/integration_tests/common.proto
    ${PROJECT_SOURCE_DIR}/generator/integration_tests/test.proto
    ${PROJECT_SOURCE_DIR}/generator/integration_tests/test2.proto
    ${PROJECT_SOURCE_DIR}/generator/integration_tests/test_request_id.proto
    ${PROJECT_SOURCE_DIR}/generator/integration_tests/test_deprecated.proto
    PROTO_PATH_DIRECTORIES
    ${PROTO_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}/external/googleapis/src/googleapis_download)
target_link_libraries(
    google_cloud_cpp_generator_golden_protos
    PUBLIC google-cloud-cpp::api_annotations_protos
           google-cloud-cpp::api_client_protos
           google-cloud-cpp::api_field_behavior_protos
           google-cloud-cpp::api_field_info_protos
           google-cloud-cpp::api_resource_protos
           google-cloud-cpp::api_routing_protos
           google-cloud-cpp::iam_v1_iam_policy_protos
           google-cloud-cpp::iam_v1_policy_protos
           google-cloud-cpp::longrunning_operations_protos
           google-cloud-cpp::rpc_status_protos)
set_target_properties(google_cloud_cpp_generator_golden_protos
                      PROPERTIES CXX_CLANG_TIDY "")

file(
    GLOB google_cloud_cpp_generator_golden_files
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "golden/*.h"
    "golden/mocks/*.h"
    "golden/v1/*.h"
    "golden/v1/internal/*.h"
    "golden/v1/internal/*_sources.cc"
    "golden/v1/internal/streaming.cc"
    "golden/v1/mocks/*.h")
list(SORT google_cloud_cpp_generator_golden_files)

# Create a library from the where the golden code was copied to.
add_library(google_cloud_cpp_generator_golden # cmake-format: sort
            ${google_cloud_cpp_generator_golden_files})

target_include_directories(
    google_cloud_cpp_generator_golden
    PUBLIC ${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR}
           ${PROJECT_BINARY_DIR}/generator/integration_tests)
target_link_libraries(
    google_cloud_cpp_generator_golden
    PUBLIC google_cloud_cpp_generator_golden_protos
           google-cloud-cpp::rest_protobuf_internal
           google-cloud-cpp::rest_internal
           google-cloud-cpp::grpc_utils
           google-cloud-cpp::common
           google-cloud-cpp::api_client_protos
           google-cloud-cpp::longrunning_operations_protos
           absl::str_format
           protobuf::libprotoc)
google_cloud_cpp_add_common_options(google_cloud_cpp_generator_golden)
target_compile_options(google_cloud_cpp_generator_golden
                       PUBLIC ${GOOGLE_CLOUD_CPP_EXCEPTIONS_FLAG})

# The tests require googletest to be installed. Force CMake to use the config
# file for googletest (that is, the CMake file installed by googletest itself),
# because the generic `FindGTest` module does not define the GTest::gmock
# target, and the target names are also weird.
find_package(GTest CONFIG REQUIRED)

add_library(
    google_cloud_cpp_generator_golden_testing # cmake-format: sort
    tests/mock_golden_kitchen_sink_stub.h tests/mock_golden_thing_admin_stub.h
    tests/mock_request_id_stub.h)
target_link_libraries(
    google_cloud_cpp_generator_golden_testing
    PUBLIC google_cloud_cpp_testing google_cloud_cpp_mocks
           google_cloud_cpp_generator_golden GTest::gmock_main GTest::gmock
           GTest::gtest)

file(
    GLOB tests_cc
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "tests/*.cc")
foreach (fname ${tests_cc})
    google_cloud_cpp_add_executable(target "generator_golden" "${fname}")
    target_link_libraries(
        ${target}
        PRIVATE google_cloud_cpp_generator_golden_testing
                google_cloud_cpp_generator_golden
                google_cloud_cpp_testing
                google_cloud_cpp_testing_grpc
                GTest::gmock_main
                GTest::gmock
                GTest::gtest
                protobuf::libprotoc)
    google_cloud_cpp_add_common_options(${target})
    add_test(NAME ${target} COMMAND ${target})
endforeach ()

file(
    GLOB samples_cc
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "golden/v1/samples/*.cc")
foreach (fname IN LISTS samples_cc)
    google_cloud_cpp_add_executable(target "generator" "${fname}")
    target_link_libraries(
        ${target}
        PRIVATE google_cloud_cpp_generator_golden_testing
                google_cloud_cpp_generator_golden google_cloud_cpp_testing
                google_cloud_cpp_testing_grpc)
    google_cloud_cpp_add_common_options(${target})
    add_test(NAME ${target} COMMAND ${target})
    set_tests_properties("${target}" PROPERTIES LABELS "integration-test")
endforeach ()

include(FindBenchmarkWithWorkarounds)
file(
    GLOB benchmarks_cc
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "benchmarks/*.cc")
foreach (fname IN LISTS benchmarks_cc)
    google_cloud_cpp_add_executable(target "generator" "${fname}")
    add_test(NAME ${target} COMMAND ${target})
    target_link_libraries(${target} PRIVATE google_cloud_cpp_generator_golden
                                            benchmark::benchmark_main)
    google_cloud_cpp_add_common_options(${target})
endforeach ()
