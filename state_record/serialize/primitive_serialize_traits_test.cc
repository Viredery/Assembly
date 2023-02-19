#include "state_record/serialize/primitive_serialize_traits.h"

#include <iostream>
#include <optional>

#include "gtest/gtest.h"

namespace state_record {

TEST(PrimitiveSerializeTraitsTest, TestBasic) {
  EXPECT_TRUE(PrimitiveSerializeTraits<int>::is_primitive);
  EXPECT_TRUE(PrimitiveSerializeTraits<uint8_t>::is_primitive);
  EXPECT_TRUE(PrimitiveSerializeTraits<std::string>::is_primitive);
  EXPECT_TRUE(PrimitiveSerializeTraits<bool>::is_primitive);

  EXPECT_FALSE(PrimitiveSerializeTraits<std::optional<int>>::is_primitive);
}

}  // namespace state_record
