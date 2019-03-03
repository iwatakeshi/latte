#ifndef LATTE_CORE_RESULT_H
#define LATTE_CORE_RESULT_H
#include <list>
#include <memory>
#include <string>
#include <tuple>
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
  latte_it_result(const latte_it_result& other) {
    this->state_ = other.state_;
    this->description_ = other.description_;
    this->message_ = other.message_;
    this->depth_string_ = other.depth_string_;
  }

  latte_it_result(const std::string& description) :
      description_(description){};

  latte_it_result(const std::string& description, const std::string& message) :
      latte_it_result(description, message, latte_result_state::pending){};

  latte_it_result(const std::string& description, const std::string& message, latte_result_state state) :
      description_(description), message_(message), state_(state){};

  latte_it_result& operator=(const latte_it_result& other) {
    this->state_ = other.state_;
    this->description_ = other.description_;
    this->message_ = other.message_;
    this->depth_string_ = other.depth_string_;
    this->time_ = other.time_;
    return *this;
  }

  double time() {
    return time_;
  }

  latte_result_state state() const {
    return state_;
  }

  const std::string description() {
    return description_;
  }

  const std::string message() {
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

  const std::string depth_string() {
    return depth_string_;
  }

  friend struct latte_describe;
  friend struct latte_it;

  private:
  std::string description_ = "";
  std::string message_ = "";
  latte_result_state state_;
  std::string depth_string_ = "";
  double time_ = 0;
};

struct latte_describe_result {
  latte_describe_result() {}
  // Performs a deep copy of latte_describe_result
  latte_describe_result(const latte_describe_result& other) {
    this->state_ = other.state_;
    this->description_ = other.description_;
    this->depth_string_ = other.depth_string_;
    this->time_ = other.time_;
    this->results_.assign(other.results_.begin(), other.results_.end());
  }

  latte_describe_result(const std::string& description) :
      description_(description){};
  latte_describe_result(const std::string& description, latte_result_state state, double time) :
      description_(description), state_(state), time_(time) {};

  latte_describe_result& operator=(const latte_describe_result& other) {
    this->state_ = other.state_;
    this->description_ = other.description_;
    this->depth_string_ = other.depth_string_;
    this->time_ = other.time_;
    this->results_.assign(other.results_.begin(), other.results_.end());
    return *this;
  }

  void add_result(std::shared_ptr<latte_it_result> result) {
    results_.push_back(result);
  }
  void add_result(const std::string& description, latte_result_state state) {
    add_result(description, "", state);
  }

  void add_result(const std::string& description, const std::string& message, latte_result_state state) {
    auto result = std::make_shared<latte_it_result>(description, message, state);
    results_.push_back(result);
  }

  double time() {
    return time_;
  }

  latte_result_state state() const {
    return state_;
  }

  const std::string description() {
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

  const std::string depth_string() {
    return depth_string_;
  }

  friend struct latte_describe;
  friend struct latte_it;

  private:
  std::string description_ = "";
  latte_result_state state_ = latte_result_state::pending;
  std::string depth_string_ = "";
  double time_ = 0;
  std::list<std::shared_ptr<latte_it_result>> results_;
};

} // core
} // name

#endif