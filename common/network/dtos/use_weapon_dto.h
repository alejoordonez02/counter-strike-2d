#ifndef COMMON_NETWORK_DTOS_USE_WEAPON_DTO_H
#define COMMON_NETWORK_DTOS_USE_WEAPON_DTO_H

#include <cstdint>
#include <utility>
#include <vector>

#include "common/network/dto.h"
#include "common/network/protocol.h"
#include "common/weapons.h"

class UseWeaponDTO: public DTO {
private:
    WeaponType weapon_type;

    friend class UseWeapon;

    void deserialize_from(std::vector<uint8_t>::iterator& in) override {
        in++;  // skip 1st byte (DTO weapon_type)
        weapon_type = static_cast<WeaponType>(*in++);
    }

public:
    explicit UseWeaponDTO(std::vector<uint8_t>&& bytes): DTO(std::move(bytes)) {
        auto payload_it = payload.begin();
        deserialize_from(payload_it);
    }

    explicit UseWeaponDTO(std::vector<uint8_t>::iterator& in):
        DTO(DTOSerial::PlayerCommands::USE_WEAPON) {
        deserialize_from(in);
    }

    explicit UseWeaponDTO(WeaponType weapon_type):
        DTO(DTOSerial::PlayerCommands::USE_WEAPON), weapon_type(weapon_type) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
        out.push_back(static_cast<uint8_t>(weapon_type));
    }

    ~UseWeaponDTO() = default;
};

#endif
