#ifndef LATTE_CORE_H
#define LATTE_CORE_H
#include "latte_core_event.hpp"
#include "latte_core_exception.hpp"
#include "latte_core_hook.hpp"
#include "latte_core_options.hpp"
#include "latte_core_result.hpp"
#include "latte_core_state.hpp"
#include "latte_type.hpp"
#include <bench.hpp>
#include <functional>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>

namespace latte {
namespace core {

struct latte_test_core {

  protected:
  virtual void execute(const type::latte_callback&){};
  virtual void only() {}
  void only(const std::string&, const type::latte_callback&){};
  virtual void operator()() {}
  virtual void operator()(const type::latte_callback&) {}
  virtual std::string depth_string() { return ""; };
  virtual std::string depth_string(int depth) const {
    std::string depth_string = "";
    for (auto i = 0; i < depth; i++) {
      depth_string += latte_options.indentation;
    }
    return depth_string;
  }
  virtual void operator()(const std::string&, const type::latte_callback&) {}
};

struct latte_describe : public latte_test_core {
  latte_describe(
    latte_before* before,
    latte_after* after,
    latte_before_each* before_each,
    latte_after_each* after_each) :
      before_(before),
      after_(after),
      before_each_(before_each),
      after_each_(after_each){};

  ~latte_describe() = default;
  /**
   * Restricts the test suite and labels the it as pending suite.
   */
  void only(const std::string& description) {
    only_map_[depth()] = true;
    add_result(description);
  }

  /**
   * Restricts and runs the test suite.
   */
  void only(const std::string& description, const type::latte_callback& function) {
    only(description);
    this->execute(function);
  };

  void operator()() {}

  /**
   * Labels the test suite as pending.
   */
  void operator()(const std::string& description) {
    if (!only_map_[this->depth()]) {
      add_result(description);
    }
  }

  /**
   * Runs the test suite.
   */
  virtual void operator()(const std::string& description, const type::latte_callback& function) {
    if (!only_map_[this->depth()]) {
      this->operator()(description);
      this->execute(function);
    }
  }

  protected:
  /**
   * Returns the current depth of the parent
   */
  int depth() { return _latte_state.depth(); }
  /**
   * Returns the current depth of the child
   */
  int child_depth() { return _latte_state.depth() + 1; }

  /**
   * Adds describe()'s result to the list of test suites.
   */
  void add_result(const std::string& description) {
    auto describe = std::make_shared<latte_describe_result>(description);
    describe->depth_string_ = this->depth_string();
    this->test_cases_.push_back(describe);
  }

  private:
  std::list<std::shared_ptr<latte_describe_result>> test_cases_;
  std::list<std::shared_ptr<latte_describe_result>> test_suite_;
  latte_before* before_ = nullptr;
  latte_after* after_ = nullptr;
  latte_before_each* before_each_ = nullptr;
  latte_after_each* after_each_ = nullptr;
  std::unordered_map<int, bool> only_map_;

  void execute(const type::latte_callback& function) {
    if (depth() == 0) {
      event::latte_describe_emitter.emit(event::describe_event_test_start);
    }
    // Set describe()'s depth
    _latte_state.add_depth();
    // Start the call to other functions.
    auto time = bench::time([&] {
      function();
    });

    // Assume that test is really passing
    if (this->test_cases_.back()->is_pending()) {
      this->test_cases_.back()->state_ = latte_result_state::passing;
    }
    
    this->test_cases_.back()->time_ = time;
    // std::cout << std::to_string(time) << std::endl;
    // Clear the call stack at the specified level.
    this->clear_hooks();
    _latte_state.remove_depth();

    if (!this->test_cases_.empty()) {
      event::latte_describe_emitter.emit(event::latte_event::describe_event_test_result, this->test_cases_);
      auto root = this->test_cases_.front();
      //  std::cout << "TIME!!: " + std::to_string(root->time()) << std::endl;
      this->test_suite_.push_back(root);
      this->test_cases_.pop_front();
    }

    if (depth() < 0) {
      event::latte_describe_emitter.emit(event::describe_event_test_end, this->test_suite_);
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

  void only(const std::string& description) {
    only_ = true;
    add_result(description, latte_result_state::pending);
  };

  void only(const std::string& description, const type::latte_callback& function) {
    only_ = true;
    execute(description, function);
  };

  void operator()() {}

  void operator()(const std::string& description) {
    if (!only_) {
      add_result(description, latte_result_state::pending);
    }
  }

  virtual void operator()(const std::string& description, const type::latte_callback& function) {
    if (!only_) {
      execute(description, function);
    }
  }

  protected:
  std::string depth_string() {
    return latte_test_core::depth_string(describe_->child_depth());
  }

  void add_result(const std::string& description, latte_result_state state) {
    // Create the result for it()
    auto result = std::make_shared<latte_it_result>(description, "", state);
    // Set it()'s depth string
    result->depth_string_ = this->depth_string();
    auto current_describe = this->describe_->test_cases_.back();
    current_describe->add_result(result);
  }

  void add_result(const std::string& description, std::string message, latte_result_state state, double time) {
    if (state == latte_result_state::failing) {
      // Update the result_state for describe() if a test case fails.
      this->describe_->test_cases_.back()->state_ = state;
    }
    // Create the result for it()
    auto result = std::make_shared<latte_it_result>(description, message, state);
    // Set it()'s depth string
    result->depth_string_ = this->depth_string();
    // Add the result
    this->describe_->test_cases_.back()->add_result(result);
  }

  private:
  latte_describe* describe_ = nullptr;
  bool only_ = false;

  // Executes the hooks and the callback method
  void execute(const std::string& description, const type::latte_callback& function) {
    auto result_state = latte_result_state::pending;
    std::string message = "";
    // Call before and before_each hooks
    describe_->before_->operator()(describe_->depth());
    describe_->before_each_->operator()(describe_->depth());
    double time = 0;
    try {
      time = bench::time([&] () {
        function();
      });
      result_state = latte_result_state::passing;
    } catch (const exception::latte_exception& e) {
      result_state = latte_result_state::failing;
      message = e.what();
    }

    add_result(description, message, result_state, time);

    // Call after and after_each hooks
    describe_->after_->operator()(describe_->depth());
    describe_->after_each_->operator()(describe_->depth());
    // We are done with before and after so don't let it() call it again.
    describe_->before_->clear(describe_->depth());
    describe_->after_->clear(describe_->depth());
  }
};
} // core
} // latte

#endif