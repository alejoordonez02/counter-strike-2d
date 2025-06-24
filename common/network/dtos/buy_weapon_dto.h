#ifndef COMMON_NETWORK_DTOS_BUY_WEAPON_DTO_H
#define COMMON_NETWORK_DTOS_BUY_WEAPON_DTO_H

#include <cstdint>
#include <utility>
#include <vector>

#include "common/network/dto.h"
#include "common/network/protocol.h"
#include "common/weapons.h"

class BuyWeaponDTO: public DTO {
private:
    WeaponName weapon_name;

    friend class BuyWeapon;

    void deserialize_from(std::vector<uint8_t>::iterator& in) override {
        in++;  // skip 1st byte (DTO weapon_name)
        weapon_name = static_cast<WeaponName>(*in++);
    }

public:
    explicit BuyWeaponDTO(std::vector<uint8_t>&& bytes): DTO(std::move(bytes)) {
        auto payload_it = payload.begin();
        deserialize_from(payload_it);
    }

    explicit BuyWeaponDTO(std::vector<uint8_t>::iterator& in):
        DTO(DTOSerial::PlayerCommands::BUY_WEAPON) {
        deserialize_from(in);
    }

    explicit BuyWeaponDTO(WeaponName weapon_name):
        DTO(DTOSerial::PlayerCommands::BUY_WEAPON), weapon_name(weapon_name) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
        out.push_back(static_cast<uint8_t>(weapon_name));
    }

    ~BuyWeaponDTO() = default;
};

#endif
