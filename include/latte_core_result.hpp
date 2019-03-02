#ifndef LATTE_CORE_RESULT_H
#define LATTE_CORE_RESULT_H
#include <list>
#include <string>
#include <tuple>
#include <memory>
namespace latte {
namespace core {

enum latte_result_state {
  pending = 0,
  passing = 1,
  failing = -1,
};

// struct latte_result_counter {
//   unsigned int pending = 0;
//   unsigned int passing = 0;
//   unsigned int failing = 0;

//   void reset() {
//     pending = passing = failing = 0;
//   }
// };

// latte_result_counter _latte_result_counter;

struct latte_it_result {
  latte_it_result() {}
  latte_it_result(std::string description)
      : description_(description) {};

  latte_it_result(std::string description, std::string message)
      : latte_it_result(description, message, latte_result_state::pending) {};

  latte_it_result(std::string description, std::string message, latte_result_state state)
      : description_(description)
      , message_(message)
      , state_(state) {};

  latte_result_state state() const {
    return state_;
  }

  std::string description() {
    return description_;
  }
  
  std::string message() {
    return message_;
  }
  

  bool is_passing() {
    return state_ == latte_result_state::passing;
  }

  bool is_failing() {
    return state_ == latte_result_state::failing;
  }

  bool is_pending() {
    return state_ == latte_result_state::pending;
  }

  std::string depth_string() {
    return depth_string_;
  }

  friend struct latte_describe;
  friend struct latte_it;

  private:
  latte_result_state state_;
  std::string description_ = "";
  std::string message_ = "";
  std::string depth_string_ = "";
};

struct latte_describe_result {
  latte_describe_result() {}
  latte_describe_result(std::string description)
      : description_(description) {};
  latte_describe_result(std::string description, latte_result_state state)
      : description_(description)
      , state_(state) {};

  void add_result(std::shared_ptr<latte_it_result> result) {
    results_.push_back(result);
  }
  void add_result(std::string description, latte_result_state state) {
    add_result(description, "", state);
  }

  void add_result(std::string description, std::string message, latte_result_state state) {
    auto result = std::make_shared<latte_it_result>(description, message, state);
    results_.push_back(result);
  }

  latte_result_state state() const {
    return state_;
  }

  std::string description() {
    return description_;
  }

  std::list<std::shared_ptr<latte_it_result>> results() {
    return results_;
  }

  bool is_passing() {
    return state_ == latte_result_state::passing;
  }

  bool is_failing() {
    return state_ == latte_result_state::failing;
  }

  bool is_pending() {
    return state_ == latte_result_state::pending;
  }

  std::string depth_string() {
    return depth_string_;
  }

  void clear() {
    results_.clear();
  }

  friend struct latte_describe;
  friend struct latte_it;

  private:
  latte_result_state state_;
  std::string description_ = "";
  std::string depth_string_ = "";
  std::list<std::shared_ptr<latte_it_result>> results_;
};

} // core
} // name

#endif