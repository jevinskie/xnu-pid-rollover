add_library(subprocess-dot-h INTERFACE)
target_include_directories(subprocess-dot-h INTERFACE subprocess-scoped-include)

add_subdirectory(googletest EXCLUDE_FROM_ALL)

add_subdirectory(benchmark EXCLUDE_FROM_ALL)

add_subdirectory(fmt EXCLUDE_FROM_ALL)

add_compile_options(-fexceptions)
add_subdirectory(nanobench EXCLUDE_FROM_ALL)
add_compile_options(-fno-exceptions)
