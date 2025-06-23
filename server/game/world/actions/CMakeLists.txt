# server/world/actions/CMakeLists.txt

target_sources(cs2d_server_lib
    PRIVATE
    attack.cpp
    plant_bomb.cpp
)

target_include_directories(cs2d_server_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
