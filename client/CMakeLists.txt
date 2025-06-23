target_sources(cs2d_client
    PRIVATE
        client_main.cpp
        client.cpp
        gameloop.cpp
        input_handler.cpp
        render.cpp
        mainwindow.cpp
        lobbywindow.cpp
        creatematchdialog.cpp
        camera.cpp
        hud_manager.cpp
        field_of_view.cpp
)

add_subdirectory(renderables)
add_subdirectory(providers)

target_include_directories(cs2d_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})