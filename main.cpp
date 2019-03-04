#include "latte.hpp"
#include <functional>
#include <string>
// using latte::before;
// using latte::after;
// using latte::before_each;
// using latte::after_each;
using latte::describe;
using latte::it;
using latte::style::expect;
std::string greet() {
  return "hey";
}

int gcd(int a, int b) {
  if (b == 0) {
    return a;
  }
  return gcd(b, a % b);
}

int main() {
  latte::runner([&]() {
    describe("hello world", [&] {
      it("should add 1 + 1 = 2", [&] {
        expect(1 + 1).to->equal(2);
      });

      describe("greet()", [&] {
        it("should greet politely", [&] {
          expect(greet()).to->equal("Hello");
        });
      });

      describe("oops", [&]() {
        it("should do something", [&] {
          expect(gcd(4, 6)).to->equal(2);
        });
        it("should do something again", [&] {
          expect(100).to->equal(400);
        });
      });

      describe("pending test suite");
      describe("make a pending test case", [&] {
        it("should have a pending test case");
      });
    });
  });

  return 0;
}