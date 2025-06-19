# common/network/CMakeLists.txt

target_sources(cs2d_common
    PRIVATE
     connection.cpp
)

add_subdirectory(dtos)
add_subdirectory(socket)
