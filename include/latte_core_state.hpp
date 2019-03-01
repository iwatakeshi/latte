#ifndef LATTE_CORE_STATE_H
#define LATTE_CORE_STATE_H
#include "latte_type.hpp"
#include <string>
#include <vector>

namespace latte {
namespace core {
 namespace state {
  struct latte_state {
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
 }

 state::latte_state _latte_state;
} // core
} // latte

#endif