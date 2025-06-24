#ifndef PRIVATE_WEAPON_DTO_H
#define PRIVATE_WEAPON_DTO_H

#include <cstdint>
#include <vector>

#include "common/weapons.h"
#include "dto.h"
#include "protocol.h"

class PrivateWeaponDTO: public DTO {
public:
    WeaponName name;
    uint8_t total_ammo = 0;
    uint8_t loaded_ammo = 0;

    PrivateWeaponDTO(WeaponName weapon_name, uint8_t total_ammo,
                     uint8_t loaded_ammo):
        DTO(DTOSerial::WEAPON_PRIVATE), name(weapon_name),
        total_ammo(total_ammo), loaded_ammo(loaded_ammo) {}

    explicit PrivateWeaponDTO(std::vector<uint8_t>&& bytes):
        DTO(std::move(bytes)) {
        auto payload_it = payload.begin();
        deserialize_from(payload_it);
    }
    explicit PrivateWeaponDTO(std::vector<uint8_t>::iterator& in):
        DTO(DTOSerial::WEAPON_PRIVATE) {
        deserialize_from(in);
    }
    PrivateWeaponDTO(): DTO(DTOSerial::WEAPON_PRIVATE) {}
    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
        out.push_back(static_cast<uint8_t>(name));
        out.push_back(total_ammo);
        out.push_back(loaded_ammo);
    }
    PrivateWeaponDTO(const PrivateWeaponDTO&) = delete;
    PrivateWeaponDTO& operator=(const PrivateWeaponDTO&) = delete;
    PrivateWeaponDTO(PrivateWeaponDTO&&) = default;
    PrivateWeaponDTO& operator=(PrivateWeaponDTO&&) = default;
    ~PrivateWeaponDTO() = default;

private:
    void deserialize_from(std::vector<uint8_t>::iterator& in) override {
        in++;  // skip 1st byte (DTO type)
        name = static_cast<WeaponName>(*in++);
        total_ammo = *in++;
        loaded_ammo = *in++;
    }
};

#endif
