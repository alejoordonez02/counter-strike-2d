# server/world/physics/CMakeLists.txt

target_sources(cs2d_server_lib
    PRIVATE
    player_physics.cpp
    structure.cpp
    trajectory.cpp
)

target_include_directories(cs2d_server_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
