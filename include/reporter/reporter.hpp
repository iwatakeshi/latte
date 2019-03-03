#ifndef LATTE_REPORTER_H
#define LATTE_REPORTER_H
#include "spec.hpp"
#include <thread>
namespace latte {
namespace reporter {
struct latte_reporter {
  void operator()() {
    reporter_spec spec;
    spec();
  }
};
}
}
#endif