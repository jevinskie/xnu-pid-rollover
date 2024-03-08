#pragma once

#include "common.hpp"

namespace XnuNoLibc {

[[gnu::visibility("default"), gnu::always_inline, gnu::naked, noreturn]] void __exit(int status);
[[gnu::visibility("default"), gnu::always_inline, noreturn]] void __exit_raw(int status);

} // namespace XnuNoLibc
