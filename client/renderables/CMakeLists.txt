# client/renderables/CMakeLists.txt

target_sources(cs2d_client
    PRIVATE
        animation.cpp
        animation.cpp
        renderable_player.cpp
        renderable_legs.cpp
    PUBLIC
        animation.h
        animation.h
        renderable_player.h
        renderable_legs.h
)

target_include_directories(cs2d_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
