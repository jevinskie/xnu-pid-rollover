add_executable(steal-pid steal-pid.cpp)

target_link_libraries(steal-pid PRIVATE fileperm xnu-nolibc)
target_compile_options(steal-pid PRIVATE -Wall -Wextra -Wpedantic -Wno-gnu-line-marker)
target_link_options(steal-pid PRIVATE)

install(TARGETS steal-pid
    RUNTIME DESTINATION bin
)
