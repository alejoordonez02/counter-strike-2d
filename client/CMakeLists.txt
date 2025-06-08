target_sources(cs2d_client
    PRIVATE
        client_main.cpp
        client.cpp
        gameloop.cpp
        texture_provider.cpp
        animation_provider.cpp
        input_handler.cpp
        render.cpp
    PUBLIC
        client.h
        gameloop.h
        texture_provider.h
        animation_provider.h
        input_handler.h
        render.h
)

add_subdirectory(renderables)

target_include_directories(cs2d_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})