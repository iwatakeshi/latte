#ifndef LATTE_CORE_STATE
#define LATTE_CORE_STATE
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>
#include "latte_type.hpp"

namespace latte {
namespace core {
struct latte_state {
  std::unordered_map<int, 
  std::unordered_map<std::string, std::vector<type::latte_result_t>>
  > result_map_;
  int depth() {
    return describe_depth - 1;
  }
  void add_depth() {
    describe_depth += 1;
  }
  void remove_depth() {
    describe_depth -= 1;
  }
  private:
    int describe_depth = 0;
};

latte_state _latte_state;
} // core
} // latte

#endif