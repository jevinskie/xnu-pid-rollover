set(SUBPROCESSPP_SRC
    subprocesspp.cpp
)

set(SUBPROCESSPP_HDR_STANDALONE
    common.hpp
    common-attrs.hpp
)

set(SUBPROCESSPP_PRIVATE_HDR_STANDALONE
    common-internal.hpp
)

set(SUBPROCESSPP_HDR)
foreach(HDR ${SUBPROCESSPP_HDR_STANDALONE})
    set(HDR "${CMAKE_CURRENT_SOURCE_DIR}/../../include/subprocesspp/${HDR}")
    list(APPEND SUBPROCESSPP_HDR ${HDR})
endforeach()

foreach(SRC ${SUBPROCESSPP_SRC})
    get_filename_component(HDR_NAME ${SRC} NAME_WLE)
    get_filename_component(SRC_EXT ${SRC} EXT)
    if("${SRC_EXT}" STREQUAL ".c")
       set(HDR "${CMAKE_CURRENT_SOURCE_DIR}/../../include/subprocesspp/${HDR_NAME}.h")
    elseif("${SRC_EXT}" STREQUAL ".cpp")
        set(HDR "${CMAKE_CURRENT_SOURCE_DIR}/../../include/subprocesspp/${HDR_NAME}.hpp")
    else()
        message(FATAL_ERROR "Unknown source extension '${SRC_EXT}' for source file '${SRC}'")
    endif()
    if(EXISTS ${HDR})
        list(APPEND SUBPROCESSPP_HDR ${HDR})
    endif()
endforeach()

set(SUBPROCESSPP_PUBLIC_LIBS
    subprocess-dot-h
)

set(SUBPROCESSPP_PRIVATE_LIBS
    fileperm
)

# SUBPROCESSPP_HDR/SUBPROCESSPP_PRIVATE_HDR_STANDALONE added for Xcode project generation
add_library(subprocesspp STATIC ${SUBPROCESSPP_SRC} ${SUBPROCESSPP_HDR} ${SUBPROCESSPP_PRIVATE_HDR_STANDALONE})
add_library(subprocesspp-shared SHARED ${SUBPROCESSPP_SRC} ${SUBPROCESSPP_HDR} ${SUBPROCESSPP_PRIVATE_HDR_STANDALONE})
set_target_properties(subprocesspp subprocesspp-shared PROPERTIES PUBLIC_HEADER "${SUBPROCESSPP_HDR}")

target_link_libraries(subprocesspp
PUBLIC
    ${SUBPROCESSPP_PUBLIC_LIBS}
PRIVATE
    ${SUBPROCESSPP_PRIVATE_LIBS}
)
target_compile_options(subprocesspp PRIVATE -Wall -Wextra -Wpedantic -Wno-gnu-line-marker)

target_include_directories(subprocesspp
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(subprocesspp-shared
PUBLIC
    ${SUBPROCESSPP_PUBLIC_LIBS}
PRIVATE
    ${SUBPROCESSPP_PRIVATE_LIBS}
)
target_compile_options(subprocesspp-shared PRIVATE -Wall -Wextra -Wpedantic -Wno-gnu-line-marker)

target_include_directories(subprocesspp-shared
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
)


install(TARGETS subprocesspp subprocesspp-shared
    ARCHIVE DESTINATION usr/lib
    LIBRARY DESTINATION usr/lib
    PUBLIC_HEADER DESTINATION include/subprocesspp
)

# target_compile_options(subprocesspp PRIVATE -Xclang -fdump-record-layouts)
