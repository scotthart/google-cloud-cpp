package(default_visibility = ["//visibility:public"])

licenses(["notice"])  # Apache 2.0

cc_binary(
    name = "bigtable_hello_google3",
    srcs = [
        "bigtable_hello_google3.cc",
    ],
    deps = [
        "//base",
        "//net/grpc:grpc++",
        "//third_party/cloud_cpp/google/cloud:google_cloud_cpp_common",
        "//third_party/cloud_cpp/google/cloud/bigtable:bigtable_client",
    ],
)
