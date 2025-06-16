add_library(cs2d_server_model STATIC
    attack.cpp
    player.cpp
    player_physics.cpp
    random.cpp
    weapon.cpp
)

target_include_directories(cs2d_server_model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(cs2d_server_model PRIVATE cs2d_common)
