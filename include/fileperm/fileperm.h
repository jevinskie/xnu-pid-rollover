#pragma once

#include "common.h"

#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

// retval: 0 - in group, 1 - not in group, 2 - getgroups error
int am_member_of_group(gid_t gid);

// retval: 0 - is executable, 1 - not executable, 2 - stat error, 3 - not regular file
int check_executable(const char *exe_path);

#ifdef __cplusplus
} // extern "C"
#endif
