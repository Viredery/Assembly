package(default_visibility = ["//visibility:public"])

cc_library(
    name = "primitive_deserialize_traits",
    hdrs = ["primitive_deserialize_traits.h"],
    deps = [
        "//state_record/utils:status",
        "//state_record/utils",
    ],
)

cc_test(
    name = "primitive_deserialize_traits_test",
    srcs = ["primitive_deserialize_traits_test.cc",],
    deps = [
        ":primitive_deserialize_traits",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "compound_deserialize_traits",
    hdrs = ["compound_deserialize_traits.h"],
    deps = [
        ":primitive_deserialize_traits",
        "//state_record/parsers:parser",
    ],
)

cc_test(
    name = "compound_deserialize_traits_test",
    srcs = ["compound_deserialize_traits_test.cc",],
    deps = [
        ":compound_deserialize_traits",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "deserializer",
    hdrs = ["deserializer.h"],
    deps = [
        ":compound_deserialize_traits",
    ],
)
