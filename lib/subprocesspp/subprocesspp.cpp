#include "subprocesspp/subprocesspp.hpp"
#include "common-internal.hpp"
#include <fileperm/fileperm.hpp>

namespace SubprocessPP {

Subprocess::Subprocess(const fs::path &exe_path) noexcept : m_exe_path(exe_path) {}
Subprocess::~Subprocess() {}

std::error_code Subprocess::create(const std::vector<std::string_view> &args) noexcept {
    std::error_code canon_ec;
#if __has_feature(cxx_exceptions)
    try {
#endif
        const auto canon_exe_path = fs::canonical(m_exe_path, canon_ec);
#if __has_feature(cxx_exceptions)
    } catch (const fs::filesystem_error &e) {
        return e.code();
    }
#endif
    if (canon_ec) {
        return canon_ec;
    }
    if (const auto perm_res = FilePerm::check_executable(m_exe_path)) {
        switch (perm_res) {
        case 1:
            return std::make_error_code(std::errc::executable_format_error);
        case 3:
            return std::make_error_code(std::errc::no_such_file_or_directory);
        case 2:
        default:
            return std::make_error_code(std::errc::io_error);
        }
    }
    return std::error_code();
}

} // namespace SubprocessPP
