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

include(GoogleCloudCppLibrary)

google_cloud_cpp_add_gapic_library(
    managedkafka "Managed Service for Apache Kafka API"
    SERVICE_DIRS "v1/" "schemaregistry/v1/")

if (BUILD_TESTING AND GOOGLE_CLOUD_CPP_ENABLE_CXX_EXCEPTIONS)
    add_executable(managedkafka_quickstart "quickstart/quickstart.cc")
    target_link_libraries(managedkafka_quickstart
                          PRIVATE google-cloud-cpp::managedkafka)
    google_cloud_cpp_add_common_options(managedkafka_quickstart)
    add_test(
        NAME managedkafka_quickstart
        COMMAND
            cmake -P "${PROJECT_SOURCE_DIR}/cmake/quickstart-runner.cmake"
            $<TARGET_FILE:managedkafka_quickstart> GOOGLE_CLOUD_PROJECT
            GOOGLE_CLOUD_CPP_TEST_REGION)
    set_tests_properties(managedkafka_quickstart
                         PROPERTIES LABELS "integration-test;quickstart")
endif ()
