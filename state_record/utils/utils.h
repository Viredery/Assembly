#pragma once

#include <cstddef>
#include <concepts>
#include <string_view>
#include <utility>

#include "state_record/utils/status.h"

namespace state_record {

namespace internal {

constexpr std::string_view kTrueValue = "true";
constexpr std::string_view kFalseValue = "false";

template <bool primitive>
struct IsPrimitive {
  static constexpr bool is_primitive = primitive;
};

template <typename T>
concept Arithmetric = std::is_arithmetic_v<T>;

template <typename T>
concept HasField = requires {
  typename std::decay_t<T>::template FIELD<T, 0>;
};

template <typename T>
concept Reflected = requires(T obj) {
  { obj._field_count_ } -> std::convertible_to<std::size_t>;
  requires requires {
    (obj._field_count_ == 0) || (obj._field_count_ > 0 && HasField<T>);
  };
};

// DummyField: used for check if `f' returns Status value or not(void)
struct DummyField {
  int& value();
  const char* name();
};

template <Reflected T, std::invocable<DummyField> F, std::size_t... Is>
constexpr auto ForEachField(T&& obj, F&& f, std::index_sequence<Is...>) {
  if constexpr (std::same_as<decltype(f(std::declval<DummyField>())), utils::Status>) {
    utils::Status status{utils::Status::SUCCESS};
    (void) (((status = f(typename std::decay_t<T>::template FIELD<T, Is>(std::forward<T>(obj)))) 
        == utils::Status::SUCCESS) && ...);
      return status;
  } else {
    (f(typename std::decay_t<T>::template FIELD<T, Is>(std::forward<T>(obj))), ...);
  }
}

}  // namespace internal

template <internal::Reflected T, std::invocable<internal::DummyField> F>
constexpr auto ForEachField(T&& obj, F&& f) {
  return internal::ForEachField(std::forward<T>(obj), 
                                std::forward<F>(f), 
                                std::make_index_sequence<std::decay_t<T>::_field_count_>());
}

}  // namespace state_record
