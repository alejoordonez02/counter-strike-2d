# server/model/CMakeLists.txt

target_sources(cs2d_server
    PRIVATE
    attack.cpp
    player.cpp
    player_physics.cpp
    random.cpp
    weapon.cpp
)

add_subdirectory(action)
add_subdirectory(equipment)
add_subdirectory(physics)
