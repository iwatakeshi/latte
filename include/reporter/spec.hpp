#ifndef LATTE_REPORTER_SPEC_H
#define LATTE_REPORTER_SPEC_H
#include "../latte_color.hpp"
#include "../latte_core_event.hpp"
#include "../latte_type.hpp"
#include <iostream>
#include <list>
#include <string>
#include <tuple>
#include <vector>

namespace latte {
namespace reporter {
// Probably a struct is better.
// Then just overload the () operator

struct reporter_spec {
  reporter_spec() {
    operator()();
  }
  void operator()() {
    using core::debug;
    using core::latte_describe_result;
    using core::latte_result_state;
    using core::event::describe_event_test_end;
    using core::event::describe_event_test_result;
    using core::event::describe_event_test_start;
    using core::event::latte_describe_emitter;

    std::vector<std::string> test;

    latte_describe_emitter.on(
      describe_event_test_result,
      [&](std::list<latte_describe_result> test_case) mutable {
        auto describe = test_case.front();
        std::cout << color::white(describe.description()) << std::endl;
        int count = 0;
        std::vector<std::tuple<std::string, std::string>> local;
        for (auto it : describe.results()) {
          std::string description = it.description();
          switch (it.state()) {
          case latte_result_state::passing:
            description = color::green("✓ ") + description;
            passing += 1;
            break;
          case latte_result_state::pending:
            description = description;
            pending += 1;
            break;
          default:
            description = color::red(std::to_string(count) + ") " + description);
            failing += 1;
            break;
          }
          debug(it.depth_string() + description);
        }
        count++;
        // test.push_back("");
      });

    latte_describe_emitter.on(
      describe_event_test_end,
      [&](std::list<latte_describe_result> test_cases) mutable {
        if (failing > 0) {
          debug(color::red(std::to_string(failing) + " out of " + std::to_string(failing + passing) + " failed") + ":");
          for (auto&& describe : test_cases) {
            int count = 0;
            for (auto it : describe.results()) {
              if (it.is_failing()) {
                debug(color::white(std::to_string(count) + ") " + it.description()) + " : " + color::red(it.message()));
              }
              count++;
            }
          }
          return;
        }
        debug(std::to_string(failing + passing) + " completed.");
      });
    // std::cout << test->size() << std::endl;
  }

  private:
  int passing = 0;
  int pending = 0;
  int failing = 0;
};
} // reporter
} // latte

#endif