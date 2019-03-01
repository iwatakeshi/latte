load('//:buckaroo_macros.bzl', 'buckaroo_deps')

prebuilt_cxx_library(
  name = 'latte',
  header_only = True,
  header_namespace = '',
  exported_headers = [
    'include/latte_core_comparator.hpp',
    'include/latte_core_event_emitter.hpp',
    'include/latte_core_exception.hpp',
    'include/latte_core_hook.hpp',
    'include/latte_core_result.hpp',
    'include/latte_core_state.hpp',
    'include/latte_core.hpp',
    'include/latte_type.hpp',
    'include/style/expect.hpp',
    'latte.hpp',
  ],
  licenses = [
    'LICENSE',
  ], 
  visibility = [
    'PUBLIC',
  ],
  deps = buckaroo_deps()
)

cxx_binary(
  name = 'main',
  srcs = [
    'main.cpp',
  ],
  deps = [
    '//:latte',
  ] + buckaroo_deps(),
)

cxx_test(
  name = 'test',
  raw_headers = [
    'include/latte_core_comparator.hpp',
    'include/latte_core_event_emitter.hpp',
    'include/latte_core_exception.hpp',
    'include/latte_core_hook.hpp',
    'include/latte_core_result.hpp',
    'include/latte_core_state.hpp',
    'include/latte_core.hpp',
    'include/latte_type.hpp',
    'include/style/expect.hpp',
    'latte.hpp',
  ],
  srcs = [
    'test/main.cpp',
  ],
  deps = buckaroo_deps()
)