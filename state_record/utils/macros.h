#pragma once

#include <cstddef>

namespace state_record {

// GET_ARG_COUNT: get the length of the variable paramters.
//  It assumes that the the length is between 0 and 9.
#define GET_NTH_ARG(_1, _2, _3, _4, _5, _6, _7, _8, _9, n, ...) n
#define GET_ARG_COUNT(...) \
  GET_NTH_ARG(__VA_ARGS__ __VA_OPT__(,) 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

// REPEAT_##i: Repeat the function `f` `i` times, 
#define REPEAT_1(f, i, arg) f(i, arg)
#define REPEAT_2(f, i, arg, ...) f(i, arg) REPEAT_1(f, i + 1, __VA_ARGS__)
#define REPEAT_3(f, i, arg, ...) f(i, arg) REPEAT_2(f, i + 1, __VA_ARGS__)
#define REPEAT_4(f, i, arg, ...) f(i, arg) REPEAT_3(f, i + 1, __VA_ARGS__)
#define REPEAT_5(f, i, arg, ...) f(i, arg) REPEAT_4(f, i + 1, __VA_ARGS__)
#define REPEAT_6(f, i, arg, ...) f(i, arg) REPEAT_5(f, i + 1, __VA_ARGS__)
#define REPEAT_7(f, i, arg, ...) f(i, arg) REPEAT_6(f, i + 1, __VA_ARGS__)
#define REPEAT_8(f, i, arg, ...) f(i, arg) REPEAT_7(f, i + 1, __VA_ARGS__)
#define REPEAT_9(f, i, arg, ...) f(i, arg) REPEAT_8(f, i + 1, __VA_ARGS__)

// PAIR((double) a) -> PARE(double) a -> double a
#define PARE(...) __VA_ARGS__
#define PAIR(x) PARE x 

// STRIP((double) a) -> _EAT(double) a -> a
#define EAT(x) 
#define STRIP(x) EAT x

// STRING(a) -> STR(a) -> #a -> "a"
#define _STRING(x) #x
#define STRING(x) _STRING(x)

// PASTE(x, y) -> CONCATE(x, y) -> x ## y -> xy
#define _CONCATE(x, y) x ## y
#define CONCATE(x, y) _CONCATE(x, y)

// FIELD_EACH: class member and its relative FIELD used for record
#define FIELD_EACH(i, arg)                \
  PAIR(arg);                              \
  template <typename T>                   \
  struct FIELD<T, i> {                    \
    T& obj;                               \
    FIELD(T& obj): obj(obj) {}            \
    auto value() -> decltype(auto) {      \
      return (obj.STRIP(arg));            \
    }                                     \
    static constexpr const char* name() { \
      return STRING(STRIP(arg));          \
    }                                     \
  };                                      

// DEFINE_SCHEMA: define a struct with varibale recording support
#define DEFINE_SCHEMA(st, ...)                                                \
  struct st {                                                                 \
    template<typename, std::size_t> struct FIELD;                             \
    static constexpr std::size_t _field_count_ = GET_ARG_COUNT(__VA_ARGS__);  \
    static constexpr decltype(#st) _schema_name_ = #st;                       \
    CONCATE(REPEAT_, GET_ARG_COUNT(__VA_ARGS__)) (FIELD_EACH, 0, __VA_ARGS__) \
  }                                                                         

}  // namespace state_record
