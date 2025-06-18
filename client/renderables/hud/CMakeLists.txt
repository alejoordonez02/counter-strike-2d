# client/renderables/hud/CMakeLists.txt

target_sources(cs2d_client
    PRIVATE
        renderable_numbers.cpp
        renderable_hud_health.cpp
    PUBLIC
        renderable_numbers.h
        renderable_hud_health.h
)

target_include_directories(cs2d_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
