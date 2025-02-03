#pragma once

// NOTE: Include this header in `.cpp` files that correspond with header-only classes. 
// NOTE: When linking with `ar`, the linker will complain about `.o` files that are empty and have no symbols. If you
// include this header in (#include <AllegroFlare/HeaderOnly.hpp>) in the `.cpp` file, it will remove the warnings.

static inline void dummy_function() __attribute__((used));
static inline void dummy_function() {}

