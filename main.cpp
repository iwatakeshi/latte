#include "latte.hpp"
#include <functional>
#include <list>
#include <vector>
using latte::after;
using latte::after_each;
using latte::before;
using latte::before_each;
using latte::describe;
using latte::it;
using latte::style::expect;

int main() {
  latte::runner([&]() {
    describe("Hello world", [&] {
      it("should do something", [&] {
        expect(20).to->equal(20);
        expect(100).to->equal(500);
      });

      describe("What! Cool!", [&] {
        it("should do something 2", [&] {

        });
      });

      describe("Test", [&]() {
        it("should do something 3", [&] {

        });
        describe("Test again!", [&] () {

        });
      });
    });
  });

  return 0;
}