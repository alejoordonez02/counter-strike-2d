#ifndef ATTACK_DTO_H
#define ATTACK_DTO_H

#include "../dto.h"
#include "../protocol.h"

class AttackDTO: private DTO {
public:
    AttackDTO(/* args de Attack */): DTO(DTOtypeSerial::COMMAND) {
        // data = serializacion de Attack
    }

    ~AttackDTO() = default;
};

#endif


// std::vector<uint8_t> Serializer::serialize(const Attack& attack) {
//     std::vector<uint8_t> srlzd_attack;

//     auto pos = attack.get_position();
//     auto srlzd_x = serialize(pos.x);
//     auto srlzd_y = serialize(pos.y);

//     srlzd_attack.push_back(PlayerCommandSerial::ATTACK);
//     srlzd_attack.insert(srlzd_attack.end(), srlzd_x.begin(), srlzd_x.end());
//     srlzd_attack.insert(srlzd_attack.end(), srlzd_y.begin(), srlzd_y.end());

//     return srlzd_attack;
// }