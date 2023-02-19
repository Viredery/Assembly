#include "state_record/deserialize/primitive_deserialize_traits.h"

#include <optional>

#include "gtest/gtest.h"

namespace state_record {

TEST(PrimitiveDeserializeTraitsTest, TestBasic) {
  EXPECT_TRUE(PrimitiveDeserializeTraits<int>::is_primitive);
  EXPECT_TRUE(PrimitiveDeserializeTraits<uint8_t>::is_primitive);
  EXPECT_TRUE(PrimitiveDeserializeTraits<std::string>::is_primitive);
  EXPECT_TRUE(PrimitiveDeserializeTraits<bool>::is_primitive);

  EXPECT_FALSE(PrimitiveDeserializeTraits<std::optional<int>>::is_primitive);

  PrimitiveDeserializeTraits<std::optional<int>> unsupported_deserializer;
  std::optional<int> value;
  EXPECT_EQ(unsupported_deserializer.Deserialize(std::nullopt, &value), 
            utils::Status::ERR_UNSUPPORTED);
}

TEST(PrimitiveDeserializeTraitsTest, TestArithmetric) {
  int int_value{0};
  EXPECT_EQ(PrimitiveDeserializeTraits<int>::Deserialize(std::nullopt, &int_value), 
            utils::Status::ERR_ILLEGAL_INPUT);

  PrimitiveDeserializeTraits<int>::Deserialize(std::make_optional("432"), &int_value);
  EXPECT_EQ(int_value, 432);

  uint8_t uint8_value{0};
  PrimitiveDeserializeTraits<uint8_t>::Deserialize(std::make_optional("32"), &uint8_value);
  EXPECT_EQ(uint8_value, 32);

  double double_value{0.0};
  PrimitiveDeserializeTraits<double>::Deserialize(std::make_optional("0.01"), &double_value);
  EXPECT_DOUBLE_EQ(double_value, 0.01);
}

TEST(PrimitiveDeserializeTraitsTest, TestBool) {
  bool bool_value{false};
  EXPECT_EQ(PrimitiveDeserializeTraits<bool>::Deserialize(std::nullopt, &bool_value), 
            utils::Status::ERR_ILLEGAL_INPUT);

  PrimitiveDeserializeTraits<bool>::Deserialize(std::make_optional("True"), &bool_value);
  EXPECT_EQ(bool_value, true);

  PrimitiveDeserializeTraits<bool>::Deserialize(std::make_optional("false"), &bool_value);
  EXPECT_EQ(bool_value, false);
}

TEST(PrimitiveDeserializeTraitsTest, TestString) {
  std::string string_value;
  EXPECT_EQ(PrimitiveDeserializeTraits<std::string>::Deserialize(std::nullopt, &string_value), 
            utils::Status::ERR_ILLEGAL_INPUT);

  PrimitiveDeserializeTraits<std::string>::Deserialize(
      std::make_optional("false"), &string_value);
  EXPECT_EQ(string_value, "false");  
}

}  // namespace state_record
