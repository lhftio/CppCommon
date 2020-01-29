load("@bazel_tools//tools/build_defs/pkg:pkg.bzl", "pkg_tar")

cc_library(
    name = "common",
    srcs = glob([
        "source/**/*.cpp",
    ]),
    hdrs = glob([
        "include/**/*.h",
        "include/**/*.inl",
    ]),
    strip_include_prefix = "include",
    deps = [
        "@boost//:headers",
    ],
    visibility = ["//visibility:public"],
)
