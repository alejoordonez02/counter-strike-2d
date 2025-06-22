target_sources(cs2d_client
    PRIVATE
        client_main.cpp
        client.cpp
        gameloop.cpp
        input_handler.cpp
        render.cpp
        mainwindow.cpp
        camera.cpp
        hud_manager.cpp
    PUBLIC
        client.h
        gameloop.h
        input_handler.h
        render.h
        mainwindow.h
        camera.h
        hud_manager.h
)

add_subdirectory(renderables)
add_subdirectory(providers)

target_include_directories(cs2d_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})