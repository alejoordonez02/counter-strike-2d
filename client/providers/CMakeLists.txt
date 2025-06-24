# client/providers/CMakeLists.txt

target_sources(cs2d_client
    PRIVATE
        texture_provider.cpp
        animation_provider.cpp
    PUBLIC
        texture_provider.h
        animation_provider.h
)

target_include_directories(cs2d_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
