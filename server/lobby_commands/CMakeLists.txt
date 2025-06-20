# server/lobby_commands/CMakeLists.txt

target_sources(cs2d_server
    PRIVATE
    create_game.cpp
    join_game.cpp
    list_games.cpp
)

target_include_directories(cs2d_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
