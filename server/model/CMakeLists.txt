# server/model/CMakeLists.txt

target_sources(cs2d_server
    PRIVATE
    attack.cpp
    player.cpp
    player_physics.cpp
    random.cpp
    weapon.cpp
)

target_include_directories(cs2d_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
