#ifndef LATTE_CORE_DEFINITION_H
#define LATTE_CORE_DEFINITION_H
#include <functional>
#include <tuple>
#include <type_traits>
#include "latte_core_result.hpp"
namespace latte {
namespace type {

using latte_callback = std::function<void()>;

template <typename T, typename U>
using latte_comparator_callback = std::function<bool(T, U)>;

using latte_result_t = std::tuple<std::string, std::string, core::latte_result>;

template <typename T, typename U>
bool is_same() {
  return std::is_same<T, U>::value;
}
} // core
} // latte

#endif