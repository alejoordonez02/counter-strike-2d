# server/world/equipment/CMakeLists.txt

target_sources(cs2d_server_lib
    PRIVATE
    bomb.cpp
    weapon.cpp
)

target_include_directories(cs2d_server_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
