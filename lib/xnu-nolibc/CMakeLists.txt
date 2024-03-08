set(XNU_NOLIBC_SRC
    xnu-nolibc.cpp
)

set(XNU_NOLIBC_HDR_STANDALONE
    common.hpp
    common-attrs.hpp
)

set(XNU_NOLIBC_PRIVATE_HDR_STANDALONE
    common-internal.hpp
)

set(XNU_NOLIBC_HDR)
foreach(HDR ${XNU_NOLIBC_HDR_STANDALONE})
    set(HDR "${CMAKE_CURRENT_SOURCE_DIR}/../../include/xnu-nolibc/${HDR}")
    list(APPEND XNU_NOLIBC_HDR ${HDR})
endforeach()

foreach(SRC ${XNU_NOLIBC_SRC})
    get_filename_component(HDR_NAME ${SRC} NAME_WLE)
    get_filename_component(SRC_EXT ${SRC} EXT)
    if("${SRC_EXT}" STREQUAL ".c")
       set(HDR "${CMAKE_CURRENT_SOURCE_DIR}/../../include/xnu-nolibc/${HDR_NAME}.h")
    elseif("${SRC_EXT}" STREQUAL ".cpp")
        set(HDR "${CMAKE_CURRENT_SOURCE_DIR}/../../include/xnu-nolibc/${HDR_NAME}.hpp")
    else()
        message(FATAL_ERROR "Unknown source extension '${SRC_EXT}' for source file '${SRC}'")
    endif()
    if(EXISTS ${HDR})
        list(APPEND XNU_NOLIBC_HDR ${HDR})
    endif()
endforeach()

set(XNU_NOLIBC_PUBLIC_LIBS
)

set(XNU_NOLIBC_PRIVATE_LIBS
)

# XNU_NOLIBC_HDR/XNU_NOLIBC_PRIVATE_HDR_STANDALONE added for Xcode project generation
add_library(xnu-nolibc STATIC ${XNU_NOLIBC_SRC} ${XNU_NOLIBC_HDR} ${XNU_NOLIBC_PRIVATE_HDR_STANDALONE})
add_library(xnu-nolibc-shared SHARED ${XNU_NOLIBC_SRC} ${XNU_NOLIBC_HDR} ${XNU_NOLIBC_PRIVATE_HDR_STANDALONE})
set_target_properties(xnu-nolibc xnu-nolibc-shared PROPERTIES PUBLIC_HEADER "${XNU_NOLIBC_HDR}")

target_link_libraries(xnu-nolibc
PUBLIC
    ${XNU_NOLIBC_PUBLIC_LIBS}
PRIVATE
    ${XNU_NOLIBC_PRIVATE_LIBS}
)
target_compile_options(xnu-nolibc PRIVATE -Wall -Wextra -Wpedantic -Wno-gnu-line-marker)

target_include_directories(xnu-nolibc
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(xnu-nolibc-shared
PUBLIC
    ${XNU_NOLIBC_PUBLIC_LIBS}
PRIVATE
    ${XNU_NOLIBC_PRIVATE_LIBS}
)
target_compile_options(xnu-nolibc-shared PRIVATE -Wall -Wextra -Wpedantic -Wno-gnu-line-marker)

target_include_directories(xnu-nolibc-shared
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
)


install(TARGETS xnu-nolibc xnu-nolibc-shared
    ARCHIVE DESTINATION usr/lib
    LIBRARY DESTINATION usr/lib
    PUBLIC_HEADER DESTINATION include/xnu-nolibc
)

# target_compile_options(xnu-nolibc PRIVATE -Xclang -fdump-record-layouts)
