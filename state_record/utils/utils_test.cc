#include "state_record/utils/utils.h"

#include <iostream>

#include "gtest/gtest.h"

#include "state_record/utils/macros.h"

namespace state_record {

DEFINE_SCHEMA(Point, (double) x, (double) y);

TEST(ForEachFieldTest, TestBasic) {
  Point point;

  utils::Status status = ForEachField(point, [](auto field) {
    if constexpr (std::same_as<std::decay_t<decltype(field.value())>, double>) {
      return utils::Status::SUCCESS;
    } else {
      return utils::Status::ERR_ILLEGAL_INPUT;
    }
  });
  EXPECT_EQ(status, utils::Status::SUCCESS);

  status = ForEachField(point, [](auto field) {
    if constexpr (std::same_as<std::decay_t<decltype(field.value())>, int>) {
      return utils::Status::SUCCESS;
    } else {
      return utils::Status::ERR_ILLEGAL_INPUT;
    }
  });
  EXPECT_EQ(status, utils::Status::ERR_ILLEGAL_INPUT);
}

}  // namespace state_record
