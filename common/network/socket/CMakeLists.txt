# common/network/socket/CMakeLists.txt

target_sources(cs2d_common
    PRIVATE
     liberror.cpp
     resolver.cpp
     resolvererror.cpp
     socket.cpp
)

target_include_directories(cs2d_common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
