#ifndef LATTE_H
#define LATTE_H
#include "include/reporter/reporter.hpp"
#include "include/style/expect.hpp"
#include "include/latte_core.hpp"


namespace latte {
// Setup reporter before anything!
latte::reporter::reporter_spec spec = latte::reporter::reporter_spec();
latte::core::latte_before before;
latte::core::latte_before_each before_each;
latte::core::latte_after after;
latte::core::latte_after_each after_each;
latte::core::latte_describe describe(&before, &after, &before_each, &after_each, &core::event::latte_describe_emitter);
latte::core::latte_it it(&describe);
} // latte

#endif
