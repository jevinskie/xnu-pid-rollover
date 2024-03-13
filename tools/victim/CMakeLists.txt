add_executable(victim victim.cpp)

target_link_libraries(victim PRIVATE System)
target_compile_options(victim PRIVATE -Wall -Wextra -Wpedantic -Wno-gnu-line-marker)
target_link_options(victim PRIVATE -nostdlib)

install(TARGETS victim
    RUNTIME DESTINATION bin
)
