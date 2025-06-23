#ifndef COMMON_NETWORK_DTOS_SNAPSHOT_DTO_H
#define COMMON_NETWORK_DTOS_SNAPSHOT_DTO_H

#include <cstdint>
#include <utility>
#include <vector>

#include <sys/types.h>

#include "common/network/dto.h"
#include "common/network/protocol.h"

#define MAX_PLAYER_NAME 32

enum class WeaponType { None, Bomb, Knife, Glock, AK47, M3, AWP };

enum class EquipmentType { Primary, Secondary, Knife, Bomb};

// armas en el suelo
struct WeaponDTO {
    WeaponType type;
    int16_t x;
    int16_t y;
};

struct YourPlayerData {
    uint8_t player_id;
    uint8_t player_hp;
    
    uint total_money = 0;

    // estadisticas
    uint8_t rounds_won = 0;
    uint8_t total_kills = 0;
};

struct PlayerData {
    uint8_t player_id;
    char player_name[MAX_PLAYER_NAME];
    uint8_t team_id;  // 0 para terroristas, 1 para counter

    // Armas
    // Para poder ser visualizada por otros jugadores
    WeaponType current_weapon;  
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

    YourPlayerData user_data;
    std::vector<PlayerData> players;
    std::vector<WeaponDTO> weapons_on_floor;

private:
    void deserialize_from(std::vector<uint8_t>::iterator& in) override {
        // Deserializar campos snapshot
        in++;  // skip 1st byte (DTO type)
        round_number = *in++;
        size_t num_players = *in++;
        players.clear();
        players.reserve(num_players);
        for (size_t j = 0; j < num_players; ++j) {
            PlayerData player;
            player.player_id = *in++;
            player.team_id = *in++;
            player.current_weapon = static_cast<WeaponType>(*in++);
            player.has_bomb = *in++;
            player.is_shooting = *in++;
            player.was_hurt = *in++;
            player.is_walking = *in++;
            player.is_dead = *in++;
            Position pos = deserialize_pos_from(in);
            player.x = pos.x;
            player.y = pos.y;
            Position aim = deserialize_pos_from(in);
            player.aim_x = aim.x;
            player.aim_y = aim.y;
            players.push_back(player);
        }
        // armas en el suelo
        size_t num_weapons_on_floor = *in++;
        weapons_on_floor.clear();
        weapons_on_floor.reserve(num_weapons_on_floor);
        for (size_t j = 0; j < num_weapons_on_floor; ++j) {
            WeaponDTO weapon;
            weapon.type = static_cast<WeaponType>(*in++);
            Position pos = deserialize_pos_from(in);
            weapon.x = pos.x;
            weapon.y = pos.y;
            weapons_on_floor.push_back(weapon);
        }
        user_data.player_id = *in++;
        user_data.player_hp = *in++;
        user_data.total_money = deserialize_int_from(in);
        user_data.rounds_won = *in++;
        user_data.total_kills = *in++;
    }

public:
    explicit SnapshotDTO(std::vector<uint8_t>&& bytes): DTO(std::move(bytes)) {
        auto payload_it = payload.begin();
        deserialize_from(payload_it);
    }

    explicit SnapshotDTO(std::vector<uint8_t>::iterator& in):
            DTO(DTOSerial::PlayerCommands::SNAPSHOT) {
        deserialize_from(in);
    }

    SnapshotDTO(): DTO(DTOSerial::PlayerCommands::SNAPSHOT) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
        // Serializar campos snapshot
        out.push_back(round_number);

        // jugadores
        out.push_back(players.size());
        for (const auto& player : players) {
            out.push_back(player.player_id);
            out.push_back(player.team_id);
            out.push_back(static_cast<uint8_t>(player.current_weapon));
            out.push_back(player.has_bomb);

            out.push_back(player.is_shooting);
            out.push_back(player.was_hurt);
            out.push_back(player.is_walking);
            out.push_back(player.is_dead);
            
            serialize_tuple_into(out, player.x, player.y);
            serialize_tuple_into(out, player.aim_x, player.aim_y);
        }
        // armas en el suelo
        out.push_back(weapons_on_floor.size());
        for (const auto& weapon : weapons_on_floor) {
            out.push_back(static_cast<uint8_t>(weapon.type));
            serialize_tuple_into(out, weapon.x, weapon.y);
        }
        out.push_back(user_data.player_id);
        out.push_back(user_data.player_hp);
        serialize_int_into(out, user_data.total_money);
        out.push_back(user_data.rounds_won);
        out.push_back(user_data.total_kills);
    }

    SnapshotDTO(const SnapshotDTO&) = delete;
    SnapshotDTO& operator=(const SnapshotDTO&) = delete;
    
    SnapshotDTO(SnapshotDTO&&) = default;
    SnapshotDTO& operator=(SnapshotDTO&&) = default;

    ~SnapshotDTO() = default;
};

#endif
