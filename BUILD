filegroup(
    name = "sources",
    srcs = glob(["src/*.cpp"]),
)

filegroup(
    name = "headers",
    srcs = glob(["include/*.h"]),
)

cc_library(
    name = "ga_lib",
    srcs = [":sources"],
    hdrs = [":headers"],
)

cc_binary(
    name = "ga_bin",
    srcs = ["main.cpp"],
    linkopts = ["-pthread"],
    deps = [
        ":ga_lib",
        "//external:gflags",
    ],
)
