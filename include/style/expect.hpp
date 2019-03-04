#ifndef LATTE_STYLE_EXPECT_H
#define LATTE_STYLE_EXPECT_H
#include <string>
#include <to_string.hpp>
#include "../latte_core_exception.hpp"
#include "../latte_core_comparator.hpp"
namespace latte {
namespace style {

using core::exception::latte_exception;

template <typename T>
using type_t = typename std::conditional<
  std::is_same<char const *, typename std::decay<T>::type>::value ||
  std::is_same<char *, typename std::decay<T>::type>::value,
  std::string, T>::type;

  // expect: BDD
template <typename T>
struct expect_t {
  expect_t(T actual) : actual(actual) { };

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* equal(const char* expected) {
    return this->equal<std::string>(std::string(expected));
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* equal(T expected) {
    bool result = core::comparator::latte_comparator<type_t<T>, type_t<T>>().equal(this->actual, expected);
    this->eval(
      to_string(this->actual),
      to_string(expected),
      result,
      "expected " + to_string(this->actual) + " to " + (this->negate ? "not " : "") + "equal " + to_string(expected)
    );
    return this;
  };

  /**
   * [alias]
   * Compares the actual and expected of the same type.
   */
  expect_t* eql(T expected) {
    return this->equal(expected);
  };

  /**
   * Compares the actual and expected of different types.
   */
  template<typename U>
  expect_t* equal(U expected) {
    bool result = core::comparator::latte_comparator<type_t<T>, type_t<U>>().equal(this->actual, expected);
    this->eval(
      to_string(this->actual),
      to_string(expected),
      result,
      "expected " + to_string(this->actual) + " to " + (this->negate ? "not " : "") + "equal " + to_string(expected)
    );
    return this;
  };

  /**
   * [alias]
    * Compares the actual and expected of different types.
    */
  template <typename U>
  expect_t* eql(U expected) {
    return this->equal(expected);
  };

  /**
   * Compares the actual and expected of different types using a custom comparator function.
    */
  template <typename U>
  expect_t* equal(U expected, const core::comparator::latte_comparator<T, U>& comparator) {
    bool result = comparator.equal(this->actual, expected);
    this->eval(
      to_string(this->actual),
      to_string(expected),
      result,
      "expected " + to_string(this->actual) + " to " + (this->negate ? "not " : "") + "equal " + to_string(expected)
    );
    return this;
  };

  /**
   * [alias]
   * Compares the actual and expected of different types using a custom comparator function.
   */
  template <typename U>
  expect_t* eql(U expected, const core::comparator::latte_comparator<T, U>& comparator) {
    return this->equal(expected, comparator);
  };

  /**
   * Compares the actual and expected of different types using a custom comparator function.
   */
  template <typename U>
  expect_t* equal(U expected, const type::latte_comparator_callback<T, U>& comparator) {
    bool result = comparator(this->actual, expected);
    this->eval(
      to_string(this->actual),
      to_string(expected),
      result,
      "expected " + to_string(this->actual) + " to " + (this->negate ? "not " : "") + "equal " + to_string(expected)
    );
    return this;
  };

  /**
   * [alias]
   * Compares the actual and expected of different types using a custom comparator function.
   */
  template <typename U>
  expect_t* eql(U expected, const type::latte_comparator_callback<T, U>& comparator) {
    return this->equal(expected, comparator);
  };

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* equal(bool expected, const type::latte_comparator_callback<T, bool>& comparator) {
    return this->equal<bool>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* equal(short int expected, const type::latte_comparator_callback<T, short int>& comparator) {
    return this->equal<short int>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* equal(unsigned short int expected, const type::latte_comparator_callback<T, unsigned short int>& comparator) {
    return this->equal<unsigned short int>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* equal(unsigned int expected, const type::latte_comparator_callback<T, unsigned int>& comparator) {
    return this->equal<unsigned int>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* equal(int expected, const type::latte_comparator_callback<T, int>& comparator) {
    return this->equal<int>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* equal(unsigned long int expected, const type::latte_comparator_callback<T, unsigned long int>& comparator) {
    return this->equal<unsigned long int>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* equal(long long int expected, const type::latte_comparator_callback<T, long long int>& comparator) {
    return this->equal<long long int>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* equal(unsigned long long int expected, const type::latte_comparator_callback<T, unsigned long long int> &comparator) {
    return this->equal<unsigned long long int>(expected, comparator);
  }

  /**
  * Compares the actual and expected of the same type.
  */
  expect_t* equal(unsigned char expected, const type::latte_comparator_callback<T, unsigned char>& comparator) {
    return this->equal<unsigned char>(expected, comparator);
  }

  /**
  * Compares the actual and expected of the same type.
  */
  expect_t* equal(char expected, const type::latte_comparator_callback<T, char>& comparator) {
    return this->equal<char>(expected, comparator);
  }

  /**
  * Compares the actual and expected of the same type.
  */
  expect_t* equal(float expected, const type::latte_comparator_callback<T, float>& comparator) {
    return this->equal<float>(expected, comparator);
  }

  /**
  * Compares the actual and expected of the same type.
  */
  expect_t* equal(long double expected, const type::latte_comparator_callback<T, long double>& comparator) {
    return this->equal<long double>(expected, comparator);
  }

  /**
  * Compares the actual and expected of the same type.
  */
  expect_t* equal(wchar_t expected, const type::latte_comparator_callback<T, wchar_t>& comparator) {
    return this->equal<wchar_t>(expected, comparator);
  }

  /**
  * Compares the actual and expected of the same type.
  */
  expect_t* equal(const char* expected, const type::latte_comparator_callback<T, const char*>& comparator) {
    return this->equal<const char*>(expected, comparator);
  }

  /**
  * Compares the actual and expected of the same type.
  */
  expect_t* equal(const std::string& expected, const type::latte_comparator_callback<T, const std::string&> comparator) {
    return this->equal<const std::string&>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* eql(bool expected, const type::latte_comparator_callback<T, bool>& comparator) {
    return this->eql<bool>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* eql(short int expected, const type::latte_comparator_callback<T, short int>& comparator) {
    return this->eql<short int>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* eql(unsigned short int expected, const type::latte_comparator_callback<T, unsigned short int>& comparator) {
    return this->eql<unsigned short int>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* eql(unsigned int expected, const type::latte_comparator_callback<T, unsigned int>& comparator) {
    return this->eql<unsigned int>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* eql(int expected, const type::latte_comparator_callback<T, int>& comparator) {
    return this->eql<int>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* eql(unsigned long int expected, const type::latte_comparator_callback<T, unsigned long int>& comparator) {
    return this->eql<unsigned long int>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* eql(long long int expected, const type::latte_comparator_callback<T, long long int>& comparator) {
    return this->eql<long long int>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* eql(unsigned long long int expected, const type::latte_comparator_callback<T, unsigned long long int> &comparator) {
    return this->eql<unsigned long long int>(expected, comparator);
  }

  /**
  * Compares the actual and expected of the same type.
  */
  expect_t* eql(unsigned char expected, const type::latte_comparator_callback<T, unsigned char>& comparator) {
    return this->eql<unsigned char>(expected, comparator);
  }

  /**
  * Compares the actual and expected of the same type.
  */
  expect_t* eql(char expected, const type::latte_comparator_callback<T, char>& comparator) {
    return this->eql<char>(expected, comparator);
  }

  /**
  * Compares the actual and expected of the same type.
  */
  expect_t* eql(float expected, const type::latte_comparator_callback<T, float>& comparator) {
    return this->eql<float>(expected, comparator);
  }

  /**
  * Compares the actual and expected of the same type.
  */
  expect_t* eql(long double expected, const type::latte_comparator_callback<T, long double>& comparator) {
    return this->eql<long double>(expected, comparator);
  }

  /**
  * Compares the actual and expected of the same type.
  */
  expect_t* eql(wchar_t expected, const type::latte_comparator_callback<T, wchar_t>& comparator) {
    return this->eql<wchar_t>(expected, comparator);
  }

  /**
  * Compares the actual and expected of the same type.
  */
  expect_t* eql(const char* expected, const type::latte_comparator_callback<T, const char*>& comparator) {
    return this->eql<const char*>(expected, comparator);
  }

  /**
  * Compares the actual and expected of the same type.
  */
  expect_t* eql(const std::string& expected, const type::latte_comparator_callback<T, const std::string&> comparator) {
    return this->eql<const std::string&>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* strict_equal(T expected) {
    bool result = core::comparator::latte_comparator<type_t<T>, type_t<T>>().strict_equal(this->actual, expected);
    this->eval(
      to_string(this->actual),
      to_string(expected),
      result,
      "expected " + to_string(this->actual) + " to strictly " + (this->negate ? "not " : "") + "equal " + to_string(expected)
    );
    return this;
  };

  /**
   * [alias]
   * Compares the actual and expected of the same type.
   */
  expect_t* seql(T expected) {
    return this->equal(expected);
  };

  /**
   * Compares the actual and expected of different types.
   */
  expect_t* strict_equal(const char* expected) {
    return this->strict_equal<std::string>(std::string(expected));
  }

  /**
   * Compares the actual and expected of different types.
   */
  template <typename U>
  expect_t* strict_equal(U expected) {
    bool result = core::comparator::latte_comparator<type_t<T>, type_t<U>>().strict_equal(this->actual, expected);
    // bool is_same_type = std::is_same<decltype(this->actual), decltype(expected)>::value;
    this->eval(
      to_string(this->actual),
      to_string(expected),
      result,
      "expected " + to_string(this->actual) + " to strictly " + (this->negate ? "not " : "") + "equal " + to_string(expected)
    );
    return this;
  };

  /**
   * [alias]
   * Compares the actual and expected of different types.
   */
  template <typename U>
  expect_t* seql(U expected) {
    return this->strict_equal(expected);
  };

  /**
   * Compares the actual and expected of different types using a custom comparator function.
   */
  template <typename U>
  expect_t* strict_equal(U expected, const core::comparator::latte_comparator<T, U>& comparator) {
    bool result = comparator.strict_equal(this->actual, expected);
    this->eval(
      to_string(this->actual),
      to_string(expected),
      result,
      "expected " + to_string(this->actual) + " to strictly" + (this->negate ? "not " : "") + "equal " + to_string(expected)
    );

    return this;
  };

  /**
   * [alias]
   * Compares the actual and expected of different types using a custom comparator function.
   */
  template <typename U>
  expect_t* seql(U expected, const core::comparator::latte_comparator<T, U>& comparator) {
    return this->strict_equal(expected, comparator);
  };

  /**
   * Compares the actual and expected of different types using a custom comparator function.
   */
  template <typename U>
  expect_t* strict_equal(U expected, const type::latte_comparator_callback<T, U>& comparator) {
    bool result = comparator(this->actual, expected);
    this->eval(
      to_string(this->actual),
      to_string(expected),
      result,
      "expected " + to_string(this->actual) + " to strictly" + (this->negate ? "not " : "") + "equal " + to_string(expected)
    );

    return this;
  };

  /**
   * [alias]
   * Compares the actual and expected of different types using a custom comparator function.
   */
  template <typename U>
  expect_t* seql(U expected, const type::latte_comparator_callback<T, U>& comparator) {
    return this->strict_equal(expected, comparator);
  };

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* strict_equal(bool expected, const type::latte_comparator_callback<T, bool>& comparator) {
    return this->strict_equal<bool>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* strict_equal(short int expected, const type::latte_comparator_callback<T, short int>& comparator) {
    return this->strict_equal<short int>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* strict_equal(unsigned short int expected, const type::latte_comparator_callback<T, unsigned short int>& comparator) {
    return this->strict_equal<unsigned short int>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* strict_equal(unsigned int expected, const type::latte_comparator_callback<T, unsigned int>& comparator) {
    return this->strict_equal<unsigned int>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* strict_equal(int expected, const type::latte_comparator_callback<T, int>& comparator) {
    return this->strict_equal<int>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* strict_equal(unsigned long int expected, const type::latte_comparator_callback<T, unsigned long int>& comparator) {
    return this->strict_equal<unsigned long int>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* strict_equal(long long int expected, const type::latte_comparator_callback<T, long long int>& comparator) {
    return this->strict_equal<long long int>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* strict_equal(unsigned long long int expected, const type::latte_comparator_callback<T, unsigned long long int> &comparator) {
    return this->strict_equal<unsigned long long int>(expected, comparator);
  }

  /**
  * Compares the actual and expected of the same type.
  */
  expect_t* strict_equal(unsigned char expected, const type::latte_comparator_callback<T, unsigned char>& comparator) {
    return this->strict_equal<unsigned char>(expected, comparator);
  }

  /**
  * Compares the actual and expected of the same type.
  */
  expect_t* strict_equal(char expected, const type::latte_comparator_callback<T, char>& comparator) {
    return this->strict_equal<char>(expected, comparator);
  }

  /**
  * Compares the actual and expected of the same type.
  */
  expect_t* strict_equal(float expected, const type::latte_comparator_callback<T, float>& comparator) {
    return this->strict_equal<float>(expected, comparator);
  }

  /**
  * Compares the actual and expected of the same type.
  */
  expect_t* strict_equal(long double expected, const type::latte_comparator_callback<T, long double>& comparator) {
    return this->strict_equal<long double>(expected, comparator);
  }

  /**
  * Compares the actual and expected of the same type.
  */
  expect_t* strict_equal(wchar_t expected, const type::latte_comparator_callback<T, wchar_t>& comparator) {
    return this->strict_equal<wchar_t>(expected, comparator);
  }

  /**
  * Compares the actual and expected of the same type.
  */
  expect_t* strict_equal(const char* expected, const type::latte_comparator_callback<T, const char*>& comparator) {
    return this->strict_equal<const char*>(expected, comparator);
  }

  /**
  * Compares the actual and expected of the same type.
  */
  expect_t* strict_equal(const std::string& expected, const type::latte_comparator_callback<T, const std::string&> comparator) {
    return this->strict_equal<const std::string&>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* seql(bool expected, const type::latte_comparator_callback<T, bool>& comparator) {
    return this->seql<bool>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* seql(short int expected, const type::latte_comparator_callback<T, short int>& comparator) {
    return this->seql<short int>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* seql(unsigned short int expected, const type::latte_comparator_callback<T, unsigned short int>& comparator) {
    return this->seql<unsigned short int>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* seql(unsigned int expected, const type::latte_comparator_callback<T, unsigned int>& comparator) {
    return this->seql<unsigned int>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* seql(int expected, const type::latte_comparator_callback<T, int>& comparator) {
    return this->seql<int>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* seql(unsigned long int expected, const type::latte_comparator_callback<T, unsigned long int>& comparator) {
    return this->seql<unsigned long int>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* seql(long long int expected, const type::latte_comparator_callback<T, long long int>& comparator) {
    return this->seql<long long int>(expected, comparator);
  }

  /**
   * Compares the actual and expected of the same type.
   */
  expect_t* seql(unsigned long long int expected, const type::latte_comparator_callback<T, unsigned long long int> &comparator) {
    return this->seql<unsigned long long int>(expected, comparator);
  }

  /**
  * Compares the actual and expected of the same type.
  */
  expect_t* seql(unsigned char expected, const type::latte_comparator_callback<T, unsigned char>& comparator) {
    return this->seql<unsigned char>(expected, comparator);
  }

  /**
  * Compares the actual and expected of the same type.
  */
  expect_t* seql(char expected, const type::latte_comparator_callback<T, char>& comparator) {
    return this->seql<char>(expected, comparator);
  }

  /**
  * Compares the actual and expected of the same type.
  */
  expect_t* seql(float expected, const type::latte_comparator_callback<T, float>& comparator) {
    return this->seql<float>(expected, comparator);
  }

  /**
  * Compares the actual and expected of the same type.
  */
  expect_t* seql(long double expected, const type::latte_comparator_callback<T, long double>& comparator) {
    return this->seql<long double>(expected, comparator);
  }

  /**
  * Compares the actual and expected of the same type.
  */
  expect_t* seql(wchar_t expected, const type::latte_comparator_callback<T, wchar_t>& comparator) {
    return this->seql<wchar_t>(expected, comparator);
  }

  /**
  * Compares the actual and expected of the same type.
  */
  expect_t* seql(const char* expected, const type::latte_comparator_callback<T, const char*>& comparator) {
    return this->seql<const char*>(expected, comparator);
  }

  /**
  * Compares the actual and expected of the same type.
  */
  expect_t* seql(const std::string& expected, const type::latte_comparator_callback<T, const std::string&> comparator) {
    return this->seql<const std::string&>(expected, comparator);
  }

  expect_t* close_to(double expected) {
    return this->close_to(expected, 0.0001);
  };

  expect_t* close_to(double expected, double tolerance) {
    this->eval(
      to_string(this->actual),
      "close to " + to_string(expected),
      fabs(this->actual - expected) <= tolerance,
      "expected " + to_string(this->actual) + " to " + (this->negate ? "not " : "") + "equal " + (to_string(expected) + " within tolerance of " + to_string(tolerance))
    );

    return this;
  };

  expect_t* within(double lower, double upper) {
    this->eval(
      to_string(this->actual),
      "within " + to_string(lower) + " and " + to_string(upper),
      this->actual > lower && this->actual < upper,
      "expected " + to_string(this->actual) + " to " + (this->negate ? "not " : "") + "be above " + to_string(lower) + " and below " + to_string(upper)
    );

    return this;
  };


  expect_t* above(double expected) {
    this->eval(
      to_string(this->actual),
      to_string(expected),
      this->actual > expected,
      "expected " + to_string(this->actual) + " to " + (this->negate ? "not " : "") + "be greater than " + to_string(expected)
    );

    return this;
  };
  expect_t* gt(double expected) {
    return this->above(expected);
  };
  expect_t* greater_than(double expected) {
    return this->above(expected);
  };

  expect_t* least(double expected) {
    this->eval(
      to_string(this->actual),
      to_string(expected),
      this->actual >= expected,
      "expected " + to_string(this->actual) + " to " + (this->negate ? "not " : "") + "be greater than or equal to " + to_string(expected)
    );

    return this;
  };
  expect_t* gte(double expected) {
    return this->least(expected);
  };

  expect_t* below(double expected) {
    this->eval(
      to_string(this->actual),
      to_string(expected),
      this->actual < expected,
      "expected " + to_string(this->actual) + " to " + (this->negate ? "not " : "") + "be lesser than " + to_string(expected)
    );

    return this;
  };

  expect_t* lt(double expected) {
    return this->below(expected);
  };

  expect_t* less_than(double expected) {
    return this->below(expected);
  };

  expect_t* most(double expected) {
    this->eval(
      to_string(this->actual),
      to_string(expected),
      this->actual <= expected,
      "expected " + to_string(this->actual) + " to " + (this->negate ? "not " : "") + "be less than or equal to " + to_string(expected)
    );

    return this;
  };

  expect_t* lte(double expected) {
    return this->most(expected);
  };

  expect_t* satisfy(std::function<bool (T)> lambda_test) {
    bool result = lambda_test(this->actual);
    return this->satisfy(
      result,
      "expected " + to_string(this->actual) + " to " + (this->negate ? "not " : "") + "satisfy the given test"
    );
  };

  expect_t* satisfy(bool result, std::string actual, std::string expected, std::string message) {
    this->eval(
      actual,
      expected,
      result,
      message
    );

    return this;
  };

  class member_logic {
    expect_t* expect_pointer;
    std::function<void (expect_t*)> getter_lambda;
    public:
      member_logic(expect_t *i, std::function<void (expect_t*)> getter_lambda) : expect_pointer(i), getter_lambda(getter_lambda) {};

      // Setter
      expect_t* operator = (const expect_t i) {
        return this->expect_pointer = (expect_t*)&i;

      };

      // Setter
      expect_t* operator = (const expect_t *i) {
        return this->expect_pointer = (expect_t*)i;
      };

      // Getter
      expect_t* operator -> () {
        this->getter_lambda(this->expect_pointer);
        return this->expect_pointer;
      };

      // Getter
      operator expect_t* () const {
        this->getter_lambda(this->expect_pointer);
        return this->expect_pointer;
      };
  };


  // Sets the negate flag when used
  // expect<int>(3).to->never->equal->(5);
  member_logic never{this, [&](expect_t* expect_pointer) {
    expect_pointer->negate = !expect_pointer->negate;
  }};



  // Provided as chainable getters to improve the readability of your assertions.
  // They do not provide testing capabilities.
  expect_t* to = this;
  expect_t* be = this;
  expect_t* been = this;
  expect_t* is = this;
  expect_t* that = this;
  expect_t* which = this;
  // `and` is a reserved keyword
  expect_t* then = this;//expect_t* and = this;
  expect_t* has = this;
  expect_t* have = this;
  expect_t* with = this;
  expect_t* at = this;
  expect_t* of = this;
  expect_t* same = this;

  protected:
    T actual;
    bool negate = false;

    void eval(std::string actual, std::string expected, bool result, const std::string& message) {
      bool did_pass = (this->negate ? !result : result);
      // Reset the flag
      this->negate = false;
      if (!did_pass) {
        throw core::exception::latte_exception { actual, expected, message, did_pass };
      }
    };

    template<typename U>
    std::string to_string(U value) {
      return type::is_string<U>() ? "\"" + utils::to_string(value) + "\"" : utils::to_string(value);
    }
};

template <typename T>
expect_t<type_t<T>> expect(T&& x) {
  return { std::forward<type_t<T>>(x) };
};
    
} // style
  
} // latte

#endif