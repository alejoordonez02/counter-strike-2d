# server/world/actions/CMakeLists.txt

target_sources(cs2d_server_lib
    PRIVATE
    attack.cpp
    defuse_bomb.cpp
    plant_bomb.cpp
    reload.cpp
)

target_include_directories(cs2d_server_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
