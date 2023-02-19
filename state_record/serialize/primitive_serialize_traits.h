#pragma once

#include <concepts>
#include <iostream>
#include <string>

#include "state_record/utils/status.h"
#include "state_record/utils/utils.h"

namespace state_record {

template <typename T>
struct PrimitiveSerializeTraits : internal::IsPrimitive<false> {
  static utils::Status Serialize(T t, std::ostream* out) {
    return utils::Status::ERR_UNSUPPORTED;
  }
};

template <internal::Arithmetric Number>
struct PrimitiveSerializeTraits<Number> : internal::IsPrimitive<true> {
  static utils::Status Serialize(Number number, std::ostream* out) {
    if constexpr (std::is_same_v<Number, int8_t> || std::is_same_v<Number, uint8_t>) {
      *out << +number;
    } else {
      *out << number;
    }
    return utils::Status::SUCCESS;
  }
};

template <>
struct PrimitiveSerializeTraits<bool> : internal::IsPrimitive<true> {
  static utils::Status Serialize(bool value, std::ostream* out) {
    *out << (value ? internal::kTrueValue : internal::kFalseValue);
    return utils::Status::SUCCESS;
  }
};

template <>
struct PrimitiveSerializeTraits<std::string> : internal::IsPrimitive<true> {
  static utils::Status Serialize(const std::string& value, std::ostream* out) {
    *out << "\"" << value << "\"";
    return utils::Status::SUCCESS;
  }
};

}  // namespace state_record
