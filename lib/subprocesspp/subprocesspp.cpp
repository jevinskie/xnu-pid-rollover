#include "subprocesspp/subprocesspp.hpp"
#include "common-internal.hpp"
#include <fileperm/fileperm.h>

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
    return std::error_code();
}

} // namespace SubprocessPP
