cmake_minimum_required(VERSION 3.28)

project(xnu-pid-rollover C CXX)

set(BUILD_SHARED_LIBS OFF)

# set(CMAKE_OSX_ARCHITECTURES arm64e)
# set(CMAKE_XCODE_ATTRIBUTE_COMPILER_INDEX_STORE_ENABLE NO)

option(FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." ON)

if (${FORCE_COLORED_OUTPUT})
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
       add_compile_options(-fdiagnostics-color=always)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
       add_compile_options(-fcolor-diagnostics)
    endif ()
endif ()

# add_compile_options(-glldb)
# add_compile_options(-g0)

if (NOT ${CMAKE_BUILD_TYPE} STREQUAL Debug)
   add_compile_options(-O0 -fno-omit-frame-pointer)

   # add_compile_options(-Og)
   # add_link_options(-Og)

   # add_compile_options(-fsanitize=address)
   # add_link_options(-fsanitize=address)

   # add_compile_options(-fsanitize=memory)
   # add_link_options(-fsanitize=memory)

   # lol just don't its so bad
   # add_compile_options(-fno-inline)
   # add_link_options(-fno-inline)
else()
   # add_compile_options(-Oz)
   # add_link_options(-Oz)

   # add_compile_options(-Os)
   # add_link_options(-Os)

   add_compile_options(-O3)
   add_link_options(-O3)

   # add_compile_options(-Ofast)
   # add_link_options(-Ofast)
endif()

add_compile_options(-fno-rtti -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables)
add_link_options(-fno-rtti -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables)

add_compile_options(-fvisibility=hidden -fvisibility-inlines-hidden -fvisibility-inlines-hidden-static-local-var -ffunction-sections -fdata-sections)
add_link_options(-Wl,-dead_strip)

if (NOT ${CMAKE_BUILD_TYPE} STREQUAL Debug)
   add_compile_options(-flto=full -fwhole-program-vtables -fvirtual-function-elimination)
   add_link_options(-flto=full -fwhole-program-vtables -fvirtual-function-elimination)
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
   add_compile_options(-ferror-limit=100)
endif()

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_EXTENSIONS YES)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS YES)

add_subdirectory(3rdparty)

add_compile_options(-save-temps)
execute_process(COMMAND sysctl -n hw.ncpu OUTPUT_VARIABLE XNU_PID_ROLLOVER_NUM_CPUS OUTPUT_STRIP_TRAILING_WHITESPACE)
message("XNU_PID_ROLLOVER_NUM_CPUS: ${XNU_PID_ROLLOVER_NUM_CPUS}")
add_compile_definitions(XNU_PID_ROLLOVER_NUM_CPUS=${XNU_PID_ROLLOVER_NUM_CPUS})

add_subdirectory(lib)
add_subdirectory(bench)
add_subdirectory(tools)
