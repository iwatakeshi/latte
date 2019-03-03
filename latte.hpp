#ifndef LATTE_H
#define LATTE_H
#include "include/latte_core.hpp"
#include "include/reporter/reporter.hpp"
#include "include/style/expect.hpp"
#include <functional>

namespace latte {
latte::core::latte_before before;
latte::core::latte_before_each before_each;
latte::core::latte_after after;
latte::core::latte_after_each after_each;
latte::core::latte_describe describe(
  &before,
  &after,
  &before_each,
  &after_each);
latte::core::latte_it it(&describe);

void runner(std::function<void()> test) {
  // Setup reporter
  latte::reporter::latte_reporter report = latte::reporter::latte_reporter();
  report();
  // Begin the test
  test();
};

void runner(int& argc, char** argv, std::function<void()> test) {
  // TODO: Add a command line parser similar to: https://stackoverflow.com/a/868894
  // Setup reporter
  latte::reporter::latte_reporter report = latte::reporter::latte_reporter();
  report();
  // Begin the test
  test();
};

} // latte

#endif
