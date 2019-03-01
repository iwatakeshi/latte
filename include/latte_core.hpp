#ifndef LATTE_CORE_H
#define LATTE_CORE_H
#include "latte_core_event.hpp"
#include "latte_core_event_emitter.hpp"
#include "latte_core_hook.hpp"
#include "latte_core_options.hpp"
#include "latte_core_result.hpp"
#include "latte_core_state.hpp"
#include "latte_type.hpp"
#include <functional>
#include <iostream>
#include <list>
#include <string>

namespace latte {
namespace core {

struct latte_test_core {

  protected:
  virtual void execute(const type::latte_callback&) {};
  virtual void only() {}
  void only(std::string, const type::latte_callback&) {};
  virtual void operator()() {}
  virtual void operator()(const type::latte_callback& function) {}
  virtual std::string depth_string() { return ""; };
  virtual std::string depth_string(int depth) const {
    std::string depth_string = "";
    for (auto i = 0; i < depth; i++) {
      depth_string += latte_options.indentation;
    }
    return depth_string;
  }
  virtual void operator()(std::string description, const type::latte_callback& function) {}
};

struct latte_describe : public latte_test_core {
  latte_describe(
    latte_before* before,
    latte_after* after,
    latte_before_each* before_each,
    latte_after_each* after_each,
    emitter::latte_event_emitter* emitter) :
      before_(before),
      after_(after), before_each_(before_each), after_each_(after_each), emitter_(emitter) {};

  ~latte_describe() {
    for (auto&& result : this->test_case_) {
      if (!result.results().empty()) {
        result.clear();
      }
    }
    this->test_case_.clear();

    for (auto&& result : this->test_cases_) {
      if (!result.results().empty()) {
        result.clear();
      }
    }
    this->test_case_.clear();
  }
  /**
   * Restricts the test suite and labels the it as pending suite.
   */
  void only(std::string description) {
    only_ = true;
    add_result(description);
  }

  /**
   * Restricts and runs the test suite.
   */
  void only(std::string description, const type::latte_callback& function) {
    only(description);
    this->execute(function);
  };

  void operator()() {}

  /**
   * Labels the test suite as pending.
   */
  void operator()(std::string description) {
    if (!only_) {
      add_result(description);
    }
  }

  /**
   * Runs the test suite.
   */
  virtual void operator()(std::string description, const type::latte_callback& function) {
    if (!only_) {
      this->operator()(description);
      this->execute(function);
    }
  }

  protected:
  /**
   * Returns the current depth of the parent
   */
  int depth() { return _latte_state.depth(); }
  int child_depth() { return _latte_state.depth() + 1; }

  void add_result(std::string description) {
    auto describe = latte_describe_result(description);
    describe.depth_string_ = this->depth_string();
    this->test_case_.push_back(describe);
  }

  private:
  std::list<latte_describe_result> test_case_;
  std::list<latte_describe_result> test_cases_;
  latte_before* before_ = nullptr;
  latte_after* after_ = nullptr;
  latte_before_each* before_each_ = nullptr;
  latte_after_each* after_each_ = nullptr;
  emitter::latte_event_emitter* emitter_;

  void execute(const type::latte_callback& function) {
    if (depth() == 0) {
      emitter_->emit(event::describe_event_test_start);
    }
    // Set describe()'s depth
    _latte_state.add_depth();
    // Start the call to other functions.
    function();
    // Clear the call stack at the specified level.
    this->clear_hooks();
    _latte_state.remove_depth();

    if (!this->test_case_.empty()) {
      emitter_->emit(event::latte_event::describe_event_test_result, this->test_case_);
      auto root = this->test_case_.front();
      this->test_cases_.push_back(root);
      this->test_case_.pop_front();
      root.clear();
    }

    if (depth() < 0) {
      emitter_->emit(event::describe_event_test_end, this->test_cases_);
    }
  }

  void clear_hooks() {
    before_->clear(depth());
    after_->clear(depth());
    before_each_->clear(depth());
    after_each_->clear(depth());
  }

  friend struct latte_it;

  std::string depth_string() {
    return latte_test_core::depth_string(depth());
  };

  bool only_ = false;
};

struct latte_it : public latte_test_core {
  latte_it(latte_describe* describe) :
      describe_(describe) {}

  void only(std::string description) {
    only_ = true;
    add_result(description, latte_result_state::pending);
  };

  void only(std::string description, const type::latte_callback& function) {
    only_ = true;
    execute(description, function);
  };

  void operator()() {}

  void operator()(std::string description) {
    if (!only_) {
      add_result(description, latte_result_state::pending);
    }
  }

  virtual void operator()(std::string description, const type::latte_callback& function) {
    if (!only_) {
      execute(description, function);
    }
  }

  protected:
  std::string depth_string() {
    return latte_test_core::depth_string(describe_->child_depth());
  }

  void add_result(std::string description, latte_result_state state) {
    // Create the result for it()
    auto result = latte_it_result(description, "", state);
    // Set it()'s depth string
    result.depth_string_ = this->depth_string();
    this->describe_->test_case_.back().add_result(result);
  }

  void add_result(std::string description, std::string message, latte_result_state state) {
    if (state == latte_result_state::failing) {
      // Update the result_state for describe() if a test case fails.
      this->describe_->test_case_.back().state_ = state;
    }
    // Create the result for it()
    auto result = latte_it_result(description, message, state);
    // Set it()'s depth string
    result.depth_string_ = this->depth_string();
    // Add the result
    this->describe_->test_case_.back().add_result(result);
  }

  private:
  latte_describe* describe_ = nullptr;
  bool only_ = false;

  // Executes the hooks and the callback method
  void execute(std::string description, const type::latte_callback& function) {
    auto result_state = latte_result_state::pending;
    std::string message = "";
    // Call before and before_each hooks
    describe_->before_->operator()(describe_->depth());
    describe_->before_each_->operator()(describe_->depth());

    try {
      function();
      result_state = latte_result_state::passing;
    } catch (const exception::latte_exception& e) {
      result_state = latte_result_state::failing;
      message = e.what();
    }

    add_result(description, message, result_state);

    // Call after and after_each hooks
    describe_->after_->operator()(describe_->depth());
    describe_->after_each_->operator()(describe_->depth());
    // We are done with before and after so don't let it() call it again.
    describe_->before_->clear(describe_->depth());
    this->describe_->depth();
    describe_->after_->clear(describe_->depth());
  }
};
} // core
} // latte

#endif