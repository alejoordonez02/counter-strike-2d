#ifndef COMMON_NETWORK_DTOS_SNAPSHOT_DTO_H
#define COMMON_NETWORK_DTOS_SNAPSHOT_DTO_H

#include <sys/types.h>

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "common/network/dto.h"
#include "common/network/protocol.h"
#include "private_weapon_dto.h"

#define MAX_PLAYER_NAME 32

enum class EquipmentType : uint8_t { PRIMARY, SECONDARY, KNIFE, BOMB };

// armas en el suelo
class WeaponDTO: public DTO {
public:
    WeaponName name;
    int16_t x;
    int16_t y;

private:
    void deserialize_from(std::vector<uint8_t>::iterator& in) override {
        in++;  // skip 1st byte (DTO type)
        name = static_cast<WeaponName>(*in++);
        Position pos = deserialize_pos_from(in);
        x = pos.x;
        y = pos.y;
    }

public:
    explicit WeaponDTO(std::vector<uint8_t>&& bytes): DTO(std::move(bytes)) {
        auto payload_it = payload.begin();
        deserialize_from(payload_it);
    }

    explicit WeaponDTO(std::vector<uint8_t>::iterator& in):
        DTO(DTOSerial::WEAPON) {
        deserialize_from(in);
    }

    WeaponDTO(): DTO(DTOSerial::WEAPON) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
        out.push_back(static_cast<uint8_t>(name));
        serialize_tuple_into(out, x, y);
    }

    WeaponDTO(const WeaponDTO&) = delete;
    WeaponDTO& operator=(const WeaponDTO&) = delete;

    WeaponDTO(WeaponDTO&&) = default;
    WeaponDTO& operator=(WeaponDTO&&) = default;

    ~WeaponDTO() = default;
};

class PrivatePlayerDTO: public DTO {
public:
    uint8_t player_id = 0;
    uint8_t player_hp = 100;

    PrivateWeaponDTO current_weapon;

    uint total_money = 0;

    // estadisticas
    uint8_t rounds_won = 0;
    uint8_t total_kills = 0;

private:
    void deserialize_from(std::vector<uint8_t>::iterator& in) override {
        in++;  // skip 1st byte (DTO type)
        player_id = *in++;
        player_hp = *in++;
        current_weapon = PrivateWeaponDTO(in);
        total_money = deserialize_int_from(in);
        rounds_won = *in++;
        total_kills = *in++;
    }

public:
    explicit PrivatePlayerDTO(std::vector<uint8_t>&& bytes):
        DTO(std::move(bytes)) {
        auto payload_it = payload.begin();
        deserialize_from(payload_it);
    }

    explicit PrivatePlayerDTO(std::vector<uint8_t>::iterator& in):
        DTO(DTOSerial::PLAYER_PRIVATE) {
        deserialize_from(in);
    }

    PrivatePlayerDTO(): DTO(DTOSerial::PLAYER_PRIVATE) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
        out.push_back(player_id);
        out.push_back(player_hp);
        current_weapon.serialize_into(out);
        serialize_int_into(out, total_money);
        out.push_back(rounds_won);
        out.push_back(total_kills);
    }

    PrivatePlayerDTO(const PrivatePlayerDTO&) = delete;
    PrivatePlayerDTO& operator=(const PrivatePlayerDTO&) = delete;

    PrivatePlayerDTO(PrivatePlayerDTO&&) = default;
    PrivatePlayerDTO& operator=(PrivatePlayerDTO&&) = default;

    ~PrivatePlayerDTO() = default;
};

class PlayerDTO: public DTO {
public:
    uint8_t player_id;
    std::string player_name;
    uint8_t team_id;  // 0 para terroristas, 1 para counter

    // Armas
    // Para poder ser visualizada por otros jugadores
    WeaponName current_weapon;
    bool has_bomb;

    // animaciones y sonidos
    bool is_shooting;
    bool was_hurt;
    bool is_walking;
    bool is_dead;

    // coordenadas del jugador
    float x;
    float y;

    // coordenadas del mouse
    float aim_x;
    float aim_y;

private:
    void deserialize_from(std::vector<uint8_t>::iterator& in) override {
        in++;  // skip 1st byte (DTO type)
        player_id = *in++;
        // player_name = deserialize_string_from(in);
        team_id = *in++;
        current_weapon = static_cast<WeaponName>(*in++);
        has_bomb = *in++;
        is_shooting = *in++;
        was_hurt = *in++;
        is_walking = *in++;
        is_dead = *in++;
        Position pos = deserialize_pos_from(in);
        x = pos.x;
        y = pos.y;
        Position aim = deserialize_pos_from(in);
        aim_x = aim.x;
        aim_y = aim.y;
    }

public:
    explicit PlayerDTO(std::vector<uint8_t>&& bytes): DTO(std::move(bytes)) {
        auto payload_it = payload.begin();
        deserialize_from(payload_it);
    }

    explicit PlayerDTO(std::vector<uint8_t>::iterator& in):
        DTO(DTOSerial::PLAYER) {
        deserialize_from(in);
    }

    PlayerDTO(): DTO(DTOSerial::PLAYER) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
        out.push_back(player_id);
        // serialize_string_into(out, player_name);
        out.push_back(team_id);
        out.push_back(static_cast<uint8_t>(current_weapon));
        out.push_back(has_bomb);
        out.push_back(is_shooting);
        out.push_back(was_hurt);
        out.push_back(is_walking);
        out.push_back(is_dead);

        serialize_tuple_into(out, x, y);
        serialize_tuple_into(out, aim_x, aim_y);
    }

    PlayerDTO(const PlayerDTO&) = delete;
    PlayerDTO& operator=(const PlayerDTO&) = delete;

    PlayerDTO(PlayerDTO&&) = default;
    PlayerDTO& operator=(PlayerDTO&&) = default;

    ~PlayerDTO() = default;
};

class SnapshotDTO: public DTO {
public:
    bool round_finished = false;
    bool game_finished = false;
    bool initial_phase = true;

    // medido en segundos
    uint time_left = 60 * 5;

    uint8_t round_number = 0;
    uint8_t terrorists_score = 0;
    uint8_t counter_terrorists_score = 0;

    std::vector<PlayerDTO> players;
    std::vector<WeaponDTO> weapons_on_floor;

private:
    void deserialize_from(std::vector<uint8_t>::iterator& in) override {
        // Deserializar campos snapshot
        in++;  // skip 1st byte (DTO type)
        round_number = *in++;
        size_t num_players = *in++;
        for (size_t j = 0; j < num_players; ++j) {
            PlayerDTO player(in);
            players.push_back(std::move(player));
        }
        // armas en el suelo
        size_t num_weapons_on_floor = *in++;
        for (size_t j = 0; j < num_weapons_on_floor; ++j) {
            WeaponDTO weapon(in);
            weapons_on_floor.push_back(std::move(weapon));
        }
    }

public:
    explicit SnapshotDTO(std::vector<uint8_t>&& bytes): DTO(std::move(bytes)) {
        auto payload_it = payload.begin();
        deserialize_from(payload_it);
    }

    explicit SnapshotDTO(std::vector<uint8_t>::iterator& in):
        DTO(DTOSerial::SNAPSHOT) {
        deserialize_from(in);
    }

    SnapshotDTO(): DTO(DTOSerial::SNAPSHOT) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
        // Serializar campos snapshot
        out.push_back(round_number);

        // jugadores
        out.push_back(players.size());
        for (auto& player : players) {
            player.serialize_into(out);
        }
        // armas en el suelo
        out.push_back(weapons_on_floor.size());
        for (auto& weapon : weapons_on_floor) {
            weapon.serialize_into(out);
        }
    }

    SnapshotDTO(const SnapshotDTO&) = delete;
    SnapshotDTO& operator=(const SnapshotDTO&) = delete;

    SnapshotDTO(SnapshotDTO&&) = default;
    SnapshotDTO& operator=(SnapshotDTO&&) = default;

    ~SnapshotDTO() = default;
};

#endif
