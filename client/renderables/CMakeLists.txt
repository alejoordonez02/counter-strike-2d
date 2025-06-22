# client/renderables/CMakeLists.txt

target_sources(cs2d_client
    PRIVATE
        animation.cpp
        animation.cpp
        renderable_player.cpp
        renderable_legs.cpp
        renderable_gun.cpp
        renderable_gun_effect.cpp
        renderable_pointer.cpp
    PUBLIC
        animation.h
        animation.h
        renderable_player.h
        renderable_legs.h
        renderable_gun.h
        renderable_gun_effect.h
        renderable_pointer.h
)

add_subdirectory(hud)
add_subdirectory(map)

target_include_directories(cs2d_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
