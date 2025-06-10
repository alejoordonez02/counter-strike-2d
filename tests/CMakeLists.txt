target_sources(cs2d_tests
    PRIVATE
    main.cpp
    mock_player.cpp
    mock_player_physics.cpp
    cmd_deserialization.cpp
    serialization.cpp
    physics.cpp
    attack.cpp
    bomb.cpp
)

target_include_directories(cs2d_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
