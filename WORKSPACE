local_repository(name = "pesto", path = "submodule/pesto")
load("@pesto//:rules.bzl", "submodule_init", "library_all", "pip_import_requirements")
submodule_init()
load("@submodule//:all.bzl", "submodule_all")
submodule_all()
library_all()

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
http_archive(
      name = "cpp_common",
      urls = ["https://github.com/chronoxor/CppCommon/archive/master.zip"],
      sha256 = "29c87956e3e9ec26d73a66523cac411b8e86871564084dc2940327fb6bb0e848",
      build_file = "@//:cppcommon.BUILD",
)

