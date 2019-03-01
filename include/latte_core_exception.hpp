#ifndef LATTE_CORE_EXCEPTION_H
#define LATTE_CORE_EXCEPTION_H
#include <exception>
#include <iostream>
#include <string>

namespace latte {
namespace core {
namespace exception {

struct latte_exception : public std::exception {
  latte_exception(const std::string& message, bool errored = false)
      : message_(message)
      , errored_(errored) {}
  const char* what() const noexcept { return message_.c_str(); }
  bool has_errored() const {
    return errored_;
  }

  private:
  std::string message_;
  bool errored_ = false;
};

} // exception
} // core
} // latte

#endif