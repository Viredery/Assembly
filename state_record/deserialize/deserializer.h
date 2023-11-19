#pragma once

#include <concepts>

#include "state_record/deserialize/compound_deserialize_traits.h"

namespace state_record {

template<Parser P>
struct Load2Obj {
  template<typename T, std::invocable Loader>
  utils::Status operator() (Loader&& loader, T* obj) const {
    const std::string content{loader()};
    if (content.empty()) {
      return utils::Status::ERR_ILLEGAL_INPUT;
    }
    P parser;
    const utils::Status parsing_status = parser.Parse(content); 
    if (parsing_status != utils::Status::SUCCESS) {
      return parsing_status;
    }

    typename P::ElemType root_elem = parser.ToRootElemType();
    if (!root_elem.IsValid()) {
      return utils::Status::ERR_ILLEGAL_INPUT;
    }
    return CompoundDeserializeTraits<T>::Deserialize(root_elem, obj);
  }
};

}  // namespace state_record
