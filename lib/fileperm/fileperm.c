#include "fileperm/fileperm.h"
#include "common-internal.h"

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// retval: 0 - in group, 1 - not in group, 2 - getgroups error
int am_member_of_group(gid_t gid) {
    gid_t groups[NGROUPS_MAX + 2];
    groups[0]         = getegid();
    const int ngroups = getgroups(NGROUPS_MAX + 1, groups + 1);
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

// retval: 0 - is executable, 1 - not executable, 2 - stat error, 3 - not regular file
int check_executable(const char *exe_path) {
    struct stat st;
    int res;
    if ((res = stat(exe_path, &st)) < 0) {
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
