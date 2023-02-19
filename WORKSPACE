load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
  name = "googletest",
  url = "https://github.com/google/googletest/archive/release-1.11.0.zip",
  sha256 = "353571c2440176ded91c2de6d6cd88ddd41401d14692ec1f99e35d013feda55a",
  strip_prefix = "googletest-release-1.11.0",
)

http_archive(
  name = "rapidjson",
  urls = [
    "https://github.com/Tencent/rapidjson/archive/v1.1.0.tar.gz",
  ],
  sha256 = "bf7ced29704a1e696fbccf2a2b4ea068e7774fa37f6d7dd4039d0787f8bed98e",
  strip_prefix = "rapidjson-1.1.0",
  build_file = "//third_party:rapidjson.BUILD",
)

http_archive(
    name = "jsoncpp",
    urls = [
      "https://github.com/open-source-parsers/jsoncpp/archive/1.8.4.tar.gz",
    ],
    sha256 = "c49deac9e0933bcb7044f08516861a2d560988540b23de2ac1ad443b219afdb6",
    strip_prefix = "jsoncpp-1.8.4",
    build_file = "//third_party:jsoncpp.BUILD",
)
