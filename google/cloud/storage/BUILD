load(
    ":storage_client.bzl",
    "storage_client_srcs",
    "storage_client_hdrs",
)
load(
    ":storage_client_testing.bzl",
    "storage_client_testing_srcs",
    "storage_client_testing_hdrs",
)
load(
    ":storage_client_unit_tests.bzl",
    "storage_client_unit_tests",
)
load(
    ":storage_client_version.bzl",
    "STORAGE_CLIENT_VERSION_MAJOR",
    "STORAGE_CLIENT_VERSION_MINOR",
    "STORAGE_CLIENT_VERSION_PATCH",
)

package(default_visibility = ["//visibility:public"])

licenses(["notice"])  # Apache 2.0

genrule(
    name = "generate_version_info",
    srcs = ["version_info.h.in"],
    outs = ["version_info.h"],
    cmd = """
sed -e 's/@STORAGE_CLIENT_VERSION_MAJOR@/%s/' \
    -e 's/@STORAGE_CLIENT_VERSION_MINOR@/%s/' \
    -e 's/@STORAGE_CLIENT_VERSION_PATCH@/%s/' < $< > $@
""" % (
        STORAGE_CLIENT_VERSION_MAJOR,
        STORAGE_CLIENT_VERSION_MINOR,
        STORAGE_CLIENT_VERSION_PATCH,
    ),
    compatible_with = ["//buildenv/target:gce"],
)

cc_library(
    name = "storage_client",
    srcs = storage_client_srcs,
    hdrs = storage_client_hdrs + ["version_info.h"],
    compatible_with = ["//buildenv/target:gce"],
    copts = [
        "-Wno-google3-literal-operator",
        "-Wno-google3-inline-namespace",
    ],
    includes = ["."],
    deps = [
        "//third_party/absl/strings",
        "//third_party/absl/strings:cord",
        "//third_party/cloud_cpp/google/cloud:google_cloud_cpp_common",
        "//third_party/curl:curl_for_third_party",
        "//third_party/json",
        "//third_party/openssl:crypto",
        "//util/hash:crc32c",
    ],
)

cc_library(
    name = "storage_client_testing",
    testonly = True,
    srcs = storage_client_testing_srcs,
    hdrs = storage_client_testing_hdrs,
    copts = [
        "-I$(GENDIR)",
        "-Wno-google3-literal-operator",
        "-Wno-google3-inline-namespace",
    ],
    deps = [
        ":storage_client",
        "//testing/base/public:gunit",
        "//third_party/absl/strings",
        "//third_party/absl/strings:cord",
        "//third_party/cloud_cpp/google/cloud:google_cloud_cpp_common",
        "//third_party/cloud_cpp/google/cloud:google_cloud_cpp_testing",
        "//third_party/curl:curl_for_third_party",
        "//third_party/json",
        "//third_party/openssl:crypto",
        "//util/hash:crc32c",
    ],
)

[cc_test(
    name = "storage_client_" + test.replace("/", "_").replace(".cc", ""),
    srcs = [test],
    copts = [
        "-I$(GENDIR)",
        "-Wno-google3-literal-operator",
        "-Wno-google3-inline-namespace",
    ],
    deps = [
        ":storage_client",
        ":storage_client_testing",
        "//testing/base/public:gunit",
        "//testing/base/public:gunit_main",
        "//third_party/cloud_cpp/google/cloud:google_cloud_cpp_common",
        "//third_party/cloud_cpp/google/cloud:google_cloud_cpp_testing",
        "//third_party/json",
        "//third_party/openssl:crypto",
    ],
) for test in storage_client_unit_tests]
