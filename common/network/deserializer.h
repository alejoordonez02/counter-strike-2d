#ifndef DESERIALIZER_H
#define DESERIALIZER_H

#include <memory>

#include "../player_commands/attack.h"
#include "../player_commands/command.h"
#include "../player_commands/move.h"

class Deserializer {
private:
    static float deserialize_float(const std::vector<uint8_t>& srlzd_float);
    static Position deserialize_position(const std::vector<uint8_t>& srlzd_pos);
    static Direction deserialize_direction(const std::vector<uint8_t>& srlzd_dir);
    static std::unique_ptr<Move> deserialize_move_command(const std::vector<uint8_t>& srzld_cmd);
    static std::unique_ptr<Attack> deserialize_attack_command(
            const std::vector<uint8_t>& srzld_cmd);

public:
    static std::unique_ptr<Command> deserialize_command(const std::vector<uint8_t>& srlzd_cmd);
};

#endif
