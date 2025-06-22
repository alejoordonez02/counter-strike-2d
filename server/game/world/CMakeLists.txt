# server/world/CMakeLists.txt

target_sources(cs2d_server_lib
    PRIVATE
    map.cpp
    player.cpp
    terrorist.cpp
    counter_terrorist.cpp
    random.cpp
    world.cpp
)

add_subdirectory(actions)
add_subdirectory(equipment)
add_subdirectory(physics)
add_subdirectory(team)

target_include_directories(cs2d_server_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
