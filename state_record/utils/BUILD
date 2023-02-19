package(default_visibility = ["//visibility:public"])

cc_library(
    name = "macros",
    hdrs = ["macros.h"],
)

cc_test(
    name = "macros_test",
    srcs = ["macros_test.cc",],
    deps = [
        ":macros",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "status",
    hdrs = ["status.h"],
)

cc_library(
    name = "utils",
    hdrs = ["utils.h"],
    deps = [
        ":status",
    ],
)

cc_test(
    name = "utils_test",
    srcs = ["utils_test.cc",],
    deps = [
        ":macros",
        ":utils",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
