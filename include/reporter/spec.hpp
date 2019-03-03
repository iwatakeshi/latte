#ifndef LATTE_REPORTER_SPEC_H
#define LATTE_REPORTER_SPEC_H
#include "../latte_color.hpp"
#include "../latte_core_debug.hpp"
#include "../latte_core_event.hpp"
#include "../latte_core_result.hpp"
#include <functional>
#include <iostream>
#include <list>
#include <mutex>
#include <string>
#include <tuple>
#include <vector>

namespace latte {
namespace reporter {

struct reporter_spec {
  reporter_spec(){};

  void operator()() {

    using latte::core::debug;
    using latte::core::latte_describe_result;
    using latte::core::latte_result_state;
    using latte::core::event::describe_event_test_end;
    using latte::core::event::describe_event_test_result;
    using latte::core::event::describe_event_test_start;
    using latte::core::event::latte_describe_emitter;
    using namespace latte::color;
    latte_describe_emitter.on(
      describe_event_test_result,
      std::function<void(std::list<std::shared_ptr<latte_describe_result>>)>(process_test_suite));

    latte_describe_emitter.on(
      describe_event_test_end,
      std::function<void(std::list<std::shared_ptr<latte_describe_result>>)>(process_completed));
  }

  static void process_test_suite(std::list<std::shared_ptr<latte::core::latte_describe_result>> current_test_suite) {
    using latte::core::debug;
    using latte::core::latte_describe_result;
    using latte::core::latte_result_state;
    using latte::core::event::describe_event_test_end;
    using latte::core::event::describe_event_test_result;
    using latte::core::event::describe_event_test_start;
    using latte::core::event::latte_describe_emitter;
    using namespace latte::color;

    auto test_suite = current_test_suite.front();
    auto describe_description = test_suite->description();
    std::cout << white(describe_description) << std::endl;
    int failed_counts = 0;
    for (auto test_case : test_suite->results()) {
      std::string description = test_case->description();
      switch (test_case->state()) {
      case latte_result_state::passing:
        description = green("✓ ") + description;
        break;
      case latte_result_state::pending:
        description = description;
        description = cyan(description);
        break;
      default:
        description = red(std::to_string(failed_counts++) + ") " + description);
        break;
      }
      debug(test_case->depth_string() + description);
    }
  }

  static void process_completed(std::list<std::shared_ptr<latte::core::latte_describe_result>> test_suites) {

    using latte::core::debug;
    using latte::core::latte_describe_result;
    using latte::core::latte_result_state;
    using latte::core::event::describe_event_test_end;
    using latte::core::event::describe_event_test_result;
    using latte::core::event::describe_event_test_start;
    using latte::core::event::latte_describe_emitter;
    using namespace latte::color;

    std::vector<std::shared_ptr<latte_describe_result>> passing_test_suites;
    std::vector<std::shared_ptr<latte_describe_result>> failing_test_suites;
    std::vector<std::shared_ptr<latte_describe_result>> pending_test_suites;
    int marker_count = 0;
    int passing_count = 0;
    int failing_count = 0;
    int pending_count = 0;
    double total_time = 0;
    for (auto test_suite : test_suites) {
      if (test_suite->is_passing()) {
        passing_count += test_suite->results().size();
        passing_test_suites.push_back(test_suite);
      }

      if (test_suite->is_failing()) {
        failing_count += test_suite->results().size();
        failing_test_suites.push_back(test_suite);
      }
      // Note: These are pending tests for test suites and not for test cases!
      if (test_suite->is_pending()) {
        pending_count += test_suite->results().size();
        pending_test_suites.push_back(test_suite);
      }
      total_time += test_suite->time();
    }

    int total_tests = failing_count + passing_count + pending_count;

    debug("");

    if (failing_test_suites.size() > 0) {

      debug(red(std::to_string(failing_count) + " out of " + std::to_string(total_tests) + " tests failed") + ":" + "\n");
      for (auto test_suite : failing_test_suites) {
        int failed_count = 0;
        for (auto test_case : test_suite->results()) {
          debug(white(std::to_string(failed_count) + ") " + test_case->description()) + " : " + red(test_case->message()) + "\n");
          failed_count++;
        }
      }
    } else {
      debug(green(std::to_string(total_tests) + " tests completed " + "(" + std::to_string(total_time) + ")"));
    }
  }
};
} // reporter
} // latte

#endif