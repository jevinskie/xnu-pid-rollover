#pragma once

#include "common.h"
#include "fileperm.h"

#include <filesystem>

namespace FilePerm {
namespace fs = std::filesystem;

// retval: 0 - in group, 1 - not in group, 2 - getgroups error
int am_member_of_group(gid_t gid) noexcept {
    return ::am_member_of_group(gid);
}

// retval: 0 - is executable, 1 - not executable, 2 - stat error, 3 - not regular file
int check_executable(const char *exe_path) noexcept {
    return ::check_executable(exe_path);
}

// retval: 0 - is executable, 1 - not executable, 2 - stat error, 3 - not regular file
int check_executable(const fs::path &exe_path) noexcept {
    return ::check_executable(exe_path.c_str());
}

} // namespace FilePerm
