load(
    ":google_cloud_cpp_common.bzl",
    "google_cloud_cpp_common_srcs",
    "google_cloud_cpp_common_hdrs",
)
load(
    ":google_cloud_cpp_testing.bzl",
    "google_cloud_cpp_testing_srcs",
    "google_cloud_cpp_testing_hdrs",
)
load(
    ":google_cloud_cpp_common_unit_tests.bzl",
    "google_cloud_cpp_common_unit_tests",
)

package(default_visibility = ["//visibility:public"])

licenses(["notice"])  # Apache 2.0

genrule(
    name = "generate_build_info",
    srcs = ["internal/build_info.cc.in"],
    outs = ["internal/build_info.cc"],
    cmd = """
sed -e "s;@CMAKE_CXX_COMPILER_ID@;Clang;" \
    -e "s;@CMAKE_CXX_COMPILER_VERSION@;4.0.1;" \
    -e "s;@CMAKE_CXX_FLAGS@;$(CC_FLAGS);" \
    -e "s;@CMAKE_CXX_FLAGS_.*}@;$(CC_FLAGS);" \
    -e "s;@GIT_HEAD@;piper;" < $< > $@
  """,
    compatible_with = ["//buildenv/target:gce"],
    toolchains = [
        "//tools/cpp:cc_flags",
    ],
)

genrule(
    name = "generate_version_info",
    srcs = ["internal/version_info.h.in"],
    outs = ["internal/version_info.h"],
    cmd = """
sed -e 's/@GOOGLE_CLOUD_CPP_VERSION_MAJOR@/0/' \
    -e 's/@GOOGLE_CLOUD_CPP_VERSION_MINOR@/1/' \
    -e 's/@GOOGLE_CLOUD_CPP_VERSION_PATCH@/0/' < $< > $@
""",
    compatible_with = ["//buildenv/target:gce"],
)

cc_library(
    name = "google_cloud_cpp_common",
    srcs = google_cloud_cpp_common_srcs + ["internal/build_info.cc"],
    hdrs = google_cloud_cpp_common_hdrs + ["internal/version_info.h"],
    compatible_with = ["//buildenv/target:gce"],
    copts = [
        "-Wno-google3-literal-operator",
        "-Wno-google3-inline-namespace",
    ],
    includes = ["."],
    deps = [
    ],
)

cc_library(
    name = "google_cloud_cpp_testing",
    testonly = True,
    srcs = google_cloud_cpp_testing_srcs,
    hdrs = google_cloud_cpp_testing_hdrs,
    copts = [
        "-Wno-google3-literal-operator",
        "-Wno-google3-inline-namespace",
    ],
    includes = ["."],
    deps = [
        ":google_cloud_cpp_common",
        "//testing/base/public:gunit",
    ],
)

EXCLUDED_TESTS = [
    "internal/future_impl_test.cc",
    "future_void_test.cc",
    "future_void_then_test.cc",
    "future_generic_test.cc",
    "future_generic_then_test.cc",
]

filtered_tests = [test for test in google_cloud_cpp_common_unit_tests if not test in EXCLUDED_TESTS]

[cc_test(
    name = "google_cloud_cpp_common_" + test.replace("/", "_"),
    srcs = [test],
    copts = [
        "-I$(GENDIR)",
        "-Wno-google3-literal-operator",
        "-Wno-google3-inline-namespace",
    ],
    deps = [
        ":google_cloud_cpp_common",
        ":google_cloud_cpp_testing",
        "//testing/base/public:gunit",
        "//testing/base/public:gunit_main",
    ],
) for test in filtered_tests]
