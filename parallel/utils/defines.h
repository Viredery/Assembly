#pragma once

#define SIMPLE_VARIABLE(variable, type, default_value)           \
 public:                                                         \
  const type& variable() const { return variable##_; }           \
  void set_##variable(type variable) { variable##_ = variable; } \
                                                                 \
 private:                                                        \
  type variable##_ = default_value


#define DISALLOW_COPY_AND_ASSIGN(Typename)                       \
Typename(const Typename&) = delete;                              \
void operator=(const Typename&) = delete
