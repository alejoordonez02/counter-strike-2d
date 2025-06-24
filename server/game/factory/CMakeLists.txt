# server/factory/CMakeLists.txt

target_sources(cs2d_server_lib
    PRIVATE
    game_factory.cpp
    map_factory.cpp
    player_factory.cpp
    weapon_factory.cpp
    world_factory.cpp
)

target_include_directories(cs2d_server_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
