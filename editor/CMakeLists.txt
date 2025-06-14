target_sources(cs2d_editor
    PRIVATE
    ../common/maploader.cpp
    PUBLIC
    ../common/maploader.h
)

add_subdirectory(src)

target_include_directories(cs2d_editor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})