target_sources(cs2d_tests
    PRIVATE
    # .cpp files
    deserializer.cpp
    serializer.cpp
    model.cpp
    mock_player.cpp
    PUBLIC
    # .h files
    mock_player.h
)
