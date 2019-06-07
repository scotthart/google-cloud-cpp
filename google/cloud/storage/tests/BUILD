"""Integration tests for the Cloud Storage C++ client."""

load(
    ":storage_client_integration_tests.bzl",
    "storage_client_integration_tests",
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
        "//testing/base/public:gunit",
        "//third_party/cloud_cpp/google/cloud:google_cloud_cpp_common",
        "//third_party/cloud_cpp/google/cloud:google_cloud_cpp_testing",
        "//third_party/cloud_cpp/google/cloud/storage:storage_client",
        "//third_party/cloud_cpp/google/cloud/storage:storage_client_testing",
    ],
) for test in storage_client_integration_tests]
