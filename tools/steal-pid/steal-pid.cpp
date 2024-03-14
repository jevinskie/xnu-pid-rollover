#include <cerrno>
#include <climits>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/stat.h>
#include <unistd.h>

#include <fileperm/fileperm.hpp>
#include <xnu-nolibc/xnu-nolibc.hpp>

static int takeover(uint8_t num_threads, pid_t victim_pid, const char *takeover_exe_cstr) {
    if (victim_pid > XnuNoLibc::XNU_PID_MAX) {
        fprintf(stderr, "Victim PID '%d' cant be greater than MAX_PID '%d'!", victim_pid,
                XnuNoLibc::XNU_PID_MAX);
        return 1;
    }

    if (const auto res = FilePerm::check_executable(takeover_exe_cstr)) {
        fprintf(stderr, "Takeover exe '%s' is not executable!\n", takeover_exe_cstr);
        return 2;
    }

    const auto my_pid = getpid();
    fprintf(stderr,
            "Hi, I'm the PID stealer! PID: %d, taking over victim PID %d with executable %s\n",
            my_pid, victim_pid, takeover_exe_cstr);
    return 0;
}

int main(int argc, const char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <NUMTHREAD> <VICTIM PID> <STEALER EXE>\n", getprogname());
        return 1;
    }

    const auto num_threads_int = atoi(argv[1]);
    if (num_threads_int < 0) {
        fprintf(stderr, "num_threads '%d' is negative!\n", num_threads_int);
        return 2;
    } else if (num_threads_int > 255) {
        fprintf(stderr, "num_threads '%d' is > 255!\n", num_threads_int);
    }
    const auto num_threads = static_cast<uint8_t>(num_threads_int);

    const auto victim_pid_cstr = argv[2];
    const auto victim_pid      = (pid_t)atoi(victim_pid_cstr);
    if (!victim_pid) {
        fprintf(stderr, "Victim PID '%s' couldn't be parsed!", victim_pid_cstr);
        return 3;
    }

    const auto takeover_exe_cstr = argv[3];

    const auto res = takeover(num_threads, victim_pid, takeover_exe_cstr);
    return res ? res + 3 : 0;
}
