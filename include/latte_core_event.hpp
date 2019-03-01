#ifndef LATTE_CORE_EVENT_H
#define LATTE_CORE_EVENT_H
#include "latte_core_event_emitter.hpp"
namespace latte {
namespace core {
namespace event {

enum latte_event {
  describe_event_test_start,
  describe_event_test_result,
  describe_event_test_end
};

emitter::latte_event_emitter latte_describe_emitter;
emitter::latte_event_emitter latte_it_emitter;
emitter::latte_event_emitter latte_result_emitter;

} // event
} // core
} // latte
#endif
