load(
    ":bigtable_client.bzl",
    "bigtable_client_srcs",
    "bigtable_client_hdrs",
)
load(
    ":bigtable_client_testing.bzl",
    "bigtable_client_testing_srcs",
    "bigtable_client_testing_hdrs",
)
load(
    ":bigtable_client_unit_tests.bzl",
    "bigtable_client_unit_tests",
)
load(
    ":bigtable_client_version.bzl",
    "BIGTABLE_CLIENT_VERSION_MAJOR",
    "BIGTABLE_CLIENT_VERSION_MINOR",
    "BIGTABLE_CLIENT_VERSION_PATCH",
)

package(default_visibility = ["//visibility:public"])

licenses(["notice"])  # Apache 2.0

genrule(
    name = "generate_version_info",
    srcs = ["version_info.h.in"],
    outs = ["version_info.h"],
    cmd = """
sed -e 's/@BIGTABLE_CLIENT_VERSION_MAJOR@/%s/' \
    -e 's/@BIGTABLE_CLIENT_VERSION_MINOR@/%s/' \
    -e 's/@BIGTABLE_CLIENT_VERSION_PATCH@/%s/' < $< > $@
""" % (
        BIGTABLE_CLIENT_VERSION_MAJOR,
        BIGTABLE_CLIENT_VERSION_MINOR,
        BIGTABLE_CLIENT_VERSION_PATCH,
    ),
)

cc_library(
    name = "bigtable_client",
    srcs = bigtable_client_srcs,
    hdrs = bigtable_client_hdrs + ["version_info.h"],
    copts = [
        "-Wno-google3-literal-operator",
        "-Wno-google3-inline-namespace",
    ],
    includes = ["."],
    deps = [
        "//google/bigtable/admin/v2:bigtable_instance_admin_proto",
        "//google/bigtable/admin/v2:bigtable_table_admin_proto",
        "//google/bigtable/admin/v2:common_proto",
        "//google/bigtable/admin/v2:table_proto",
        "//google/bigtable/v2:bigtable_proto",
        "//google/bigtable/v2:data_proto",
        "//google/longrunning:operations_cc_grpc_proto",
        "//google/protobuf:duration",
        "//google/protobuf:empty",
        "//net/grpc:grpc++",
        "//net/proto2/public:proto2",
        "//third_party/absl/strings",
        "//third_party/absl/strings:cord",
        "//third_party/cloud_cpp/google/cloud:google_cloud_cpp_common",
    ],
)

cc_library(
    name = "bigtable_client_testing",
    testonly = True,
    srcs = bigtable_client_testing_srcs,
    hdrs = bigtable_client_testing_hdrs,
    copts = [
        "-I$(GENDIR)",
        "-Wno-google3-literal-operator",
        "-Wno-google3-inline-namespace",
    ],
    deps = [
        ":bigtable_client",
        "//google/bigtable/admin/v2:bigtable_instance_admin_proto",
        "//google/bigtable/admin/v2:bigtable_table_admin_proto",
        "//google/bigtable/v2:bigtable_proto",
        "//google/bigtable/v2:data_proto",
        "//google/longrunning:operations_cc_grpc_proto",
        "//google/protobuf:duration",
        "//google/protobuf:empty",
        "//net/grpc:grpc++",
        "//net/proto2/public:proto2",
        "//net/proto2/util/public:differencer",
        "//testing/base/public:gunit",
        "//third_party/absl/strings",
        "//third_party/absl/strings:cord",
        "//third_party/cloud_cpp/google/cloud:google_cloud_cpp_common",
        "//third_party/cloud_cpp/google/cloud:google_cloud_cpp_testing",
    ],
)

EXCLUDED_TESTS = [
    "internal/async_future_from_callback_test.cc",
]

filtered_tests = [test for test in bigtable_client_unit_tests if not test in EXCLUDED_TESTS]

[cc_test(
    name = "bigtable_client_" + test.replace("/", "_").replace(".cc", ""),
    srcs = [test],
    copts = [
        "-I$(GENDIR)",
        "-Wno-google3-literal-operator",
        "-Wno-google3-inline-namespace",
    ],
    deps = [
        ":bigtable_client",
        ":bigtable_client_testing",
        "//google/bigtable/admin/v2:bigtable_instance_admin_proto",
        "//google/bigtable/admin/v2:bigtable_table_admin_cc_proto",
        "//google/bigtable/v2:bigtable_proto",
        "//google/bigtable/v2:data_proto",
        "//google/rpc:error_details",
        "//net/grpc:grpc++",
        "//net/proto2/public:proto2",
        "//net/proto2/util/public:differencer",
        "//testing/base/public:gunit",
        "//testing/base/public:gunit_main",
        "//third_party/cloud_cpp/google/cloud:google_cloud_cpp_common",
        "//third_party/cloud_cpp/google/cloud:google_cloud_cpp_testing",
    ],
) for test in filtered_tests]

cc_test(
    name = "bigtable_client_internal_readrowsparser_test",
    srcs = [
        "internal/readrowsparser_acceptance_tests.inc",
        "internal/readrowsparser_test.cc",
    ],
    deps = [
        ":bigtable_client",
        ":bigtable_client_testing",
        "//net/grpc:grpc++",
        "//net/proto2/public:proto2",
        "//net/proto2/util/public:differencer",
        "//testing/base/public:gunit",
        "//testing/base/public:gunit_main",
        "//third_party/cloud_cpp/google/cloud:google_cloud_cpp_common",
        "//third_party/cloud_cpp/google/cloud:google_cloud_cpp_testing",
    ],
)
