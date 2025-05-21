target_sources(cs2d_common
    PRIVATE
    # .cpp files
    network/deserializer.cpp
    PUBLIC
    # .h files
    player_commands/attack.h
    player_commands/command.h
    player_commands/move.h
    network/deserializer.h
    network/protocol.h
    )
