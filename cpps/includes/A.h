#ifndef _A_H_
#define _A_H_

#include <optional>

class A {
 public:
  A() = default;
  std::optional<int> Foo(int input);
};

#endif