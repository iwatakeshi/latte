#ifndef LATTE_CORE_OPTIONS_H
#define LATTE_CORE_OPTIONS_H
#include <string>
namespace latte {
namespace core {
namespace options {
  struct latte_core_options {
    std::string indentation = "  ";
    bool use_color = true;
  };
} // options


  options::latte_core_options latte_options;
} // core

  
} // latte


#endif