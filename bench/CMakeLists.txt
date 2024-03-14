add_executable(test-pid-benchmark test-pid-benchmark.cpp)

target_link_libraries(test-pid-benchmark PRIVATE benchmark subprocess-dot-h)
target_compile_options(test-pid-benchmark PRIVATE -Wall -Wextra -Wpedantic -Wno-gnu-line-marker)

install(TARGETS test-pid-benchmark
    RUNTIME DESTINATION bin
)


add_executable(test-pid-nanobench test-pid-nanobench.cpp)

target_link_libraries(test-pid-nanobench PRIVATE nanobench subprocess-dot-h)
target_compile_options(test-pid-nanobench PRIVATE -fexceptions -Wall -Wextra -Wpedantic -Wno-gnu-line-marker)

install(TARGETS test-pid-nanobench
    RUNTIME DESTINATION bin
)


add_executable(test-yield-benchmark test-yield-benchmark.cpp)

target_link_libraries(test-yield-benchmark PRIVATE benchmark)
target_compile_options(test-yield-benchmark PRIVATE -Wall -Wextra -Wpedantic -Wno-gnu-line-marker)

install(TARGETS test-yield-benchmark
    RUNTIME DESTINATION bin
)


add_executable(test-yield-nanobench test-yield-nanobench.cpp)

target_link_libraries(test-yield-nanobench PRIVATE nanobench)
target_compile_options(test-yield-nanobench PRIVATE -fexceptions -Wall -Wextra -Wpedantic -Wno-gnu-line-marker)

install(TARGETS test-yield-nanobench
    RUNTIME DESTINATION bin
)
