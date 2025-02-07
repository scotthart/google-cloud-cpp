# ~~~
# Copyright 2021 Google LLC
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

include(GoogleCloudCppCommon)

if (bigquery IN_LIST GOOGLE_CLOUD_CPP_ENABLE)
    include(bigquery_grpc.cmake)
endif ()

if (experimental-bigquery_generated IN_LIST GOOGLE_CLOUD_CPP_ENABLE)
    include(bigquery_generated.cmake)

endif ()

if (experimental-bigquery_rest IN_LIST GOOGLE_CLOUD_CPP_ENABLE)
    include(bigquery_rest.cmake)
    add_subdirectory(v2/minimal/benchmarks)
endif ()

add_library(
    google_cloud_cpp_bigquery_enhanced # cmake-format: sort
    enhanced/v2/bigquery_enhanced.cc
    enhanced/v2/bigquery_enhanced.h
)

target_include_directories(
    google_cloud_cpp_bigquery_enhanced
    PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
           $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
           $<INSTALL_INTERFACE:include>)
target_link_libraries(
    google_cloud_cpp_bigquery_enhanced PUBLIC google-cloud-cpp::rest_internal
                                          google-cloud-cpp::common)
google_cloud_cpp_add_common_options(google_cloud_cpp_bigquery_enhanced)
set_target_properties(
    google_cloud_cpp_bigquery_enhanced
    PROPERTIES EXPORT_NAME google-cloud-cpp::experimental-bigquery_enhanced
               VERSION "${PROJECT_VERSION}"
               SOVERSION "${PROJECT_VERSION_MAJOR}")
target_compile_options(google_cloud_cpp_bigquery_enhanced
                       PUBLIC ${GOOGLE_CLOUD_CPP_EXCEPTIONS_FLAG})

add_library(google-cloud-cpp::experimental-bigquery_enhanced ALIAS
            google_cloud_cpp_bigquery_enhanced)

include(CreateBazelConfig)
create_bazel_config(google_cloud_cpp_bigquery_enhanced YEAR "2024")
