load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "Lib",
    srcs = [
        "srcs/A.cpp",
        "srcs/a_star.cpp",
        "srcs/find_kth_largest.cpp",
        "srcs/heap_sort.cpp",
        "srcs/lis.cpp"
    ],
    hdrs = [
        "includes/A.h",
        "includes/a_star.h",
        "includes/lis.h",
    ],
    visibility = [":__subpackages__"],
)

cc_test(
    name = "Tests",
    srcs = [
        "tests/A_unit_test.cpp",
        "tests/a_star_unit_test.cpp",
        "tests/find_kth_largest_test.cpp",
        "tests/heap_sort_test.cpp",
        "tests/lis_unit_test.cpp"
    ],
    deps = [
        ":Lib",
        "@googletest//:gtest_main",
    ],
)
