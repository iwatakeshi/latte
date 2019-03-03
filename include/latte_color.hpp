#ifndef LATTE_CORE_COLOR_H
#define LATTE_CORE_COLOR_H
#include <string>
namespace latte {
namespace color {

std::string reset(const std::string & input = "") {
  return "\033[0m" + input;
}

std::string create_pygment(int code, const std::string& input, bool foreground = true) {
  return "\033[" + std::to_string(foreground ? code : code + 10)+ "m " + input;
}

std::string create_bold(const std::string& input) {
  return "\033[1m" + input;
}

std::string create_underline(const std::string& input) {
  return "\033[4m" + input;
}

std::string create_reversed(const std::string& input) {
  return "\033[7m" + input;
}

std::string create_color(int code, const std::string& input, bool foreground = true, bool bold = false, bool underlined = false, bool reversed = false) {
  std::string string = create_pygment(code, input, foreground);
  if (bold) {
    string = create_bold(string);
  }

  if (underlined) {
    string = create_underline(string);
  }

  if (reversed) {
    string = create_reversed(string);
  }

  return string + reset();
}

std::string black(const std::string& input, bool foreground = true, bool bold = false, bool underlined = false, bool reversed = false) {
  return create_color(30, input, foreground, bold, underlined, reversed);
}

std::string red(const std::string& input, bool foreground = true, bool bold = false, bool underlined = false, bool reversed = false) {
  return create_color(31, input, foreground, bold, underlined, reversed);
};

std::string green(const std::string& input, bool foreground = true, bool bold = false, bool underlined = false, bool reversed = false) {
  return create_color(32, input, foreground, bold, underlined, reversed);
};

std::string yellow(const std::string& input, bool foreground = true, bool bold = false, bool underlined = false, bool reversed = false) {
  return create_color(33, input, foreground, bold, underlined, reversed);
}

std::string blue(const std::string& input, bool foreground = true, bool bold = false, bool underlined = false, bool reversed = false) {
  return create_color(34, input, foreground, bold, underlined, reversed);
}

std::string magenta(const std::string& input, bool forground = true) {
  return create_color(35, input, forground);
}

std::string cyan(const std::string& input, bool foreground = true, bool bold = false, bool underlined = false, bool reversed = false) {
  return create_color(36, input, foreground, bold, underlined, reversed);
};

std::string white(const std::string& input, bool foreground = true, bool bold = false, bool underlined = false, bool reversed = false) {
  return create_color(37, input, foreground, bold, underlined, reversed);
};

std::string bright_black(const std::string& input, bool foreground = true, bool bold = false, bool underlined = false, bool reversed = false) {
  return create_color(90, input, foreground, bold, underlined, reversed);
}

std::string bright_red(const std::string& input, bool foreground = true, bool bold = false, bool underlined = false, bool reversed = false) {
  return create_color(91, input, foreground, bold, underlined, reversed);
}

std::string bright_green(const std::string& input, bool foreground = true, bool bold = false, bool underlined = false, bool reversed = false) {
  return create_color(92, input, foreground, bold, underlined, reversed);
}

std::string bright_yellow(const std::string& input, bool foreground = true, bool bold = false, bool underlined = false, bool reversed = false) {
  return create_color(93, input, foreground, bold, underlined, reversed);
}

std::string bright_blue(const std::string& input, bool foreground = true, bool bold = false, bool underlined = false, bool reversed = false) {
  return create_color(94, input, foreground, bold, underlined, reversed);
}

std::string bright_magenta(const std::string& input, bool foreground = true, bool bold = false, bool underlined = false, bool reversed = false) {
  return create_color(95, input, foreground, bold, underlined, reversed);
}

std::string bright_cyan(const std::string& input, bool foreground = true, bool bold = false, bool underlined = false, bool reversed = false) {
  return create_color(96, input, foreground, bold, underlined, reversed);
}

std::string bright_white(const std::string& input, bool foreground = true, bool bold = false, bool underlined = false, bool reversed = false) {
  return create_color(97, input, foreground, bold, underlined, reversed);
}
} // color
} // latte

#endif
