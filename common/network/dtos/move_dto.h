#ifndef MOVE_DTO_H
#define MOVE_DTO_H

#include "../dto.h"
#include "../protocol.h"

class MoveDTO: private DTO {
public:
    MoveDTO(/* args de Move */): DTO(DTOtypeSerial::COMMAND) {
        // data = serializacion de Move
    }

    ~MoveDTO() = default;
};

#endif

// namespace {
// constexpr std::unordered_map<Direction, uint8_t> dir_to_srl = {
//         {Direction::N, DirectionSerial::N}, {Direction::NE, DirectionSerial::NE},
//         {Direction::E, DirectionSerial::E}, {Direction::SE, DirectionSerial::SE},
//         {Direction::S, DirectionSerial::S}, {Direction::SW, DirectionSerial::SW},
//         {Direction::W, DirectionSerial::W}, {Direction::NW, DirectionSerial::NW}};
// };

// std::vector<uint8_t> Serializer::serialize(const Move& move) {
//     return {PlayerCommandSerial::MOVE, dir_to_srl.at(move.get_dir())};
// }