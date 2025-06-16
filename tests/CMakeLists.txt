target_sources(cs2d_tests
    PRIVATE
    main.cpp
)

add_subdirectory(client)
add_subdirectory(server)

target_include_directories(cs2d_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
