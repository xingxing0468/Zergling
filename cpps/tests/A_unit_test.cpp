#include "cpps/includes/A.h"
#include "gtest/gtest.h"

TEST(A_FOO, EmptyOptionReturnWhenInputSmallerThan100) {
  A a;
  EXPECT_FALSE(a.Foo(90).has_value());
}

TEST(A_FOO, ReturnValueWhenInputLargerThan100) {
  A a;
  EXPECT_EQ(110, a.Foo(110));
}