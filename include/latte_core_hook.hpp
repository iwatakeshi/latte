#ifndef LATTE_CORE_HOOK_H
#define LATTE_CORE_HOOK_H
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "latte_core_state.hpp"
#include "latte_type.hpp"

namespace latte {
namespace core {

using type::latte_callback;

void debug(std::string message) {
  std::cout << message << std::endl;
}

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
    // depth_ += 1;
  };

  virtual void operator() (int depth) {
    auto current_call_stack = call_stack.find(depth);
    if (current_call_stack != call_stack.end()) {
      std::vector<latte_callback> stack = current_call_stack->second;
      try {
        if (!stack.empty()) {
    
          auto function = stack.back();
          function();
          // debug("finished calling hook: " + name_);
        }
      }
      catch(const std::exception& e) {
        debug("[latte error::core::hook]: " + std::string(e.what()));
      }

    } else {
      // debug("---: couldn't find hook: " + name_);
    }
    // depth_ -= 1;
  }

  void clear(int depth) {
    auto current_call_stack = call_stack.find(depth);
    if (current_call_stack != call_stack.end()) {
      // Remove the function from the call stack
      if (!current_call_stack->second.empty()) {
        current_call_stack->second.pop_back();
      }
    }
    // depth_ = 0;
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

struct latte_before : latte_test_hook {
  latte_before(): latte_test_hook("before()") {};
  
  void operator()(std::string description, latte_callback&& hook) {
    latte_test_hook::operator()(description, hook);
  }

  void operator()(latte_callback&& hook) {
    latte_test_hook::operator()(hook);
  };
  
  private:
  friend struct latte_describe;
  friend struct latte_it;
  void operator() (int depth) {
    latte_test_hook::operator()(depth);
  }
};

struct latte_before_each : latte_test_hook {
  latte_before_each(): latte_test_hook("before_each()") {};
  
  void operator()(std::string description, latte_callback&& hook) {
    latte_test_hook::operator()(description, hook);
  }
  
  void operator()(latte_callback&& hook) {
  latte_test_hook::operator()(hook);
  };
  
  private:
  friend struct latte_describe;
  friend struct latte_it;
  void operator() (int depth) {
    latte_test_hook::operator()(depth);
  }
};

struct latte_after : latte_test_hook {
  latte_after(): latte_test_hook("after()") {};
  
  void operator()(std::string description, latte_callback&& hook) {
    latte_test_hook::operator()(description, hook);
  }

  void operator()(latte_callback&& hook) {
    latte_test_hook::operator()(hook);
  };
  void operator() (int depth) {
    latte_test_hook::operator()(depth);
  }
  private:
  friend struct latte_describe;
  friend struct latte_it;
};

struct latte_after_each: latte_test_hook {
  latte_after_each(): latte_test_hook("after_each()") {};
  
  void operator()(std::string description, latte_callback&& hook) {
    latte_test_hook::operator()(description, hook);
  }

  void operator()(latte_callback&& hook) {
    latte_test_hook::operator()(hook);
  };

  private:
  friend struct latte_describe;
  friend struct latte_it;
  void operator() (int depth) {
  latte_test_hook::operator()(depth);
  }
};
} // core
  
} // latte


#endif