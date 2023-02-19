#pragma once

#include <concepts>

#include "state_record/deserialize/primitive_deserialize_traits.h"
#include "state_record/parsers/parser.h"
#include "state_record/utils/status.h"
#include "state_record/utils/utils.h"

namespace state_record {

namespace internal {

template <typename T>
concept Primitive = requires {
  requires PrimitiveDeserializeTraits<T>::is_primitive;
};

}  // namespace internal

template <typename T>
struct CompoundDeserializeTraits {
  template <ParserElem Elem>
  static utils::Status Deserialize(Elem node, T* obj) {
    return utils::Status::ERR_UNSUPPORTED;
  }
};

template <internal::Reflected T>
struct CompoundDeserializeTraits<T> {
  template <ParserElem Elem>
  static utils::Status Deserialize(Elem node, T* obj) {
    if (!node.IsValid()) {
      return utils::Status::ERR_ILLEGAL_INPUT;
    }
    return ForEachField(*obj, [&node](auto&& field) {
      decltype(auto) field_name = field.name();
      decltype(auto) field_value = field.value();
      return CompoundDeserializeTraits<std::remove_cvref_t<decltype(field_value)>>
          ::Deserialize(node.ToChildElem(field_name), &field_value);
    });
  }
};

template <internal::Primitive T>
struct CompoundDeserializeTraits<T> {
  template <ParserElem Elem>
  static utils::Status Deserialize(Elem node, T* obj) {
    if (!node.IsValid()) {
      return utils::Status::ERR_ILLEGAL_INPUT;
    }
    return PrimitiveDeserializeTraits<T>::Deserialize(node.GetValueText(), obj);
  }
};

}  // namespace state_record
