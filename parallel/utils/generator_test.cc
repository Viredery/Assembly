#include "parallel/utils/generator.h"

#include <iostream>

#include "gtest/gtest.h"

namespace parallel {

TEST(GeneratorTest, TestBasic) {
  auto func = []() -> Generator {
    for (int i = 0; i != 10; ++i) {
      co_yield i;
    }
  };

  Generator generator = func();
  int expected_value = 0;
  while (!generator.done()) {
    EXPECT_EQ(generator.current_value(), expected_value);
    generator.next();
    ++expected_value;
  }

  EXPECT_EQ(expected_value, 10);
}

}  // namespace parallel
