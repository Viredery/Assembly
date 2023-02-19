#pragma once

#include <concepts>

#include "state_record/serialize/primitive_serialize_traits.h"
#include "state_record/utils/status.h"
#include "state_record/utils/utils.h"

namespace state_record {

namespace internal {

template <typename T>
concept Primitive = requires {
  requires PrimitiveSerializeTraits<T>::is_primitive;
};

}  // namespace internal

template <internal::Reflected T>
struct CompoundSerializeTraits {
  static utils::Status Serialize(const T& obj, std::ostream* out) {
    std::size_t depth = 0;
    *out << "{";
    ForEachField(obj, [&out, depth](auto&& field) {
      decltype(auto) field_name = field.name();
      decltype(auto) value = field.value();
      return CompoundSerializeTraits<std::remove_cvref_t<decltype(field_value)>>
          ::Serialize(value, out);
    });
    *out << "}";
  }
};

template <internal::Primitive T>
struct CompoundSerializeTraits {
  static utils::Status Serialize(const T& obj, std::ostream* out) {
    return PrimitiveSerializeTraits<T>::Serialize(obj, &out);
  }
};

}  // namespace state_record
