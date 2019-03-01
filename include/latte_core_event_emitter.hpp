#ifndef LATTE_CORE_EVENT_EMITTER_H
#define LATTE_CORE_EVENT_EMITTER_H
//
// Copyright (c) 2014 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
#include "latte_core_debug.hpp"
#include "latte_core_comparator.hpp"
#include <algorithm>
#include <functional>
#include <list>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>
using std::to_string;
namespace latte {
namespace core {
namespace emitter {

struct latte_event_emitter {
  latte_event_emitter()
      : last_listener(0) {}

  ~latte_event_emitter() {
    for (auto&& i : listeners) {
      for (auto&& j : i.second) {
        delete j;
      }
      i.second.clear();
    }

    listeners.clear();
  }

  template <typename... Args>
  void add_listener(int event_id, std::function<void(Args...)> cb) {
    if (!cb) {
      throw std::invalid_argument("latte_event_emitter::add_listener: No callbak provided.");
    }

    std::lock_guard<std::mutex> lock(mutex);
    listeners[event_id].push_back(new Listener<Args...>(cb));
  }

  void add_listener(int event_id, std::function<void()> cb) {
    if (!cb) {
      throw std::invalid_argument("latte_event_emitter::add_listener: No callbak provided.");
    }

    std::lock_guard<std::mutex> lock(mutex);

    listeners[event_id].push_back(new Listener<>(cb));
  }

  template <typename LambdaType>
  void add_listener(int event_id, LambdaType lambda) {
    add_listener(event_id, make_function(lambda));
  }

  template <typename... Args>
  void on(int event_id, std::function<void(Args...)> cb) {
    add_listener(event_id, cb);
  }

  void on(int event_id, std::function<void()> cb) {
    add_listener(event_id, cb);
  }

  template <typename LambdaType>
  void on(int event_id, LambdaType lambda) {
    return on(event_id, make_function(lambda));
  }

  void remove_listeners(int event_id) {
    std::lock_guard<std::mutex> lock(mutex);
    auto observers = listeners[event_id];
    if (observers.begin() != observers.end()) {
      observers.clear();
    }
  }

  template <typename... Args>
  void emit(int event_id, Args... args) {
    std::vector<Listener<Args...>> handlers;

    {
      std::lock_guard<std::mutex> lock(mutex);
      handlers.resize(listeners[event_id].size());

      for(auto* listener : listeners[event_id]) {
        Listener<Args...>* observer = dynamic_cast<Listener<Args...>*>(listener);
        observer->cb(args...);
      }
    }
  }

  private:
  struct ListenerBase {
    ListenerBase() {}

    virtual ~ListenerBase() {}
  };

  template <typename... Args>
  struct Listener : public ListenerBase {
    Listener() {}
    Listener(std::function<void(Args...)> c)
        : cb(c) {}
    ~Listener() {}
    std::function<void(Args...)> cb;
    Listener<Args...>& operator=(Listener<Args...>& right) {
      this->cb = right.cb;
      return* this;
    }

    Listener<Args...>& operator=(const Listener<Args...>& right) {
      this->cb = right.cb;
      return* this;
    }
  };

  std::mutex mutex;
  int last_listener;
  std::unordered_map<int, std::vector<ListenerBase*>> listeners;

  latte_event_emitter(const latte_event_emitter&) = delete;
  const latte_event_emitter& operator=(const latte_event_emitter&) = delete;

  // http://stackoverflow.com/a/21000981
  template <typename T>
  struct function_traits
      : public function_traits<decltype(&T::operator())> {};

  template <typename ClassType, typename ReturnType, typename... Args>
  struct function_traits<ReturnType (ClassType::*)(Args...) const> {
    typedef std::function<ReturnType(Args...)> f_type;
  };
  
  template <typename ClassType, typename ReturnType, typename... Args>
  struct function_traits<ReturnType (ClassType::*)(Args...)> {
    typedef std::function<ReturnType(Args...)> f_type;
  };

  template <typename L>
  typename function_traits<L>::f_type make_function(L l) {
    return (typename function_traits<L>::f_type)(l);
  }
}; // latte_event_emitter
} // emitter
} // core
} // latt/e

#endif