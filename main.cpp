#include "latte.hpp"
using namespace latte;
using latte::style::expect;

int main() {
  describe([&] {
    core::debug("describe: A");

    before([&] {
      core::debug("before: A");
    });

    after([&] {
      core::debug("after: A");
    });

    before_each([&] {
      core::debug("before each: A");
    });

    it([&] {
      core::debug("it: A");
      expect(20).to->equal(20);
      expect(100).to->equal(100);
    });

    it([&] {
      core::debug("it: A - 2");
      // expect()
    });

    describe([&] {
      core::debug("describe: B");

      before([&] {
        core::debug("before: B");
      });

      after([&] {
        core::debug("after: B");
      });

      it.only([&] {
        core::debug("it: B");
      });

      it([&] {
        core::debug("it: B - 2");
      });
    });
  });

  return 0;
}