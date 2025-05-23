target_sources(cs2d_common
    PRIVATE
    # .cpp files
    network/deserializer.cpp
    network/serializer.cpp
    player_commands/attack.cpp
    player_commands/move.cpp
    PUBLIC
    # .h files
    player_commands/attack.h
    player_commands/command.h
    player_commands/move.h
    network/deserializer.h
    network/serializer.h
    network/protocol.h
    position.h
    direction.h
    )
