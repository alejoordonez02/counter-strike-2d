# server/CMakeLists.txt

set(SERVER_SOURCES
    acceptor.cpp
    client_handler.cpp
    main.cpp
    server.cpp
)

add_library(cs2d_server_lib)

target_link_libraries(cs2d_server_lib PUBLIC cs2d_common)

target_include_directories(cs2d_server_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(cs2d_server_lib
    PRIVATE
    client_handler.cpp
    main.cpp
)

add_subdirectory(game)
add_subdirectory(lobby_commands)
