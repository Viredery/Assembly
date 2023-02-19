#pragma once

#include <algorithm>
#include <concepts>
#include <optional>
#include <sstream>
#include <string>
#include <type_traits>

#include "state_record/utils/status.h"
#include "state_record/utils/utils.h"

namespace state_record {

template <typename T>
struct PrimitiveDeserializeTraits : internal::IsPrimitive<false> {
  static utils::Status Deserialize(std::optional<std::string> value_text, T* t) {
    return utils::Status::ERR_UNSUPPORTED;
  }
};

template <internal::Arithmetric Number>
struct PrimitiveDeserializeTraits<Number> : internal::IsPrimitive<true> {
  static utils::Status Deserialize(std::optional<std::string> value_text, Number* number) {
    if (!value_text) {
      return utils::Status::ERR_ILLEGAL_INPUT;
    }
    if constexpr (std::is_same_v<Number, int8_t> || std::is_same_v<Number, uint8_t>) {
      *number = std::stol(*value_text);
      return utils::Status::SUCCESS;
    } else {
      std::stringstream ss;
      ss << *value_text;
      ss >> *number;
      return ss.fail() ? utils::Status::ERR_ILLEGAL_INPUT : utils::Status::SUCCESS;
    }
  }
};

template <>
struct PrimitiveDeserializeTraits<bool> : internal::IsPrimitive<true> {
  static utils::Status Deserialize(std::optional<std::string> value_text, bool* value) {
    if (!value_text) {
      return utils::Status::ERR_ILLEGAL_INPUT;
    }
    std::string lower_value_text;
    lower_value_text.resize(value_text->length());
    std::transform(value_text->begin(), value_text->end(), lower_value_text.begin(), ::tolower);
    if (lower_value_text == internal::kTrueValue) {
      *value = true;
      return utils::Status::SUCCESS;
    }
    if (lower_value_text == internal::kFalseValue) {
      *value = false;
      return utils::Status::SUCCESS;
    }
    return utils::Status::ERR_ILLEGAL_INPUT;
  }
};

template <>
struct PrimitiveDeserializeTraits<std::string> : internal::IsPrimitive<true> {
  static utils::Status Deserialize(std::optional<std::string> value_text, std::string* value) {
    if (!value_text) {
      return utils::Status::ERR_ILLEGAL_INPUT;
    }
    *value = std::move(*value_text);
    return utils::Status::SUCCESS;
  }
};

}  // namespace state_record
