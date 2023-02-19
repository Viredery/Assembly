#include "state_record/parsers/json_parser.h"

namespace state_record {

JsonParser::ElemType::ElemType(const Json::Value& elem, const char* key_name)
  : key_name_(key_name), elem_(elem) {}

bool JsonParser::ElemType::IsValid() const { 
  return !elem_.isNull(); 
}

std::optional<std::string> JsonParser::ElemType::GetValueText() const {
  if (elem_.isObject() || elem_.isArray()) {
    return std::nullopt;
  }
  return elem_.asString();
}

const char* JsonParser::ElemType::GetKeyName() const {
  return key_name_;
}

JsonParser::ElemType JsonParser::ElemType::ToChildElem(const char* field_name) const {
  if (!elem_.isObject()) {
    return ElemType{Json::Value::nullSingleton()};
  }
  return ElemType{elem_[field_name]};
}

template<typename F>
utils::Status JsonParser::ElemType::ForEachElement(F&& f) const {
  if (elem_.isNull()) {
    return utils::Status::SUCCESS;
  }
  if (elem_.isArray()) {
    for (auto&& value: elem_) {
      RETURN_IF_ERROR(f(ElemType{value}));
    }
    return utils::Status::SUCCESS;
  }
  if (elem_.isObject()) {
    auto keys = elem_.getMemberNames();
    for (auto&& key: keys) {
      RETURN_IF_ERROR(f(ElemType{elem_[key], key.c_str()}));
    }
    return utils::Status::SUCCESS;
  }
  return utils::Status::ERR_UNSUPPORTED;
}

utils::Status JsonParser::Parse(const std::string& content) {
  Json::CharReaderBuilder builder;
  std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
  return reader->parse(content.data(), content.data() + content.size(),
                       &root , nullptr) ? utils::Status::SUCCESS
                                        : utils::Status::ERR_ILLEGAL_INPUT;
}

JsonParser::ElemType JsonParser::ToRootElemType() {
  return ElemType{root};
}

}  // namespace state_record
