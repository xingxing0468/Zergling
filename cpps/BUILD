load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "Lib",
    srcs = [
        "srcs/A.cpp",
        "srcs/lis.cpp",
    ],
    hdrs = [
        "includes/A.h",
        "includes/lis.h",
    ],
    visibility = [":__subpackages__"],
)

cc_test(
    name = "Tests",
    srcs = [
        "tests/A_unit_test.cpp",
        "tests/lis_unit_test.cpp",
    ],
    deps = [
        ":Lib",
        "@googletest//:gtest_main",
    ],
)
