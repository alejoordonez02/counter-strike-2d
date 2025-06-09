# client/renderables/CMakeLists.txt

target_sources(cs2d_client
    PRIVATE
        main.cpp
        mainwindow.cpp
    PUBLIC
        mainwindow.h
)

target_include_directories(cs2d_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
