# server/game/CMakeLists.txt

target_sources(cs2d_server_lib
    PRIVATE
    game.cpp
    game_maker.cpp
    player_handler.cpp
)

add_subdirectory(config)
add_subdirectory(factory)
add_subdirectory(player_commands)
add_subdirectory(world)

target_include_directories(cs2d_server_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
