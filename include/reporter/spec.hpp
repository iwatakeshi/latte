#ifndef LATTE_REPORTER_SPEC_H
#define LATTE_REPORTER_SPEC_H
#include "../latte_color.hpp"
#include "../latte_core_debug.hpp"
#include "../latte_core_event.hpp"
#include "../latte_core_result.hpp"
#include "../latte_type.hpp"
#include <functional>
#include <iostream>
#include <list>
#include <mutex>
#include <string>
#include <tuple>
#include <vector>

namespace {

using namespace latte::core::event;
using namespace latte::color;
using latte::core::debug;
using latte::core::latte_describe_result;
using latte::core::latte_it_result;
using latte::core::latte_result_state;
using describe_results_t = latte::type::latte_results_t<latte_describe_result>;
using it_result_t = latte::type::latte_result_t<latte_it_result>;
}

namespace latte {
namespace reporter {
static int test_suite_failed_count = 0;
struct reporter_spec {
  reporter_spec() {};

  void operator()() {
    latte_describe_emitter.on(
      describe_event_test_result,
      std::function<void(describe_results_t)>(process_test_suite));

    latte_describe_emitter.on(
      describe_event_test_end,
      std::function<void(describe_results_t)>(process_completed));
  }

  static void process_test_suite(describe_results_t current_test_suite) {
    auto test_suite = current_test_suite.front();
    auto describe_description = test_suite->description();
    describe_description = test_suite->is_pending() ? cyan(describe_description) : white(describe_description);
    std::cout << test_suite->depth_string() + describe_description << std::endl;
    for (auto test_case : test_suite->results()) {
      std::string description = test_case->description();
      switch (test_case->state()) {
      case latte_result_state::passing:
        description = green("✓") + " " + description;
        break;
      case latte_result_state::pending:
        description = cyan(description);
        break;
      default:
        description = red(std::to_string(test_suite_failed_count++) + ") " + description);
        break;
      }
      debug(test_case->depth_string() + description);
    }
  }

  static void process_completed(describe_results_t test_suites) {
    // describe_results_t passing_test_suites;
    describe_results_t failing_test_suites;
    // describe_results_t pending_test_suites;
    int passing_count = 0;
    int failing_count = 0;
    int pending_count = 0;
    double total_time = 0;
    for (auto test_suite : test_suites) {

      if (test_suite->is_failing()) {
        failing_test_suites.push_back(test_suite);
      }

      passing_count += filter(test_suite->results(), [](it_result_t result) {
        return result->is_passing();
      }).size();

      failing_count += filter(test_suite->results(), [](it_result_t result) {
        return result->is_failing();
      }).size();
      // Note: These are pending tests for test suites and not for test cases!
      pending_count += filter(test_suite->results(), [](it_result_t result) {
        return result->is_pending();
      }).size();
      total_time += test_suite->time();
    }

    int total_tests = failing_count + passing_count + pending_count;

    debug("");

    if (failing_test_suites.size() > 0) {

      debug(red(std::to_string(failing_count) + " out of " + std::to_string(total_tests) + " tests failed") + ":" + "\n");
      int failed_count = 0;
      for (auto test_suite : failing_test_suites) {
        for (auto test_case : test_suite->results()) {
          if (test_case->is_failing()) {
            debug(white(std::to_string(failed_count) + ") " + test_case->description()) + " : " + red(test_case->error().what()) + "\n");
            failed_count++;
          }
        }
      }
    } else {
      debug(green(std::to_string(total_tests) + " tests completed " + "(" + std::to_string(total_time) + ")"));
    }
  }

  //https://stackoverflow.com/a/53268928/1251031
  template <typename T, typename U>
  static T filter(const T& container, U predicate) {
    T result;
    std::copy_if(container.begin(), container.end(), std::back_inserter(result), predicate);
    return result;
  }
};
} // reporter
} // latte

#endif