#ifndef COMMON_SNAPSHOT_H
#define COMMON_SNAPSHOT_H

#include <cstdint>
#include <vector>

#include <sys/types.h>

#define MAX_PLAYER_NAME 32

enum class WeaponType { None, Bomb, Knife, Glock, AK47, M3, AWP };

// armas en el suelo
struct WeaponDTO {
    uint32_t weapon_id;

    WeaponType type;
    int16_t x;
    int16_t y;
};

struct PlayerData {
    uint16_t player_id;
    char player_name[MAX_PLAYER_NAME];
    uint8_t team_id;  // 0 para terroristas, 1 para counter
    uint16_t player_hp;

    // Armas
    // El cuchillo siempre lo tienen
    // WeaponType primaryGun;
    // WeaponType secondaryGun;
    WeaponType
            current_weapon;  // Para poder ser visualizada por otros jugadores
    bool has_bomb;

    // estadisticas
    uint8_t rounds_won = 0;
    uint8_t total_kills = 0;
    uint8_t total_money = 0;

    // animaciones y sonidos
    bool is_shooting;
    bool was_hurt;
    bool is_walking;
    bool is_dead;

    // coordenadas del jugador
    int16_t x;
    int16_t y;

    // coordenadas del mouse
    int16_t aim_x;
    int16_t aim_y;
};

struct Snapshot {
    bool round_finished = false;
    bool game_finished = false;
    bool initial_phase = true;

    uint8_t round_number = 0;
    uint8_t terrorists_score = 0;
    uint8_t counter_terrorists_score = 0;

    std::vector<PlayerData> players;
    std::vector<WeaponDTO> weapons_on_floor;
};

#endif
