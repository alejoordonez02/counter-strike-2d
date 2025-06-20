# server/CMakeLists.txt

target_sources(cs2d_server
    PRIVATE
    client_handler.cpp
    game_loop.cpp
    game_maker.cpp
    main.cpp
)

add_subdirectory(model)
add_subdirectory(player_commands)
add_subdirectory(lobby_commands)

target_include_directories(cs2d_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
