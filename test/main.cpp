#include <string>
#include "../latte.hpp"
using latte::after;
using latte::after_each;
using latte::before;
using latte::before_each;
using latte::describe;
using latte::it;
using latte::core::debug;
using latte::style::expect;

struct dummy_struct {
  dummy_struct() {};
  dummy_struct(int n) :
      num(n) {};

  bool operator==(const dummy_struct& right) {
    return this->num == right.num;
  }

  int get_num() const {
    return num;
  }

  private:
  int num = 0;
};

std::string to_string(dummy_struct const&) { return "dummy_struct"; }

int main() {
  latte::runner([] {
    describe("latte", [&]() {
      describe("api", [&]() {
        describe("equal", [&] {
          describe("comparison of type T and T", [&] {
            it("should: 1 == 1", [&]() {
              expect(1).to->equal(1);
            });

            it("should: 1 != 2", [&]() {
              expect(1).to->never->equal(2);
            });

            it("should: 1.5 == 1.5", [&]() {
              expect(1.5).to->equal(1.5);
            });

            it("should: 1.5 != 2.5", [&]() {
              expect(1.5).to->never->equal(2.5);
            });

            it("should: true == true", [&]() {
              expect(true).to->equal(true);
            });

            it("should: true != false", [&]() {
              expect(true).to->never->equal(false);
            });

            it("should: 'a' == 'a'", [&]() {
              expect('a').to->equal('a');
            });

            it("should: 'a' != 'b'", [&]() {
              expect('a').to->never->equal('b');
            });

            it("should: \"true\" == \"true\"", [&]() {
              expect("true").to->eql("true");
            });

            it("should: \"true\" != \"false\"", [&]() {
              expect("true").to->never->equal("false");
            });

            it("should: \"true\" == \"true\"", [&]() {
              std::string a = "true";
              std::string b = "true";
              expect(a).to->equal(b);
            });

            it("should: \"true\" != \"false\"", [&]() {
              std::string a = "true";
              std::string b = "false";
              expect(a).to->never->equal(b);
            });

            it("should: dummy_struct() == dummy_struct()", [&]() {
              expect(dummy_struct()).to->equal(dummy_struct());
            });
          }); // end - equal: comparison of type T and T

          describe("comparison of type T and U", [&] {
            it("should: true != 1", [&]() {
              expect(true).to->never->strict_equal(1);
            });

            it("should: 1 != 1.0", [&]() {
              expect(1).to->never->strict_equal(1.0);
            });

            it("should: 1 != \"1\"", [&]() {
              std::string b = "1";
              expect(1).to->never->strict_equal(b);
            });

            it("should: 1.7 != 2", [&]() {
              expect(1.7).to->never->strict_equal(2);
            });

            it("should: 1.7 != \"1.7\"", [&]() {
              expect(1.7).to->never->strict_equal("1.7");
            });

            it("should: 1.7 != 'a'", [&]() {
              expect(1.7).to->never->strict_equal('a');
            });

            it("should: 'a' != \"a\"", [&]() {
              expect('a').to->never->strict_equal("a");
            });
          }); // end - equal comparison of type T and U
        });

        describe("equal (using comparator)", [&]() {
          it("should: dummy_struct(1).get_num() == 1", [&]() {
            expect(dummy_struct(1)).to->equal(1, [&](dummy_struct a, auto b) -> bool {
              return a.get_num() == b;
            });
          });
        });

        describe("strict_equal", [&] {
          describe("comparison of type T and T", [&] {
            it("should: 1 == 1", [&]() {
              expect(1).to->strict_equal(1);
            });

            it("should: 1 != 2", [&]() {
              expect(1).to->never->strict_equal(2);
            });

            it("should: 1.5 == 1.5", [&]() {
              expect(1.5).to->strict_equal(1.5);
            });

            it("should: 1.5 != 2.5", [&]() {
              expect(1.5).to->never->strict_equal(2.5);
            });

            it("should: true == true", [&]() {
              expect(true).to->strict_equal(true);
            });

            it("should: true != false", [&]() {
              expect(true).to->never->strict_equal(false);
            });

            it("should: 'a' == 'a'", [&]() {
              expect('a').to->strict_equal('a');
            });

            it("should: 'a' != 'b'", [&]() {
              expect('a').to->never->strict_equal('b');
            });

            it("should: \"true\" == \"true\"", [&]() {
              expect("true").to->strict_equal("true");
            });

            it("should: \"true\" != \"false\"", [&]() {
              expect("true").to->never->strict_equal("false");
            });

            it("should: \"true\" == \"true\"", [&]() {
              std::string a = "true";
              std::string b = "true";
              expect(a).to->strict_equal(b);
            });

            it("should: \"true\" != \"false\"", [&]() {
              std::string a = "true";
              std::string b = "false";
              expect(a).to->never->strict_equal(b);
            });

            it("should: dummy_struct() == dummy_struct()", [&]() {
              expect(dummy_struct()).to->strict_equal(dummy_struct());
            });
          }); // end - equal: comparison of type T and T

          describe("comparison of type T and U", [&] {
            it("should: true == 1", [&]() {
              expect(true).to->never->strict_equal(1);
            });

            it("should: 1 == 1.0", [&]() {
              expect(1).to->never->strict_equal(1.0);
            });

            it("should: 1 == \"1\"", [&]() {
              std::string b = "1";
              expect(1).to->never->strict_equal(b);
            });

            it("should: 1.7 == 2", [&]() {
              expect(1.7).to->never->strict_equal(2);
            });

            it("should: 1.7 == \"1.7\"", [&]() {
              expect(1.7).to->never->strict_equal("1.7");
            });

            it("should: 1.7 != 'a'", [&]() {
              expect(1.7).to->never->strict_equal('a');
            });

            it("should: 'a' == \"a\"", [&]() {
              expect('a').to->never->strict_equal("a");
            });
          }); // end - equal comparison of type T and U
        });

        describe("strict_equal (using comparator)", [&]() {
          it("should: dummy_struct(1).get_num() == 1", [&]() {
            expect(dummy_struct(1)).to->equal(1, [&](dummy_struct a, auto b) -> bool {
              return a.get_num() == b;
            });
          });
        });
      });
    });
  });

  return 0;
}