# server/game/world/drops/CMakeLists.txt

target_sources(cs2d_server_lib
    PRIVATE
    bomb_drop.cpp
    drop.cpp
    weapon_drop.cpp
)

target_include_directories(cs2d_server_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
