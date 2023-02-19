#include "state_record/parsers/json_parser.h"

#include "gtest/gtest.h"

namespace state_record {

TEST(JsonParserTest, TestBasic) {
  JsonParser json_parser;
  const utils::Status status = json_parser.Parse("{"
    "\"hello\": \"world\","
    "\"t\": true , "
    "\"f\": false, "
    "\"n\": null, "
    "\"i\": 123, "
    "\"pi\": 3.1416, "
    "\"a\": [1, 2, 3, 4]"
  "}");
  EXPECT_EQ(status, utils::Status::SUCCESS);

  JsonParser::ElemType elem = json_parser.ToRootElemType();
  EXPECT_TRUE(elem.IsValid());
  EXPECT_EQ(elem.GetValueText(), std::nullopt);

  JsonParser::ElemType sub_elem = elem.ToChildElem("hello");
  EXPECT_EQ(sub_elem.GetValueText(), "world");

  sub_elem = elem.ToChildElem("t");
  EXPECT_EQ(sub_elem.GetValueText(), "true");

  sub_elem = elem.ToChildElem("n");
  EXPECT_EQ(sub_elem.GetValueText(), "");
}

}  // namespace state_record
