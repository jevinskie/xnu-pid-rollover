add_executable(nop-looper nop-looper.cpp)

target_compile_options(nop-looper PRIVATE -Wall -Wextra -Wpedantic -Wno-gnu-line-marker)

install(TARGETS nop-looper
    RUNTIME DESTINATION bin
)
