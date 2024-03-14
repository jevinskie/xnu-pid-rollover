add_executable(steal-pid steal-pid.cpp)

target_link_libraries(steal-pid PRIVATE fileperm subprocesspp xnu-nolibc)
target_compile_options(steal-pid PRIVATE -Wall -Wextra -Wpedantic -Wno-gnu-line-marker)
target_link_options(steal-pid PRIVATE)
add_dependencies(steal-pid nop-looper takeover)

install(TARGETS steal-pid
    RUNTIME DESTINATION bin
)
