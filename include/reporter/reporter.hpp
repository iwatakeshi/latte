#ifndef LATTE_REPORTER_H
#define LATTE_REPORTER_H
#include "spec.hpp"
#include "tap.hpp"
#include <thread>
namespace latte {
namespace reporter {
struct latte_reporter {
  void operator()() {
    // reporter_spec spec;
    // spec();
    reporter_tap tap;
    tap();
  }
};
}
}
#endif