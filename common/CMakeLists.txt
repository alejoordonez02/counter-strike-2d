# common/CMakeLists.txt

target_sources(cs2d_common
    PRIVATE
    maploader.cpp
    PUBLIC
    maploader.h
)

add_subdirectory(network)

target_include_directories(cs2d_common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
