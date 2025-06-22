#ifndef COMMON_NETWORK_DTOS_CHANGE_WEAPON_DTO_H
#define COMMON_NETWORK_DTOS_CHANGE_WEAPON_DTO_H

#include "common/network/dto.h"
#include "common/network/protocol.h"

class ChangeWeaponDTO: public DTO {
private:
    int weapon_type;

    void deserialize() override {}

public:
    explicit ChangeWeaponDTO(std::vector<uint8_t>&& bytes):
            DTO(std::move(bytes)) {
        deserialize();
    }

    explicit ChangeWeaponDTO(int weapon_type): DTO(DTOSerial::PlayerCommands::CHANGE_WEAPON), weapon_type(weapon_type) {}

    ChangeWeaponDTO(): DTO(DTOSerial::PlayerCommands::CHANGE_WEAPON), weapon_type(0) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
        out.push_back(static_cast<uint8_t>(weapon_type));
    }

    ~ChangeWeaponDTO() = default;
};


#endif