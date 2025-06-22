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

// armas en el suelo
struct WeaponDTO {
    uint32_t weapon_id;

    WeaponType type;
    int16_t x;
    int16_t y;
};

struct YourPlayerData {
    uint16_t player_id;
    uint16_t player_hp;
    
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

struct SnapshotDTO {
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
};

class SnapshotDTOB: public DTO {
private:
    // SnapshotDTO snapshot;

    void deserialize_from(std::vector<uint8_t>::iterator& in) override {
        // Deserializar campos snapshot
        in++;  // skip 1st byte (DTO type)
        snapshot.round_number = *in++;
        size_t num_players = *in++;
        snapshot.players.clear();
        snapshot.players.reserve(num_players);
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
            snapshot.players.push_back(player);
        }
    }

public:
    SnapshotDTO snapshot;

    explicit SnapshotDTOB(std::vector<uint8_t>&& bytes): DTO(std::move(bytes)) {
        auto payload_it = payload.begin();
        deserialize_from(payload_it);
    }

    explicit SnapshotDTOB(std::vector<uint8_t>::iterator& in):
            DTO(DTOSerial::PlayerCommands::SNAPSHOT) {
        deserialize_from(in);
    }

    explicit SnapshotDTOB(const SnapshotDTO& snap):
            DTO(DTOSerial::PlayerCommands::SNAPSHOT), snapshot(snap) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
        // Serializar campos snapshot
        out.push_back(snapshot.round_number);

        // jugadores
        out.push_back(snapshot.players.size());
        for (const auto& player : snapshot.players) {
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
    }

    ~SnapshotDTOB() = default;
};

#endif
