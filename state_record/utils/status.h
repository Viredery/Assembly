#pragma once

namespace state_record {

namespace utils {

enum class Status: uint8_t {
  SUCCESS,
  ERR_UNSUPPORTED,
  ERR_ILLEGAL_INPUT,
};

} // namespace utils

#define RETURN_IF_ERROR(call)                            \
do {                                                     \
  if (auto res = call; res != utils::Status::SUCCESS) {  \
    return res;                                          \
  }                                                      \
} while(0)

}  // namespace state_record
