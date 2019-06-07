"""Integration tests for the Cloud Bigtable C++ client."""

load(
    ":bigtable_client_integration_tests.bzl",
    "bigtable_client_integration_tests",
)

package(default_visibility = ["//visibility:public"])

licenses(["notice"])  # Apache 2.0

[cc_test(
    name = test.replace("/", "_").replace(".cc", ""),
    srcs = [test],
    copts = [
        "-I$(GENDIR)",
        "-Wno-google3-literal-operator",
        "-Wno-google3-inline-namespace",
    ],
    # These are interation tests, they cannot be executed in the sandbox.
    tags = [
        "manual",
        "needs_credentials",
    ],
    deps = [
        "//google/bigtable/admin/v2:bigtable_instance_admin_proto",
        "//google/bigtable/admin/v2:bigtable_table_admin_proto",
        "//google/bigtable/v2:bigtable_proto",
        "//google/bigtable/v2:data_proto",
        "//google/rpc:error_details",
        "//net/grpc:grpc++",
        "//net/proto2/public:proto2",
        "//net/proto2/util/public:differencer",
        "//testing/base/public:gunit",
        "//third_party/cloud_cpp/google/cloud:google_cloud_cpp_common",
        "//third_party/cloud_cpp/google/cloud:google_cloud_cpp_testing",
        "//third_party/cloud_cpp/google/cloud/bigtable:bigtable_client",
        "//third_party/cloud_cpp/google/cloud/bigtable:bigtable_client_testing",
    ],
) for test in bigtable_client_integration_tests]

cc_binary(
    name = "instance_admin_emulator",
    srcs = ["instance_admin_emulator.cc"],
    copts = [
        "-I$(GENDIR)",
        "-Wno-google3-literal-operator",
        "-Wno-google3-inline-namespace",
    ],
    deps = [
        "//google/bigtable/admin/v2:bigtable_instance_admin_proto",
        "//google/bigtable/admin/v2:bigtable_table_admin_proto",
        "//google/bigtable/v2:bigtable_proto",
        "//google/bigtable/v2:data_proto",
        "//google/longrunning:operations_cc_grpc_proto",
        "//google/rpc:error_details",
        "//net/grpc:grpc++",
        "//net/proto2/public:proto2",
        "//net/proto2/util/public:differencer",
        "//third_party/cloud_cpp/google/cloud:google_cloud_cpp_common",
        "//third_party/cloud_cpp/google/cloud/bigtable:bigtable_client",
    ],
)
