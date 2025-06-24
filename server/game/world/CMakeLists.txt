# server/world/CMakeLists.txt

target_sources(cs2d_server_lib
    PRIVATE
    counter_terrorist.cpp
    map.cpp
    player.cpp
    random.cpp
    terrorist.cpp
    timer.cpp
    world.cpp
)

add_subdirectory(actions)
add_subdirectory(equipment)
add_subdirectory(physics)
add_subdirectory(team)
add_subdirectory(drops)

target_include_directories(cs2d_server_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
