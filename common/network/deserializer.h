#ifndef DESERIALIZER_H
#define DESERIALIZER_H

#include <memory>

#include "../player_commands/attack.h"
#include "../player_commands/command.h"
#include "../player_commands/move.h"

class Deserializer {
private:
    static std::unique_ptr<Move> deserialize_move_command(const std::string& srzld_cmd);
    static std::unique_ptr<Attack> deserialize_attack_command(const std::string& srzld_cmd);

public:
    static std::unique_ptr<Command> deserialize_command(const std::string& srlzd_cmd);
};

#endif
