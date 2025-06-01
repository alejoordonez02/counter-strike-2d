target_sources(cs2d_tests
    PRIVATE
    model.cpp
    mock_player.cpp
    main.cpp
)

target_include_directories(cs2d_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
