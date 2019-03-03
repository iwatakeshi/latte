#ifndef LATTE_CORE_EXCEPTION_H
#define LATTE_CORE_EXCEPTION_H
#include <exception>
#include <iostream>
#include <string>

namespace latte {
namespace core {
namespace exception {

struct latte_exception {
  latte_exception() {};
  latte_exception(const std::string& actual, const std::string& expected, const std::string& message, bool errored = false) :
      actual_(actual),
      expected_(expected),
      message_(message), errored_(errored) {}

  latte_exception(const latte_exception& other) {
    this->actual_ = other.actual_;
    this->expected_ = other.expected_;
    this->message_ = other.message_;
    this->errored_ = other.errored_;
  }

  latte_exception& operator= (const latte_exception& other) {
    this->actual_ = other.actual_;
    this->expected_ = other.expected_;
    this->message_ = other.message_;
    this->errored_ = other.errored_;
    return *this;
  }

  const std::string what() const noexcept { return message_; }

  bool has_errored() const {
    return errored_;
  }

  std::string actual() {
    return actual_;
  }
  std::string expected() {
    return expected_;
  }

  private:
  std::string actual_;
  std::string expected_;
  std::string message_;
  bool errored_ = false;
};

} // exception
} // core
} // latte

#endif