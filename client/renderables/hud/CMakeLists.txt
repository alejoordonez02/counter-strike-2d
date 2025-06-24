# client/renderables/hud/CMakeLists.txt

target_sources(cs2d_client
    PRIVATE
        renderable_numbers.cpp
        renderable_hud_health.cpp
        renderable_hud_timer.cpp
        renderable_hud_money.cpp
        renderable_hud_total_ammo.cpp
        renderable_hud_loaded_ammo.cpp
    PUBLIC
)

target_include_directories(cs2d_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
