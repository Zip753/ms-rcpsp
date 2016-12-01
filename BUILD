filegroup(
    name = "sources",
    srcs = glob(["src/*.cpp"]),
)

filegroup(
    name = "headers",
    srcs = glob([
        "include/*.h",
        "src/*.tpp",
    ]),
)

cc_library(
    name = "ms_rcpsp_lib",
    srcs = [":sources"],
    hdrs = [":headers"],
    copts = ["-std=c++14"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "ms_rcpsp",
    srcs = ["ms_rcpsp.cpp"],
    copts = ["-std=c++14"],
    deps = [
        ":ms_rcpsp_lib",
        "//external:gflags_nothreads",
    ],
)
