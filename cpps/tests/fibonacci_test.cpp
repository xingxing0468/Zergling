#include "gtest/gtest.h"

extern int Fibonacci(unsigned int n);

TEST(FibonacciTest, Base) {
  EXPECT_EQ(Fibonacci(1), 1);
  EXPECT_EQ(Fibonacci(0), 0);
}

TEST(Finonacci, Typical) { EXPECT_EQ(Fibonacci(10), 55); }