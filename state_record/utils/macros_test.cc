#include "state_record/utils/macros.h"

#include <string>

#include "gtest/gtest.h"

namespace state_record {

DEFINE_SCHEMA(Point, (double) x, (double) y);

TEST(GetArgCountTest, TestBasic) {
  EXPECT_EQ(GET_ARG_COUNT(), 0);
  EXPECT_EQ(GET_ARG_COUNT(a, b, c), 3);
  EXPECT_EQ(GET_ARG_COUNT(a, b, c, d, e, f, g, h, i), 9);
}

TEST(DefineSchemaTest, TestBasic) {
  Point point;
  EXPECT_EQ(point._field_count_, 2);
  EXPECT_EQ(std::string(point._schema_name_), std::string("Point"));
}

}  // namespace state_record
