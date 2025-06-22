#ifndef SERVER_GAME_WORLD_TEAM_H
#define SERVER_GAME_WORLD_TEAM_H

#include "server/game/factory/player_factory.h"
#include "server/game/world/player.h"

class Team {
protected:
    int won_rounds;
    std::vector<std::shared_ptr<Player>> players;

    Team(std::vector<std::shared_ptr<Player>> players, int won_rounds);

    bool players_are_alive();

    void switch_player_sides();

public:
    Team() = default;

    void update(float dt);

    virtual std::shared_ptr<Player> add_player(
        int id, const PlayerFactory& player_factory) = 0;

    void restart();

    void sum_won_round();

    int get_won_rounds();

    virtual bool lost_round(const BombState& bomb, const Timer& round_time) = 0;

    void switch_sides(Team& other);

    void push_player_data(std::vector<PlayerData>& data);
};

#endif
