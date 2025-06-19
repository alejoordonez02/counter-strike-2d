# common/CMakeLists.txt

add_library(cs2d_common STATIC)

target_sources(cs2d_common
    PRIVATE
    maploader.cpp
    PUBLIC
    maploader.h
)

add_subdirectory(network)

target_include_directories(cs2d_common PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}
)
