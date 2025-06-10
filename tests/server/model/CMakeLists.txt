target_sources(cs2d_tests
    PRIVATE
    bomb.cpp
    collisions.cpp
    attack_action.cpp
    fire_rate.cpp
)

add_subdirectory(mocks)

target_include_directories(cs2d_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
