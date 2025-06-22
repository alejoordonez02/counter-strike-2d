# server/world/team/CMakeLists.txt

target_sources(cs2d_server_lib
    PRIVATE
    counter_terrorists.cpp
    terrorists.cpp
    team.cpp
)

target_include_directories(cs2d_server_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
