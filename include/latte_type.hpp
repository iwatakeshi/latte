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

template<class T>
  struct is_integer_
    : std::integral_constant<
        bool,
        std::is_same<short int, typename std::decay<T>::type>::value ||
        std::is_same<unsigned short int, typename std::decay<T>::type>::value ||
        std::is_same<unsigned int, typename std::decay<T>::type>::value ||
        std::is_same<int, typename std::decay<T>::type>::value ||
        std::is_same<long int, typename std::decay<T>::type>::value ||
        std::is_same<unsigned int, typename std::decay<T>::type>::value ||
        std::is_same<unsigned long int, typename std::decay<T>::type>::value ||
        std::is_same<long long int, typename std::decay<T>::type>::value ||
        std::is_same<unsigned long long int, typename std::decay<T>::type>::value
  > {};

  template<class T>
  struct is_floating_point_
    : std::integral_constant<
        bool,
        std::is_same<double, typename std::decay<T>::type>::value ||
        std::is_same<long double, typename std::decay<T>::type>::value ||
        std::is_same<float, typename std::decay<T>::type>::value
  > {};

  template<class T>
  struct is_char_
    : std::integral_constant<
        bool,
        std::is_same<char, typename std::decay<T>::type>::value
  > {};

  template<class T>
  struct is_wchar_
    : std::integral_constant<
        bool,
        std::is_same<wchar_t, typename std::decay<T>::type>::value
  > {};
  
  template<class T>
  struct is_string_
    : std::integral_constant<
        bool,
        std::is_same<char const *, typename std::decay<T>::type>::value ||
        std::is_same<char *, typename std::decay<T>::type>::value ||
        std::is_same<std::string, typename std::decay<T>::type>::value
  > {};

  template<class T>
  struct is_basic_string_
    : std::integral_constant<
        bool,
        std::is_same<std::string, typename std::decay<T>::type>::value
  > {};

  template<class T>
  struct is_c_string_
    : std::integral_constant<
        bool,
        std::is_same<char const *, typename std::decay<T>::type>::value ||
        std::is_same<char *, typename std::decay<T>::type>::value
  > {};


  template <typename T, typename U>
  bool is_same() {
    return std::is_same<T, U>::value;
  }

  template <typename T>
  bool is_integer() {
    return is_integer_<T>::value;
  }

  template <typename T>
  bool is_floating_point() {
    return is_floating_point_<T>::value;
  }
  
  template <typename T>
  bool is_char() {
    return is_char_<T>::value;
  }

  template <typename T>
  bool is_wchar() {
    return is_wchar_<T>::value;
  }

  template <typename T>
  bool is_string() {
    return is_string_<T>::value;
  }

  template <typename T>
  bool is_basic_string() {
    return is_basic_string_<T>::value;
  }

  template <typename T>
  bool is_c_string() {
    return is_c_string_<T>::value;
  }

  template <typename T>
  bool is_primitive() {
    return is_integer<T>() || is_floating_point<T>() || is_char<T>() || is_wchar<T>() || is_string<T>();
  }
} // core
} // latte

#endif