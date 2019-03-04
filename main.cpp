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
    describe("hello world", [&] {
      it("should do something", [&] {
        expect(20).to->equal(20);
        expect(100).to->equal(500);
      });

      describe("what! cool!", [&] {
        it("should do something 2", [&] {
          expect(100).to->equal(20);
        });
      });

      describe("test", [&]() {
        it("should do something 3", [&] {
          expect(100).to->equal(100);
        });
        it("test again!", [&] {
          expect(100).to->equal(100);
        });
      });

      describe("pending test suite.");
      describe("test 2", [&] {
        it("pending test case");
      });
    });
  });

  return 0;
}