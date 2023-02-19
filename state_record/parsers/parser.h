#pragma once

#include <concepts>
#include <optional>
#include <string>
#include <string_view>

#include "state_record/utils/status.h"

namespace state_record {

template <typename ElemType>
concept ParserElem = requires(const ElemType elem) {
  { elem.IsValid() } -> std::convertible_to<bool>;
  { elem.GetValueText() } -> std::same_as<std::optional<std::string>>;
  { elem.GetKeyName() } -> std::same_as<const char*>;
  { elem.ToChildElem("") } -> std::same_as<ElemType>;
  requires requires (utils::Status (&f)(ElemType)) {
    elem.ForEachElement(f);
  };
};

template <typename P>
inline constexpr bool enable_parser = false;

template <typename P>
concept Parser = enable_parser<P> || requires(P p, const std::string& content) {
  requires std::default_initializable<P>;
  typename P::ElemType;
  requires ParserElem<typename P::ElemType>;
  { p.Parse(content) } -> std::same_as<utils::Status>;
  { p.ToRootElemType() } -> std::same_as<typename P::ElemType>;
};

}  // namespace state_record
