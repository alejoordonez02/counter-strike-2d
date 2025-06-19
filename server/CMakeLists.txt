# server/CMakeLists.txt

target_sources(cs2d_server
    PRIVATE
    main.cpp
)

add_subdirectory(model)
add_subdirectory(command)
add_subdirectory(network)

target_link_libraries(cs2d_server PRIVATE cs2d_common)
target_include_directories(cs2d_server PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
