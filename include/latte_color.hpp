#ifndef LATTE_CORE_COLOR_H
#define LATTE_CORE_COLOR_H
#include <string>
namespace latte {
namespace color {

std::string create_color(int code, std::string input, bool forground = true) {
  return std::string("\033[" + std::to_string(forground ? code : code + 10) + ";1m" + input + "\033[0m");
}

std::string black(std::string input, bool foreground = true) {
  return create_color(30, input, foreground);
}

std::string red(std::string input, bool foreground = true) {
  return create_color(31, input, foreground);
};

std::string green(std::string input, bool foreground = true) {
  return create_color(32, input, foreground);
};

std::string yellow(std::string input, bool foreground = true) {
  return create_color(33, input, foreground);
}

std::string blue(std::string input, bool foreground = true) {
  return create_color(34, input, foreground);
}

std::string magenta(std::string input, bool forground = true) {
  return create_color(35, input, forground);
}

std::string cyan(std::string input, bool foreground = true) {
  return create_color(36, input, foreground);
};

std::string white(std::string input, bool foreground = true) {
  return create_color(37, input, foreground);
};

std::string bright_black(std::string input, bool foreground = true) {
  return create_color(90, input, foreground);
}

std::string bright_red(std::string input, bool foreground = true) {
  return create_color(91, input, foreground);
}

std::string bright_green(std::string input, bool foreground = true) {
  return create_color(92, input, foreground);
}

std::string bright_yellow(std::string input, bool foreground = true) {
  return create_color(93, input, foreground);
}

std::string bright_blue(std::string input, bool foreground = true) {
  return create_color(94, input, foreground);
}

std::string bright_magenta(std::string input, bool foreground = true) {
  return create_color(95, input, foreground);
}

std::string bright_cyan(std::string input, bool foreground = true) {
  return create_color(96, input, foreground);
}

std::string bright_white(std::string input, bool foreground = true) {
  return create_color(97, input, foreground);
}
} // color
} // latte

#endif
