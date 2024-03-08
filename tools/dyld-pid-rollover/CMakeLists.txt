add_executable(dyld-pid-rollover dyld-pid-rollover.cpp)

target_link_libraries(dyld-pid-rollover PRIVATE xnu-nolibc)
target_compile_options(dyld-pid-rollover BEFORE PRIVATE -Wall -Wextra -Wpedantic -Wno-gnu-line-marker)
target_link_options(dyld-pid-rollover PRIVATE -Wl,-e,__start)

install(TARGETS dyld-pid-rollover
    RUNTIME DESTINATION usr/lib
    RUNTIME RENAME dyld
)
