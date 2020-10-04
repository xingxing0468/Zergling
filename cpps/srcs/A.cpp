#include "cpps/includes/A.h"

#include <stdio.h>

std::optional<int> A::Foo(int input) {
  printf("A's Foo, input [%d]\n", input);

     if (input > 100) {
    return input;
  }

  else {
    return {};
  }
}
