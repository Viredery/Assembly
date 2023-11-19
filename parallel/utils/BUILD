package(default_visibility = ["//visibility:public"])

cc_library(
    name = "generator",
    hdrs = ["generator.h"],
    srcs = ["generator.cc"]
)

cc_test(
    name = "generator_test",
    srcs = ["generator_test.cc",],
    deps = [
        ":generator",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
