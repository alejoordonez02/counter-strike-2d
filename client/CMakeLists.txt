target_sources(cs2d_client
    PRIVATE
        client_main.cpp
        client.cpp
        gameloop.cpp
        texture_provider.cpp
        animation_provider.cpp
        input_handler.cpp
        render.cpp
        mainwindow.cpp
        lobbywindow.cpp
        creatematchdialog.cpp
        teamselectiondialog.cpp
        camera.cpp
        hud_manager.cpp
)

add_subdirectory(renderables)

target_include_directories(cs2d_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})