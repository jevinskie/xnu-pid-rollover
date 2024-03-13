add_executable(takeover takeover.cpp)

target_link_libraries(takeover PRIVATE System)
target_compile_options(takeover PRIVATE -Wall -Wextra -Wpedantic -Wno-gnu-line-marker)
target_link_options(takeover PRIVATE -nostdlib)

install(TARGETS takeover
    RUNTIME DESTINATION bin
)
