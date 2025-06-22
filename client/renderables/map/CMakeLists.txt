# client/renderables/map/CMakeLists.txt

target_sources(cs2d_client
    PRIVATE
        renderable_block.cpp
        renderable_map.cpp
    PUBLIC
        renderable_block.h
        renderable_map.h
)

target_include_directories(cs2d_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
