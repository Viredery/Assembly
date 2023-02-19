package(default_visibility = ["//visibility:public"])

cc_library(
    name = "parser",
    hdrs = ["parser.h"],
    deps = [
        "//state_record/utils:status",
    ],
)

cc_library(
    name = "json_parser",
    srcs = ["json_parser.cc",],
    hdrs = ["json_parser.h"],
    deps = [
        "//state_record/utils:status",
        "@jsoncpp//:jsoncpp",
    ],
)

cc_test(
    name = "json_parser_test",
    srcs = ["json_parser_test.cc",],
    deps = [
        ":json_parser",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
