#include "../latte.hpp"
using latte::style::expect;
using latte::describe;
using latte::it;
using latte::core::debug;
using latte::before;
using latte::after;
using latte::before_each;
using latte::after_each;

int main() {
  describe("Hello world", [&] {
    it("should do something", [&] {
      expect(20).to->equal(20);
      expect(100).to->equal(100);
    });

    it("should do something 2", [&] {
  
    });

    // describe([&] {
    //   // debug("describe: B");

    //   before([&] {
    //     // debug("before: B");
    //   });

    //   after([&] {
    //     // debug("after: B");
    //   });

    //   it.only([&] {
    //     // debug("it: B");
    //   });

    //   it([&] {
    //     // debug("it: B - 2");
    //   });
    // });
  });

  return 0;
}