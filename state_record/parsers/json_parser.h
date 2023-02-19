#pragma once

#include <optional>
#include <string>

#include "json/json.h"

#include "state_record/utils/status.h"

namespace state_record {

struct JsonParser {
  struct ElemType {
    explicit ElemType(const Json::Value& elem, const char* key_name = {});
    bool IsValid() const;
    std::optional<std::string> GetValueText() const;
    const char* GetKeyName() const;
    ElemType ToChildElem(const char* field_name) const;

    template<typename F>
    utils::Status ForEachElement(F&& f) const;
   private:
    const char* key_name_ = nullptr;
    Json::Value elem_;
  };

  utils::Status Parse(const std::string& content);
  ElemType ToRootElemType();

  Json::Value root;
};

}  // namespace state_record
