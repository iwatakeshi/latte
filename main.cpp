#include "latte.hpp"
using latte::after;
using latte::after_each;
using latte::before;
using latte::before_each;
using latte::describe;
using latte::it;
using latte::core::debug;
using latte::style::expect;

int main() {
  describe("Hello world", [&] {
    
    it("should do something", [&] {
      expect(20).to->equal(20);
      expect(100).to->equal(500);
    });

    it("should do something 2", [&] {

    });

    describe("Nothing here", [&] {
      // debug("describe: B");

      before("", [&] {
        // debug("before: B");
      });

      after("", [&] {
        // debug("after: B");
      });

      it("should do something 3", [&] {
        // debug("it: B");
      });

      it("should domething 4", [&] {
        // debug("it: B - 2");
      });
    });
  });

  return 0;
}