cc_library(
    name = "A",
    srcs = ["srcs/A.cpp"],
    hdrs = ["includes/A.h"],
    visibility = [":__subpackages__"],
)


cc_test(
    name = "TestA",
    srcs = ["tests/A_unit_test.cpp"],
    deps = [":A",
            "@googletest//:gtest_main",],
)