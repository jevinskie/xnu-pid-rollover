#include "xnu-nolibc/xnu-nolibc.hpp"
#include "common-internal.hpp"

#include <sys/syscall.h>

namespace XnuNoLibc {

void __exit(int status) {}

void __exit_raw(int status) {
    register int _status __asm("w0") = status;
    __asm__ __volatile__("mov x16, %[syscall_num]\n\t"
                         "svc #0x80"
                         : "=r"(_status)
                         : [syscall_num] "I"(SYS_exit)
                         : "x1", "cc");
    // __asm __volatile (
    //     "mov x16, %[syscall_num]\n\t"
    //     "svc #0x80\n\t"
    //     : "=r" (_status) /* outputs */
    //     : [syscall_num] "I"(SYS_exit)
    //     :
    // );
    XNU_NOLIBC_UNREACHABLE();
}

} // namespace XnuNoLibc
