#include "xnu-nolibc/xnu-nolibc.hpp"

using namespace XnuNoLibc;

extern "C" [[gnu::noreturn]]
void _start(void) {
    __exit(0);
}

extern "C" [[gnu::noreturn]]
void _start_raw(void) {
    __exit_raw(0);
}
