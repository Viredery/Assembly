package(default_visibility = ["//visibility:public"])

licenses(["unencumbered"])

exports_files(["LICENSE"])

cc_library(
    name = "jsoncpp",
    srcs = [
        "src/lib_json/json_reader.cpp",
        "src/lib_json/json_tool.h",
        "src/lib_json/json_value.cpp",
        "src/lib_json/json_writer.cpp",
    ],
    hdrs = [
        "include/json/allocator.h",
        "include/json/assertions.h",
        "include/json/autolink.h",
        "include/json/config.h",
        "include/json/features.h",
        "include/json/forwards.h",
        "include/json/json.h",
        "include/json/reader.h",
        "include/json/value.h",
        "include/json/version.h",
        "include/json/writer.h",
    ],
    copts = ["-DJSON_USE_EXCEPTION=0"],
    includes = ["include"],
    deps = [":private"],
)

cc_library(
    name = "private",
    textual_hdrs = [
        "src/lib_json/json_valueiterator.inl",
        "src/lib_json/version.h.in",
    ],
)
