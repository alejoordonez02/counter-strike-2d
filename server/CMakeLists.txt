# server/CMakeLists.txt

set(SERVER_SOURCES
    client_handler.cpp
    game.cpp
    game_maker.cpp
    main.cpp
    player_handler.cpp
)

add_library(cs2d_server_lib)

target_link_libraries(cs2d_server_lib PUBLIC cs2d_common)

target_include_directories(cs2d_server_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(cs2d_server_lib
    PRIVATE
    client_handler.cpp
    game.cpp
    game_maker.cpp
    main.cpp
    player_handler.cpp
)

add_subdirectory(config)
add_subdirectory(factory)
add_subdirectory(lobby_commands)
add_subdirectory(player_commands)
add_subdirectory(world)
