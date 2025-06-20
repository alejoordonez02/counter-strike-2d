#ifndef SERVER_CONFIG_WORLD_CONFIG_H
#define SERVER_CONFIG_WORLD_CONFIG_H

struct WorldConfig {
    int rounds;
    float round_time;
    float time_out;
    float player_max_velocity;
    float player_acceleration;
    float player_radius;
    int player_starting_money;
    int player_max_health;
};

#endif
