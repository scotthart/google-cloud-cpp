# Copyright 2019 Google Inc.  All rights reserved
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

licenses(["notice"])  # Apache 2.0

cc_library(
    name = "generator",
    srcs = [
        "generator.cc",
        "internal/codegen_utils.cc",
        "internal/codegen_utils.h",
        "internal/connection_cc_generator.cc",
        "internal/connection_cc_generator.h",
        "internal/connection_header_generator.cc",
        "internal/connection_header_generator.h",
        "internal/data_model.h",
        "internal/logging_cc_generator.cc",
        "internal/logging_cc_generator.h",
        "internal/logging_header_generator.cc",
        "internal/logging_header_generator.h",
        "internal/metadata_cc_generator.cc",
        "internal/metadata_cc_generator.h",
        "internal/metadata_header_generator.cc",
        "internal/metadata_header_generator.h",
        "internal/printer.h",
        "internal/stub_cc_generator.cc",
        "internal/stub_cc_generator.h",
        "internal/stub_header_generator.cc",
        "internal/stub_header_generator.h",
        "standalone.cc",
        "standalone.h",
    ],
    hdrs = [
        "generator.h",
    ],
    includes = ["."],
    deps = [
        "@com_github_abseil_abseil_cpp//absl/base",
        "@com_github_abseil_abseil_cpp//absl/strings",
        "@com_google_googleapis//google/api:client_cc_proto",
        "@com_google_protobuf//:protoc_lib",
    ],
)

# The protoc plugin/standalone binary. The name (proto-gen-cpp_codegen) is ugly
# but it is a naming requirement for protoc plugins. To use --cpp_codegen_out
# command line argument without need to provide additional --plugin argument,
# the binary must be named proto-gen-cpp_codegen and placed in a PATH.
cc_binary(
    name = "protoc-gen-cpp_codegen",
    srcs = ["main.cc"],
    includes = ["."],
    visibility = ["//visibility:public"],
    deps = [":generator"],
)

cc_test(
    name = "generator_test",
    size = "small",
    srcs = ["generator_test.cc"],
    data = [
        "//generator/testdata:library_proto",
        #        "//generator/testdata:library_service_baseline",
        "@com_google_googleapis//google/api:client_proto",
        "@com_google_protobuf//:descriptor_proto",
    ],
    deps = [
        ":generator",
        "//generator/testdata:library_cc_codegen",
        "@com_google_googletest//:gtest_main",
    ],
)

[cc_test(
    name = "generator_" + test.replace("/", "_").replace(".cc", ""),
    size = "small",
    srcs = [test],
    deps = [
        "//generator",
        "@com_github_abseil_abseil_cpp//absl/base",
        "@com_github_abseil_abseil_cpp//absl/strings",
        "@com_google_googletest//:gtest_main",
    ],
) for test in [
    "internal/codegen_utils_test.cc",
]]
