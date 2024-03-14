set(FILEPERM_SRC
    fileperm.c
)

set(FILEPERM_HDR_STANDALONE
    common.h
    common-attrs.h
    fileperm.hpp
)

set(FILEPERM_PRIVATE_HDR_STANDALONE
    common-internal.h
)

set(FILEPERM_HDR)
foreach(HDR ${FILEPERM_HDR_STANDALONE})
    set(HDR "${CMAKE_CURRENT_SOURCE_DIR}/../../include/fileperm/${HDR}")
    list(APPEND FILEPERM_HDR ${HDR})
endforeach()

foreach(SRC ${FILEPERM_SRC})
    get_filename_component(HDR_NAME ${SRC} NAME_WLE)
    get_filename_component(SRC_EXT ${SRC} EXT)
    if("${SRC_EXT}" STREQUAL ".c")
       set(HDR "${CMAKE_CURRENT_SOURCE_DIR}/../../include/fileperm/${HDR_NAME}.h")
    elseif("${SRC_EXT}" STREQUAL ".cpp")
        set(HDR "${CMAKE_CURRENT_SOURCE_DIR}/../../include/fileperm/${HDR_NAME}.hpp")
    else()
        message(FATAL_ERROR "Unknown source extension '${SRC_EXT}' for source file '${SRC}'")
    endif()
    if(EXISTS ${HDR})
        list(APPEND FILEPERM_HDR ${HDR})
    endif()
endforeach()

set(FILEPERM_PUBLIC_LIBS
)

set(FILEPERM_PRIVATE_LIBS
)

# FILEPERM_HDR/FILEPERM_PRIVATE_HDR_STANDALONE added for Xcode project generation
add_library(fileperm STATIC ${FILEPERM_SRC} ${FILEPERM_HDR} ${FILEPERM_PRIVATE_HDR_STANDALONE})
add_library(fileperm-shared SHARED ${FILEPERM_SRC} ${FILEPERM_HDR} ${FILEPERM_PRIVATE_HDR_STANDALONE})
set_target_properties(fileperm fileperm-shared PROPERTIES PUBLIC_HEADER "${FILEPERM_HDR}")

target_link_libraries(fileperm
PUBLIC
    ${FILEPERM_PUBLIC_LIBS}
PRIVATE
    ${FILEPERM_PRIVATE_LIBS}
)
target_compile_options(fileperm PRIVATE -Wall -Wextra -Wpedantic -Wno-gnu-line-marker)

target_include_directories(fileperm
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(fileperm-shared
PUBLIC
    ${FILEPERM_PUBLIC_LIBS}
PRIVATE
    ${FILEPERM_PRIVATE_LIBS}
)
target_compile_options(fileperm-shared PRIVATE -Wall -Wextra -Wpedantic -Wno-gnu-line-marker)

target_include_directories(fileperm-shared
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
)


install(TARGETS fileperm fileperm-shared
    ARCHIVE DESTINATION usr/lib
    LIBRARY DESTINATION usr/lib
    PUBLIC_HEADER DESTINATION include/fileperm
)

# target_compile_options(fileperm PRIVATE -Xclang -fdump-record-layouts)
