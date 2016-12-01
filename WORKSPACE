git_repository(
    name = "googletest",
    commit = "a082411", # release-1.8.0-bazel-20161117
    remote = "https://github.com/chronos-tachyon/googletest-bazel.git",
)

git_repository(
    name   = "com_github_gflags_gflags",
    commit = "f8a0efe", # v2.2.0
    remote = "https://github.com/gflags/gflags.git",
)

bind(
    name = "gflags",
    actual = "@com_github_gflags_gflags//:gflags",
)

bind(
    name = "gflags_nothreads",
    actual = "@com_github_gflags_gflags//:gflags_nothreads",
)
