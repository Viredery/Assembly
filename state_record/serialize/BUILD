package(default_visibility = ["//visibility:public"])

cc_library(
    name = "primitive_serialize_traits",
    hdrs = ["primitive_serialize_traits.h"],
    deps = [
        "//state_record/utils",
        "//state_record/utils:status",
    ],
)

cc_test(
    name = "primitive_serialize_traits_test",
    srcs = ["primitive_serialize_traits_test.cc",],
    deps = [
        ":primitive_serialize_traits",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "compound_serialize_traits",
    hdrs = ["compound_serialize_traits.h"],
    deps = [
        ":primitive_serialize_traits",
    ],
)

cc_test(
    name = "compound_serialize_traits_test",
    srcs = ["compound_serialize_traits_test.cc",],
    deps = [
        ":compound_serialize_traits",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
