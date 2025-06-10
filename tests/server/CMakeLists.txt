target_sources(cs2d_tests
    PRIVATE
    cmd_deserialization.cpp
    serialization.cpp
)

add_subdirectory(model)

target_include_directories(cs2d_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
