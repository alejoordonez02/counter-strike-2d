# common/network/CMakeLists.txt

target_sources(cs2d_common
    PRIVATE
     connection.cpp
     dto.cpp
)

add_subdirectory(dtos)
add_subdirectory(socket)

target_include_directories(cs2d_common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
