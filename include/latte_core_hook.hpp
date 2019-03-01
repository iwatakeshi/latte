#ifndef LATTE_CORE_HOOK_H
#define LATTE_CORE_HOOK_H
#include "latte_core_state.hpp"
#include "latte_type.hpp"
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace latte {
namespace core {

using type::latte_callback;

// Base class for before(), after(), before_each(), and after_each()
struct latte_test_hook {
  latte_test_hook(): latte_test_hook("latte_test_hook") {}
  latte_test_hook(std::string name) {
    name_ = name;
  }
  protected:
  
  virtual void operator()(std::string description, const latte_callback& hook) {
    description_ = description;
    this->operator()(hook);
  }

  virtual void operator()(const latte_callback& hook) {
    // Find the hook's call stack associated with the current describe()
    auto current_call_stack = call_stack.find(parent_depth());
    // We found the stack
    if (current_call_stack != call_stack.end()) {
      auto stack = current_call_stack->second;
      // Add the hook to the local stack
      stack.push_back(hook);
      // Update the local stack
      call_stack[parent_depth()] = stack;
    } else  {
      // Create the local stack
      std::vector<latte_callback> stack { hook };
      // Add the local stack
      call_stack[parent_depth()] = stack;
    }
  };

  virtual void operator() (int depth) {
    auto current_call_stack = call_stack.find(depth);
    if (current_call_stack != call_stack.end()) {
      std::vector<latte_callback> stack = current_call_stack->second;
      try {
        if (!stack.empty()) {
          // The function call is located at the end.
          auto function = stack.back();
          function();
        }
      }
      catch(const std::exception& e) {
        debug("[latte error::core::hook]: " + std::string(e.what()));
      }

    } else {
      // debug("---: couldn't find hook: " + name_);
    }
  }

  void clear(int depth) {
    auto current_call_stack = call_stack.find(depth);
    if (current_call_stack != call_stack.end()) {
      // Remove the function from the call stack
      if (!current_call_stack->second.empty()) {
        current_call_stack->second.pop_back();
      }
    }
  }
  
  std::string name_ = "";
  std::string description_ = "";

  private:
  int parent_depth_ = 0;
  std::unordered_map<int, std::vector<latte_callback>> call_stack;
  int parent_depth () {
    return _latte_state.depth();
  }
  
};

struct latte_before : public latte_test_hook {
  latte_before(): latte_test_hook("before()") {};
  
  virtual void operator()(std::string description, latte_callback&& hook) {
    latte_test_hook::operator()(description, hook);
  }

  virtual void operator()(latte_callback&& hook) {
    latte_test_hook::operator()(hook);
  };
  
  private:
  friend struct latte_describe;
  friend struct latte_it;
  
  virtual void operator() (int depth) {
    latte_test_hook::operator()(depth);
  }
};

struct latte_before_each : public latte_test_hook {
  latte_before_each(): latte_test_hook("before_each()") {};
  
  virtual void operator()(std::string description, latte_callback&& hook) {
    latte_test_hook::operator()(description, hook);
  }
  
  virtual void operator()(latte_callback&& hook) {
  latte_test_hook::operator()(hook);
  };
  
  private:
  friend struct latte_describe;
  friend struct latte_it;

  virtual void operator() (int depth) {
    latte_test_hook::operator()(depth);
  }
};

struct latte_after : public latte_test_hook {
  latte_after(): latte_test_hook("after()") {};
  
  virtual void operator()(std::string description, latte_callback&& hook) {
    latte_test_hook::operator()(description, hook);
  }

  virtual void operator()(latte_callback&& hook) {
    latte_test_hook::operator()(hook);
  };

  private:
  friend struct latte_describe;
  friend struct latte_it;

  virtual void operator() (int depth) {
    latte_test_hook::operator()(depth);
  }
};

struct latte_after_each: public latte_test_hook {
  latte_after_each(): latte_test_hook("after_each()") {};
  
  virtual void operator()(std::string description, latte_callback&& hook) {
    latte_test_hook::operator()(description, hook);
  }

  virtual void operator()(latte_callback&& hook) {
    latte_test_hook::operator()(hook);
  };

  private:
  friend struct latte_describe;
  friend struct latte_it;
  virtual void operator() (int depth) {
  latte_test_hook::operator()(depth);
  }
};
} // core
  
} // latte


#endif