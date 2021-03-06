#ifndef LATTE_CORE_COMPARATOR_H
#define LATTE_CORE_COMPARATOR_H
#include <string>
#include <to_string.hpp>
#include <functional>
#include <iostream>
#include <map>
#include <cmath>
#include "latte_type.hpp"

// https://stackoverflow.com/a/53865723/1251031
#ifndef _MSC_VER
#   include <cxxabi.h>
#endif
#include <memory>
#include <string>
#include <cstdlib>
#include <regex>
#include <type_traits>
template <class T>
std::string
type_name() {
	typedef typename std::remove_reference<T>::type TR;
  std::unique_ptr<char, void(*)(void*)> own
           (
#ifndef _MSC_VER
  abi::__cxa_demangle(typeid(TR).name(), nullptr, nullptr, nullptr),
#else
  	nullptr,
#endif
	std::free
);
	std::string r = own != nullptr ? own.get() : typeid(TR).name();
	if (std::is_const<TR>::value)
		r += " const";
	if (std::is_volatile<TR>::value)
		r += " volatile";
	if (std::is_lvalue_reference<T>::value)
		r += "&";
	else if (std::is_rvalue_reference<T>::value)
		r += "&&";
	return r;
}

namespace latte {
namespace core {
namespace comparator {

template <typename T>
inline bool __equal(T a, T b) { return a == b; };

template <typename T, typename U>
inline bool __equal(T, U) {
  return false;
};

template<typename T>
inline bool __strict_equal(T a, T b) { return a == b; }

// Strict comparison of different types
// will default to false
template<typename T, typename U>
inline bool __strict_equal(T, U) {
  return false;
};

/**
 * ========================
 *        nullptr_t
 * ========================
 */
template<>
inline bool __equal<>(nullptr_t, bool) { return false; }
template<>
inline bool __equal<>(nullptr_t, unsigned short int) { return false; }
template<>
inline bool __equal<>(nullptr_t, short int) { return false; }
template<>
inline bool __equal<>(nullptr_t, unsigned int) { return false; }
template<>
inline bool __equal<>(nullptr_t, int) { return false; }
template<>
inline bool __equal<>(nullptr_t, unsigned long int) { return false; }
template<>
inline bool __equal<>(nullptr_t, long int) { return false; }
template<>
inline bool __equal<>(nullptr_t, unsigned long long int) { return false; }
template<>
inline bool __equal<>(nullptr_t, long long int) { return false; }
template<>
inline bool __equal<>(nullptr_t, unsigned char) { return false; };
template<>
inline bool __equal<>(nullptr_t, char) { return false; };
template<>
inline bool __equal<>(nullptr_t, wchar_t) { return false; };
template<>
inline bool __equal<>(nullptr_t, float) { return false; };
template<>
inline bool __equal<>(nullptr_t, double) { return false; };
template<>
inline bool __equal<>(nullptr_t, long double) { return false; };
template<>
inline bool __equal<>(nullptr_t, std::string) { return false; };

/**
 * ========================
 *          bool
 * ========================
 */
template<>
inline bool __equal<>(bool a, unsigned short int b) { return (b == 0 || b == 1) && a == (bool)(b); };
template<>
inline bool __equal<>(bool a, short int b) { return (b == 0 || b == 1) && a == (bool)(b); };
template<>
inline bool __equal<>(bool a, unsigned int b) { return (b == 0 || b == 1) && a == (bool)(b); };
template<>
inline bool __equal<>(bool a, int b) { return (b == 0 || b == 1) && a == (bool)(b); };
template<>
inline bool __equal<>(bool a, unsigned long int b) { return (b == 0 || b == 1) && a == (bool)(b); };
template<>
inline bool __equal<>(bool a, long int b) { return (b == 0 || b == 1) && a == (bool)(b); };
template<>
inline bool __equal<>(bool a, unsigned long long int b) { return (b == 0 || b == 1) && a == (bool)(b); };
template<>
inline bool __equal<>(bool a, long long int b) { return (b == 0 || b == 1) && a == (bool)(b); };
template<>
inline bool __equal<>(bool a, unsigned char b) { return ((int)(b) == 0 || (int)(b) == 1) && a == (int)(b); };
template<>
inline bool __equal<>(bool a, char b) { return ((int)(b) == 0 || (int)(b) == 1) && a == (int)(b); };
template<>
inline bool __equal<>(bool, wchar_t) { return false; };
template<>
inline bool __equal<>(bool a, float b) { return ((int)(b) == 0 || (int)(b) == 1) && a == (int)(b); };
template<>
inline bool __equal<>(bool a, double b) { return ((int)(b) == 0 || (int)(b) == 1) && a == (int)(b); };
template<>
inline bool __equal<>(bool a, long double b) { return ((int)(b) == 0 || (int)(b) == 1) && a == (int)(b); };
template<>
inline bool __equal<>(bool a, std::string b) { return stdlib::to_string(a) == b; };
template<>
inline bool __equal<>(bool, nullptr_t) { return false; };

/**
 * ========================
 *    unsigned short int
 * ========================
 */
template<>
inline bool __equal<>(unsigned short int a, bool b) { return __equal(b, a); };
template<>
inline bool __equal<>(unsigned short int a, unsigned int b) { return a == (unsigned short int)(b); };
template<>
inline bool __equal<>(unsigned short int a, short int b) { return a == (unsigned short int)(b); };
template<>
inline bool __equal<>(unsigned short int a, int b) { return a == (unsigned short int)(b); };
template<>
inline bool __equal<>(unsigned short int a, unsigned long int b) { return a == (unsigned short int)(b); };
template<>
inline bool __equal<>(unsigned short int a, long int b) { return a ==(unsigned short int)(b); };
template<>
inline bool __equal<>(unsigned short int a, unsigned long long int b) { return a == (unsigned short int)(b); };
template<>
inline bool __equal<>(unsigned short int a, long long int b) { return a == (unsigned short int)(b); };
template<>
inline bool __equal<>(unsigned short int a, unsigned char b) { return a == (unsigned short int)(b); };
template<>
inline bool __equal<>(unsigned short int a, char b) { return a == (unsigned short int)(b); };
template<>
inline bool __equal<>(unsigned short int, wchar_t) { return false; };
template<>
inline bool __equal<>(unsigned short int a, float b) { return a == (unsigned short int)(std::round(b)); };
template<>
inline bool __equal<>(unsigned short int a, double b) { return a == (unsigned short int)(std::round(b)); };
template<>
inline bool __equal<>(unsigned short int a, long double b) { return a == (unsigned short int)(std::round(b)); };
template<>
inline bool __equal<>(unsigned short int a, std::string b) { return stdlib::to_string(a) == b; };
template<>
inline bool __equal<>(unsigned short int, nullptr_t) { return false; };

/**
 * ========================
 *        short int
 * ========================
 */
template<>
inline bool __equal<>(short int a, bool b) { return __equal(b, a); };
template<>
inline bool __equal<>(short int a, unsigned short int b) { return __equal(b, a); };
template<>
inline bool __equal<>(short int a, unsigned int b) { return a == (short int)(b); };
template<>
inline bool __equal<>(short int a, int b) { return a == (short int)(b); };
template<>
inline bool __equal<>(short int a, unsigned long int b) { return a == (short int)(b); };
template<>
inline bool __equal<>(short int a, long int b) { return a == (short int)(b); }
template<>
inline bool __equal<>(short int a, unsigned long long int b) { return a == (short int)(b); };
template<>
inline bool __equal<>(short int a, long long int b) { return a == (short int)(b); };
template<>
inline bool __equal<>(short int a, unsigned char b) { return a == (short int)(b); };
template<>
inline bool __equal<>(short int a, char b) { return a == (short int)(b); };
template<>
inline bool __equal<>(short int, wchar_t) { return false; };
template<>
inline bool __equal<>(short int a, float b) { return a == (short int)(std::round(b)); };
template<>
inline bool __equal<>(short int a, double b) { return a == (short int)(std::round(b)); };
template<>
inline bool __equal<>(short int a, long double b) { return a == (short int)(std::round(b)); };
template<>
inline bool __equal<>(short int a, std::string b) { return stdlib::to_string(a) == b; };
template<>
inline bool __equal<>(short int, nullptr_t) { return false; };

/**
 * ========================
 *       unsigned int
 * ========================
 */
template<>
inline bool __equal<>(unsigned int a, bool b) { return __equal(b, a); }
template<>
inline bool __equal<>(unsigned int a, unsigned short int b) { return a == (unsigned int)(b); }
template<>
inline bool __equal<>(unsigned int a, short int b) { return a == (unsigned int)(b); }
template<>
inline bool __equal<>(unsigned int a, unsigned int b) { return a == (unsigned int)(b); }
template<>
inline bool __equal<>(unsigned int a, int b) { return a == (unsigned int)(b); }
template<>
inline bool __equal<>(unsigned int a, unsigned long int b) { return a == (unsigned int)(b); }
template<>
inline bool __equal<>(unsigned int a, long int b) { return a ==(unsigned int)(b); }
template<>
inline bool __equal<>(unsigned int a, unsigned long long int b) { return a == (unsigned int)(b); }
template<>
inline bool __equal<>(unsigned int a, long long int b) { return a == (unsigned int)(b); }
template<>
inline bool __equal<>(unsigned int a, unsigned char b) { return a == (unsigned int)(b); };
template<>
inline bool __equal<>(unsigned int a, char b) { return a == (unsigned int)(b); };
template<>
inline bool __equal<>(unsigned int, wchar_t) { return false; };
template<>
inline bool __equal<>(unsigned int a, float b) { return a== (unsigned int)(std::round(b)); };
template<>
inline bool __equal<>(unsigned int a, double b) { return a == (unsigned int)(std::round(b)); };
template<>
inline bool __equal<>(unsigned int a, long double b) { return a == (unsigned int)(std::round(b)); }
template<>
inline bool __equal<>(unsigned int a, std::string b) { return stdlib::to_string(a) == b; };
template<>
inline bool __equal<>(unsigned int, nullptr_t) { return false; }

/**
 * ========================
 *          int
 * ========================
 */
template<>
inline bool __equal<>(int a, bool b) { return __equal(b, a); }
template<>
inline bool __equal<>(int a, unsigned short int b) { return a == (int)(b); }
template<>
inline bool __equal<>(int a, short int b) { return a == (int)(b); }
template<>
inline bool __equal<>(int a, unsigned int b) { return a == (int)(b); }
template<>
inline bool __equal<>(int a, int b) { return a == (int)(b); }
template<>
inline bool __equal<>(int a, unsigned long int b) { return a == (int)(b); }
template<>
inline bool __equal<>(int a, long int b) { return a ==(int)(b); }
template<>
inline bool __equal<>(int a, unsigned long long int b) { return a == (int)(b); }
template<>
inline bool __equal<>(int a, long long int b) { return a == (int)(b); }
template<>
inline bool __equal<>(int a, unsigned char b) { return a == (int)(b); };
template<>
inline bool __equal<>(int a, char b) { return a == (int)(b); };
template<>
inline bool __equal<>(int, wchar_t) { return false; };
template<>
inline bool __equal<>(int a, float b) { return a == (int)(std::round(b)); };
template<>
inline bool __equal<>(int a, double b) { return a == (int)(std::round(b)); };
template<>
inline bool __equal<>(int a, long double b) { return a == (int)(std::round(b)); }
template<>
inline bool __equal<>(int a, std::string b) { return stdlib::to_string(a) == b; };
template<>
inline bool __equal<>(int, nullptr_t) { return false; }

/**
 * ========================
 *    unsigned long int
 * ========================
 */
template<>
inline bool __equal<>(unsigned long int a, bool b) { return __equal(b, a); }
template<>
inline bool __equal<>(unsigned long int, nullptr_t) { return false; }
template<>
inline bool __equal<>(unsigned long int a, unsigned short int b) { return a == (unsigned long int)(b); }
template<>
inline bool __equal<>(unsigned long int a, short int b) { return a == (unsigned long int)(b); }
template<>
inline bool __equal<>(unsigned long int a, unsigned int b) { return a == (unsigned long int)(b); }
template<>
inline bool __equal<>(unsigned long int a, int b) { return a == (unsigned long int)(b); }
template<>
inline bool __equal<>(unsigned long int a, unsigned long int b) { return a == (unsigned long int)(b); }
template<>
inline bool __equal<>(unsigned long int a, long int b) { return a == (unsigned long int)(b); }
template<>
inline bool __equal<>(unsigned long int a, unsigned long long int b) { return a == (unsigned long int)(b); }
template<>
inline bool __equal<>(unsigned long int a, long long int b) { return a == (unsigned long int)(b); }
template<>
inline bool __equal<>(unsigned long int a, unsigned char b) { return a == (unsigned long int)(b); };
template<>
inline bool __equal<>(unsigned long int a, char b) { return a == (unsigned long int)(b); };
template<>
inline bool __equal<>(unsigned long int, wchar_t) { return false; };
template<>
inline bool __equal<>(unsigned long int a, float b) { return a == (unsigned long int)(std::round(b)); };
template<>
inline bool __equal<>(unsigned long int a, double b) { return a == (unsigned long int)(std::round(b)); };
template<>
inline bool __equal<>(unsigned long int a, long double b) { return a == (unsigned long int)(std::round(b)); }
template<>
inline bool __equal<>(unsigned long int a, std::string b) { return stdlib::to_string(a) == b; };

/**
 * ========================
 *        long int
 * ========================
 */
template<>
inline bool __equal<>(long int a, bool b) { return __equal(b, a); }
template<>
inline bool __equal<>(long int, nullptr_t) { return false; }
template<>
inline bool __equal<>(long int a, unsigned short int b) { return a == (long int)(b); }
template<>
inline bool __equal<>(long int a, short int b) { return a == (long int)(b); }
template<>
inline bool __equal<>(long int a, unsigned int b) { return a == (long int)(b); }
template<>
inline bool __equal<>(long int a, int b) { return a == (long int)(b); }
template<>
inline bool __equal<>(long int a, unsigned long int b) { return a == (long int)(b); }
template<>
inline bool __equal<>(long int a, unsigned long long int b) { return a == (long int)(b); }
template<>
inline bool __equal<>(long int a, long long int b) { return a == (long int)(b); }
template<>
inline bool __equal<>(long int a, unsigned char b) { return a == (long int)(b); };
template<>
inline bool __equal<>(long int a, char b) { return a == (long int)(b); };
template<>
inline bool __equal<>(long int, wchar_t) { return false; };
template<>
inline bool __equal<>(long int a, float b) { return a == (long int)(std::round(b)); };
template<>
inline bool __equal<>(long int a, double b) { return a == (long int)(std::round(b)); };
template<>
inline bool __equal<>(long int a, long double b) { return a == (long int)(std::round(b)); }
template<>
inline bool __equal<>(long int a, std::string b) { return stdlib::to_string(a) == b; };


/**
 * ========================
 *        unsigned long long int
 * ========================
 */
template<>
inline bool __equal<>(unsigned long long int a, bool b) { return __equal(b, a); }
template<>
inline bool __equal<>(unsigned long long int, nullptr_t) { return false; }
template<>
inline bool __equal<>(unsigned long long int a, unsigned short int b) { return a == (unsigned long long int)(b); }
template<>
inline bool __equal<>(unsigned long long int a, short int b) { return a == (unsigned long long int)(b); }
template<>
inline bool __equal<>(unsigned long long int a, unsigned int b) { return a == (unsigned long long int)(b); }
template<>
inline bool __equal<>(unsigned long long int a, int b) { return a == (unsigned long long int)(b); }
template<>
inline bool __equal<>(unsigned long long int a, unsigned long int b) { return a == (unsigned long long int)(b); }
template<>
inline bool __equal<>(unsigned long long int a, long int b) { return a == (unsigned long long int)(b); }
template<>
inline bool __equal<>(unsigned long long int a, long long int b) { return a == (unsigned long long int)(b); }
template<>
inline bool __equal<>(unsigned long long int a, unsigned char b) { return a == (unsigned long long int)(b); };
template<>
inline bool __equal<>(unsigned long long int a, char b) { return a == (unsigned long long int)(b); };
template<>
inline bool __equal<>(unsigned long long int, wchar_t) { return false; };
template<>
inline bool __equal<>(unsigned long long int a, float b) { return a == (unsigned long long int)(std::round(b)); };
template<>
inline bool __equal<>(unsigned long long int a, double b) { return a == (unsigned long long int)(std::round(b)); };
template<>
inline bool __equal<>(unsigned long long int a, long double b) { return a == (unsigned long long int)(std::round(b)); }
template<>
inline bool __equal<>(unsigned long long int a, std::string b) { return stdlib::to_string(a) == b; };

/**
 * ========================
 *      long long int
 * ========================
 */
template<>
inline bool __equal<>(long long int a, bool b) { return __equal(b, a); }
template<>
inline bool __equal<>(long long int, nullptr_t) { return false; }
template<>
inline bool __equal<>(long long int a, unsigned short int b) { return a == (long long int)(b); }
template<>
inline bool __equal<>(long long int a, short int b) { return a == (long long int)(b); }
template<>
inline bool __equal<>(long long int a, unsigned int b) { return a == (long long int)(b); }
template<>
inline bool __equal<>(long long int a, int b) { return a == (long long int)(b); }
template<>
inline bool __equal<>(long long int a, unsigned long int b) { return a == (long long int)(b); }
template<>
inline bool __equal<>(long long int a, long int b) { return a == (long long int)(b); }
template<>
inline bool __equal<>(long long int a, unsigned long long int b) { return a ==(long long int)(b); }
template<>
inline bool __equal<>(long long int a, unsigned char b) { return a == (long long int)(b); };
template<>
inline bool __equal<>(long long int a, char b) { return a == (long long int)(b); };
template<>
inline bool __equal<>(long long int, wchar_t) { return false; };
template<>
inline bool __equal<>(long long int a, float b) { return a == (long long int)(std::round(b)); };
template<>
inline bool __equal<>(long long int a, double b) { return a == (long long int)(std::round(b)); };
template<>
inline bool __equal<>(long long int a, long double b) { return a == (long long int)(std::round(b)); }
template<>
inline bool __equal<>(long long int a, std::string b) { return stdlib::to_string(a) == b; };

/**
 * ========================
 *        unsigned char
 * ========================
 */
template<>
inline bool __equal<>(unsigned char a, bool b) { return __equal(b, a); }
template<>
inline bool __equal<>(unsigned char a, unsigned short int b) { return __equal(b, a); }
template<>
inline bool __equal<>(unsigned char a, short int b) { return __equal(b, a); }
template<>
inline bool __equal<>(unsigned char a, unsigned int b) { return __equal(b, a); }
template<>
inline bool __equal<>(unsigned char a, int b) { return __equal(b, a); }
template<>
inline bool __equal<>(unsigned char a, unsigned long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(unsigned char a, long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(unsigned char a, unsigned long long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(unsigned char a, long long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(unsigned char a, char b) { return a == (unsigned char)(b); };
template<>
inline bool __equal<>(unsigned char, wchar_t) { return false; };
template<>
inline bool __equal<>(unsigned char a, float b) { return __equal(int(std::round(b)), a); };
template<>
inline bool __equal<>(unsigned char a, double b) { return __equal(int(std::round(b)), a); };
template<>
inline bool __equal<>(unsigned char a, long double b) { return __equal(int(std::round(b)), a); }
template<>
inline bool __equal<>(unsigned char a, std::string b) { return stdlib::to_string(a) == b; };
template<>
inline bool __equal<>(unsigned char, nullptr_t) { return false; }

/**
 * ========================
 *        char
 * ========================
 */
template<>
inline bool __equal<>(char a, bool b) { return __equal(b, a); }
template<>
inline bool __equal<>(char a, unsigned short int b) { return __equal(b, a); }
template<>
inline bool __equal<>(char a, short int b) { return __equal(b, a); }
template<>
inline bool __equal<>(char a, unsigned int b) { return __equal(b, a); }
template<>
inline bool __equal<>(char a, int b) { return __equal(b, a); }
template<>
inline bool __equal<>(char a, unsigned long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(char a, long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(char a, unsigned long long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(char a, long long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(char a, unsigned char b) { return __equal(b, a); };
template<>
inline bool __equal<>(char, wchar_t) { return false; };
template<>
inline bool __equal<>(char a, float b) { return __equal(int(std::round(b)), a); };
template<>
inline bool __equal<>(char a, double b) { return __equal(int(std::round(b)), a); };
template<>
inline bool __equal<>(char a, long double b) { return __equal(int(std::round(b)), a); }
template<>
inline bool __equal<>(char a, std::string b) { return stdlib::to_string(a) == b; };
template<>
inline bool __equal<>(char, nullptr_t) { return false; }

/**
 * ========================
 *        wchar_t
 * ========================
 */
template<>
inline bool __equal<>(wchar_t a, bool b) { return __equal(b, a); }
template<>
inline bool __equal<>(wchar_t a, unsigned short int b) { return __equal(b, a); }
template<>
inline bool __equal<>(wchar_t a, short int b) { return __equal(b, a); }
template<>
inline bool __equal<>(wchar_t a, unsigned int b) { return __equal(b, a); }
template<>
inline bool __equal<>(wchar_t a, int b) { return __equal(b, a); }
template<>
inline bool __equal<>(wchar_t a, unsigned long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(wchar_t a, long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(wchar_t a, unsigned long long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(wchar_t a, long long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(wchar_t a, unsigned char b) { return __equal(b, a); };
template<>
inline bool __equal<>(wchar_t a, char b) { return __equal(b, a); };
template<>
inline bool __equal<>(wchar_t, float) { return false; };
template<>
inline bool __equal<>(wchar_t, double) { return false; };
template<>
inline bool __equal<>(wchar_t, long double) { return false; }
template<>
inline bool __equal<>(wchar_t a, std::string b) { return stdlib::to_string(a) == b; };
template<>
inline bool __equal<>(wchar_t, nullptr_t) { return false; }

/**
 * ========================
 *        float
 * ========================
 */
template<>
inline bool __equal<>(float a, bool b) { return __equal(b, a); }
template<>
inline bool __equal<>(float a, unsigned short int b) { return __equal(b, a); }
template<>
inline bool __equal<>(float a, short int b) { return __equal(b, a); }
template<>
inline bool __equal<>(float a, unsigned int b) { return __equal(b, a); }
template<>
inline bool __equal<>(float a, int b) { return __equal(b, a); }
template<>
inline bool __equal<>(float a, unsigned long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(float a, long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(float a, unsigned long long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(float a, long long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(float a, unsigned char b) { return __equal(b, a); };
template<>
inline bool __equal<>(float a, char b) { return __equal(b, a); };
template<>
inline bool __equal<>(float a, wchar_t b) { return __equal(b, a); };
template<>
inline bool __equal<>(float a, double b) { return a == (float)(b); };
template<>
inline bool __equal<>(float a, long double b) { return a == (float)(b); }
template<>
inline bool __equal<>(float a, std::string b) { return stdlib::to_string(a) == b; };
template<>
inline bool __equal<>(float, nullptr_t) { return false; }

/**
 * ========================
 *        double
 * ========================
 */
template<>
inline bool __equal<>(double a, bool b) { return __equal(b, a); }
template<>
inline bool __equal<>(double a, unsigned short int b) { return __equal(b, a); }
template<>
inline bool __equal<>(double a, short int b) { return __equal(b, a); }
template<>
inline bool __equal<>(double a, unsigned int b) { return __equal(b, a); }
template<>
inline bool __equal<>(double a, int b) { return __equal(b, a); }
template<>
inline bool __equal<>(double a, unsigned long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(double a, long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(double a, unsigned long long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(double a, long long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(double a, unsigned char b) { return __equal(b, a); };
template<>
inline bool __equal<>(double a, char b) { return __equal(b, a); };
template<>
inline bool __equal<>(double a, wchar_t b) { return __equal(b, a); };
template<>
inline bool __equal<>(double a, float b) { return __equal(b, a); };
template<>
inline bool __equal<>(double a, long double b) { return a == (double)(b); }
template<>
inline bool __equal<>(double a, std::string b) { return stdlib::to_string(a) == b; };
template<>
inline bool __equal<>(double, nullptr_t) { return false; }

/**
 * ========================
 *        long double
 * ========================
 */
template<>
inline bool __equal<>(long double a, bool b) { return __equal(b, a); }
template<>
inline bool __equal<>(long double a, unsigned short int b) { return __equal(b, a); }
template<>
inline bool __equal<>(long double a, short int b) { return __equal(b, a); }
template<>
inline bool __equal<>(long double a, unsigned int b) { return __equal(b, a); }
template<>
inline bool __equal<>(long double a, int b) { return __equal(b, a); }
template<>
inline bool __equal<>(long double a, unsigned long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(long double a, long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(long double a, unsigned long long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(long double a, long long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(long double a, unsigned char b) { return __equal(b, a); };
template<>
inline bool __equal<>(long double a, char b) { return __equal(b, a); };
template<>
inline bool __equal<>(long double a, wchar_t b) { return __equal(b, a); };
template<>
inline bool __equal<>(long double a, float b) { return __equal(b, a); };
template<>
inline bool __equal<>(long double a, std::string b) { return stdlib::to_string(a) == b; };
template<>
inline bool __equal<>(long double, nullptr_t) { return false; };

/**
 * ========================
 *        string
 * ========================
 */
template<>
inline bool __equal<>(std::string a, bool b) { return __equal(b, a); }
template<>
inline bool __equal<>(std::string a, unsigned short int b) { return __equal(b, a); }
template<>
inline bool __equal<>(std::string a, short int b) { return __equal(b, a); }
template<>
inline bool __equal<>(std::string a, unsigned int b) { return __equal(b, a); }
template<>
inline bool __equal<>(std::string a, int b) { return __equal(b, a); }
template<>
inline bool __equal<>(std::string a, unsigned long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(std::string a, long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(std::string a, unsigned long long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(std::string a, long long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(std::string a, unsigned char b) { return __equal(b, a); };
template<>
inline bool __equal<>(std::string a, char b) { return __equal(b, a); };
template<>
inline bool __equal<>(std::string a, wchar_t b) { return __equal(b, a); };
template<>
inline bool __equal<>(std::string a, float b) { return __equal(b, a); };
template<>
inline bool __equal<>(std::string a, double b) { return __equal(b, a); };
template<>
inline bool __equal<>(std::string a, long double b) { return __equal(b, a); };
template<>
inline bool __equal<>(std::string a, nullptr_t b) { return __equal(b, a); };



template<typename t_type, typename u_type>
struct latte_comparator {
  using T = typename std::conditional<std::is_fundamental<t_type>::value, t_type, t_type&>::type;
  using U = typename std::conditional<std::is_fundamental<u_type>::value, u_type, u_type&>::type;
  latte_comparator() {
    equal = [&](T a, U b) -> bool { return __equal(a, b); };
    if (type::is_same<T, U>()) {
      strict_equal = equal;
    } else  {
      strict_equal = [&] (T a, U b) -> bool { return __strict_equal(a, b); };
    }
  };

  latte_comparator(type::latte_comparator_callback<T, U> comparator):
   equal(comparator),
   strict_equal(comparator) {};

  type::latte_comparator_callback<T, U> equal;
  type::latte_comparator_callback<T, U> strict_equal;
};
} // comparator
} // core
} // mocha


#endif