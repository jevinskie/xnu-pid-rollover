#pragma once

#include "common.hpp"
#include <subprocess/subprocess.h>

#include <expected>
#include <optional>
#include <system_error>

namespace SubprocessPP {

class SUBPROCESSPP_EXPORT Subprocess {
public:
    Subprocess(const fs::path &exe_path) noexcept;
    std::error_code create(const std::vector<std::string_view> &args) noexcept;
    std::optional<int> join() noexcept;
    void destroy() noexcept;
    std::expected<int, std::error_code> kill() noexcept;
    bool alive() noexcept;
    ~Subprocess();

private:
    struct subprocess_s m_subprocess {};
    const fs::path &m_exe_path;
};

} // namespace SubprocessPP
