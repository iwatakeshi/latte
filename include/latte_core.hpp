#ifndef LATTE_CORE_H
#define LATTE_CORE_H
#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include "latte_type.hpp"
#include "latte_core_hook.hpp"
#include "latte_core_state.hpp"

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
    for(auto i = 0; i < depth; i++) {
      // depth_string += _latte_options.indentation;
    }
    return depth_string;
  }
  virtual void operator()(std::string description, const type::latte_callback& function) {}
};


struct latte_describe : latte_test_core {
  latte_describe(
    latte_before* before,
    latte_after* after,
    latte_before_each* before_each,
    latte_after_each* after_each
  ): 
  before_(before), after_(after),
  before_each_(before_each), after_each_(after_each) {};

  void only(const type::latte_callback& function) {
    only_ = true;
    _latte_state.add_depth();
    this->execute(function);
    // if (!this->result_map_.empty()) {
    //   // this->result_map_.clear();
    // }
    _latte_state.remove_depth();
  };

  void only(std::string description, const type::latte_callback& function) {
    only_ = true;
    this->description_ = description;
    this->only(function);
  };

  void operator() () {}

  void operator() (const type::latte_callback& function) {
    _latte_state.add_depth();
    if (!only_) {
      this->execute(function);
      // if (!this->result_map_.empty()) {
      //   this->result_map_.clear();
      // }
    }
    _latte_state.remove_depth();

    if (_latte_state.depth() == 0) {
      for(auto&& a : this->results_) {
        for(auto&& message : a) {
          debug(message);
        }
        
      }
      
    }
  };
  virtual void operator()(std::string description, const type::latte_callback& function) {
    this->description_ = description;
    this->operator()(function);
  }

  protected:
  int depth_ = 0;
  int depth() { return _latte_state.depth(); }
  int child_depth() { return _latte_state.depth() + 1; }
  private:
  std::string description_ = "";
  std::vector<std::vector<std::string>> results_;
  latte_before* before_ = nullptr;
  latte_after* after_ = nullptr;
  latte_before_each* before_each_ = nullptr;
  latte_after_each* after_each_ = nullptr;

  void execute(const type::latte_callback& function) {
    // Create an empty vector
    std::vector<std::string> s;
    this->results_.push_back(s);
    // Start the call to other functions.
    function();
    // Clear the call stack at the specified level.
    before_->clear(depth());
    after_->clear(depth());
    before_each_->clear(depth());
    after_each_->clear(depth());
  }

  friend struct latte_it;
  
  std::string depth_string() {
    return latte_test_core::depth_string(depth_);
  };

  bool only_ = false;
};

struct latte_it : latte_test_core {
  latte_it(latte_describe* describe): describe_(describe) {}

  void only(const type::latte_callback& function) {
    only_ = true;
    this->execute(function);
  };

  void only(std::string description, const type::latte_callback& function) {
    only_ = true;
    this->description_ = description;
    this->execute(function);
  };

  void operator()() {}

  void operator() (const type::latte_callback& function) {
    if (!only_) {
      this->execute(function);
    }
  };

  virtual void operator()(std::string description, const type::latte_callback& function) {
    this->description_ = description;
    this->operator()(function);
  }

  protected:
  std::string depth_string() {
    return latte_test_core::depth_string(describe_->child_depth());
  }
  private:
  std::string description_;
  latte_describe* describe_ = nullptr;
  bool only_ = false;
  
  // Executes the hooks and the callback method
  void execute(const type::latte_callback& function) {
    auto result_state = latte_result::pending;
    auto errored = false;
    std::string message = "";
    // Call before and before_each hooks
    describe_->before_->operator()(describe_->depth());
    describe_->before_each_->operator()(describe_->depth());
    
    try {
      function();
    } catch(const exception::latte_exception& e) {
      errored = true;
      result_state = latte_result::failing;
      message = e.what();
    }

    // 
    if (!describe_->results_.empty() && errored) {
      auto result_stack = describe_->results_.back();
      result_stack.push_back(message);
      describe_->results_[describe_->results_.size() - 1] = result_stack;
    }
    // Call after and after_each hooks
    describe_->after_->operator()(describe_->depth());
    describe_->after_each_->operator()(describe_->depth());
    // We are done with before and after so don't let it() call it again.
    describe_->before_->clear(describe_->depth());
    describe_->after_->clear(describe_->depth());
    
    
  }
};

latte::core::latte_before before;
latte::core::latte_before_each before_each;
latte::core::latte_after after;
latte::core::latte_after_each after_each;
latte::core::latte_describe describe(&before, &after, &before_each, &after_each);
latte::core::latte_it it(&describe);
} // core
} // latte

#endif