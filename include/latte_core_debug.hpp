#ifndef LATTE_CORE_DEBUG_H
#define LATTE_CORE_DEBUG_H
#include <iostream>
#include <string>

namespace latte {
namespace core {

void debug(std::string message = "") {
  std::cout << message << std::endl;
};

#ifdef _WIN32
#include <fcntl.h>
#include <io.h>

std::wstring string_to_wstring(const std::string& s) {
  std::wstring temp(s.length(), L' ');
  std::copy(s.begin(), s.end(), temp.begin());
  return temp;
}

std::string wstring_to_string(const std::wstring& s) {
  std::string temp(s.length(), ' ');
  std::copy(s.begin(), s.end(), temp.begin());
  return temp;
}

void debug(std::wstring message = L"") {
  _setmode(_fileno(stdout), _O_U16TEXT)
      std::wcout
    << message << std::endl;
};

void debug(std::string message = "") {
  debug(string_to_wstring(message));
};

#else

void debug(std::wstring message = L"") {
  std::wcout << message << std::endl;
};
#endif

} // core

} // latte

#endif