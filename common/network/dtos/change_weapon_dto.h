#ifndef COMMON_NETWORK_DTOS_CHANGE_WEAPON_DTO_H
#define COMMON_NETWORK_DTOS_CHANGE_WEAPON_DTO_H

#include "common/network/dto.h"
#include "common/network/protocol.h"
#include "common/network/dtos/snapshot_dto.h"

class ChangeWeaponDTO: public DTO {
private:
    // uint8_t weapon_type;
    EquipmentType weapon_type;

    // friend class ChangeWeapon;

    void deserialize_from(std::vector<uint8_t>::iterator& in) override {
        in++;  // skip 1st byte (DTO type)
        weapon_type = static_cast<EquipmentType>(*in++);
    }

public:
    explicit ChangeWeaponDTO(std::vector<uint8_t>&& bytes): DTO(std::move(bytes)) {
        auto payload_it = payload.begin();
        deserialize_from(payload_it);
    }

    explicit ChangeWeaponDTO(std::vector<uint8_t>::iterator& in):
            DTO(DTOSerial::PlayerCommands::CHANGE_WEAPON) {
        deserialize_from(in);
    }

    explicit ChangeWeaponDTO(EquipmentType w_type):
            DTO(DTOSerial::PlayerCommands::CHANGE_WEAPON),
            weapon_type(w_type) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
        out.push_back(static_cast<uint8_t>(weapon_type));
    }

    ~ChangeWeaponDTO() = default;
};

#endif
