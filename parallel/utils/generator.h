#pragma once

#include <coroutine>
#include <utility>

namespace parallel {

class Generator {
 public:
  struct promise_type {
    Generator get_return_object() {
      return {std::coroutine_handle<promise_type>::from_promise(*this)};
    }

    std::suspend_never initial_suspend() noexcept { return {}; }
    std::suspend_never final_suspend() noexcept { return {}; }
    std::suspend_always yield_value(int value) {
      current_value_ = value;
      return {};
    }
    void return_void() {}
    void unhandled_exception() {}

    int current_value_ = 0;
  };

  Generator(Generator&& rhs) noexcept;

  ~Generator();

  void next();
  bool done();
  int current_value();

 private:
  Generator(std::coroutine_handle<promise_type> h);
  
  std::coroutine_handle<promise_type> coro_handle_;
};

}  // namespace parallel
