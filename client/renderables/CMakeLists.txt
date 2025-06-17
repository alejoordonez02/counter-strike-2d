# client/renderables/CMakeLists.txt

target_sources(cs2d_client
    PRIVATE
        animation.cpp
        animation.cpp
        renderable_player.cpp
        renderable_legs.cpp
        renderable_map.cpp
        renderable_block.cpp
        hud/renderable_numbers.cpp
    PUBLIC
        animation.h
        animation.h
        renderable_player.h
        renderable_legs.h
        renderable_map.h
        renderable_block.h
        hud/renderable_numbers.h
)

target_include_directories(cs2d_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
