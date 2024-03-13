#include <cerrno>
#include <climits>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/stat.h>
#include <unistd.h>

#include <xnu-nolibc/xnu-nolibc.hpp>
using namespace XnuNoLibc;

// retval: 0 - in group, 1 - not in group, 2 - error
static int am_member_of_group(gid_t gid) {
    gid_t groups[NGROUPS_MAX + 2];
    groups[0]          = getegid();
    const auto ngroups = getgroups(NGROUPS_MAX + 1, groups + 1);
    if (ngroups < 0) {
        fprintf(stderr, "Error calling getgroups()! res: %d errno: %d aka '%s'\n", ngroups, errno,
                strerror(errno));
        return 2;
    }
    for (int i = 0; i < ngroups + 1; ++i) {
        if (groups[i] == gid) {
            return 0;
        }
    }
    return 1;
}

static int check_executable(const char *exe_path) {
    struct stat st;
    if (const auto res = stat(exe_path, &st) < 0) {
        fprintf(stderr, "Failed to stat exe '%s' stat() res: %d errno: %d aka '%s'\n", exe_path,
                res, errno, strerror(errno));
        return 2;
    }
    if (!S_ISREG(st.st_mode)) {
        fprintf(stderr, "exe '%s' (or the file it points to if a symlink) is not a regular file\n",
                exe_path);
        return 3;
    }
    if (st.st_mode & S_IXOTH) {
        // executable by anyone
        return 0;
    }
    if ((st.st_mode & S_IXGRP) && !am_member_of_group(st.st_gid)) {
        // executable by group
        return 0;
    }
    if ((st.st_mode & S_IXUSR) && (st.st_uid == geteuid())) {
        // executable by user
        return 0;
    }
    return 1;
}

static int takeover(uint8_t num_threads, pid_t victim_pid, const char *takeover_exe_cstr) {
    if (victim_pid > XNU_PID_MAX) {
        fprintf(stderr, "Victim PID '%d' cant be greater than MAX_PID '%d'!", victim_pid,
                XNU_PID_MAX);
        return 1;
    }

    if (const auto res = check_executable(takeover_exe_cstr)) {
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
