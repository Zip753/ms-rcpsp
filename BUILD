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
    name = "ga_lib",
    srcs = [":sources"],
    hdrs = [":headers"],
    copts = ["-std=c++14"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "ga_bin",
    srcs = ["main.cpp"],
    copts = ["-std=c++14"],
    deps = [
        ":ga_lib",
    ],
)
