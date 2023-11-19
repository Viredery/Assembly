#include "parallel/utils/generator.h"

namespace parallel {

Generator::Generator(std::coroutine_handle<promise_type> h) 
  : coro_handle_(h) {}

Generator::Generator(Generator&& rhs) noexcept 
  : coro_handle_(std::exchange(rhs.coro_handle_, {})) {}

Generator::~Generator() {
  if (coro_handle_) {
    coro_handle_.destroy();
  }
}

void Generator::next() {
  return coro_handle_.resume();
}

bool Generator::done() {
  return coro_handle_.done();
}

int Generator::current_value() {
  return coro_handle_.promise().current_value_;
}

}  // namespace parallel
