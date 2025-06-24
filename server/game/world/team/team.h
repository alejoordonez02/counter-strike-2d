#ifndef SERVER_GAME_WORLD_TEAM_H
#define SERVER_GAME_WORLD_TEAM_H

#include "server/game/factory/player_factory.h"
#include "server/game/world/player.h"

class Team {
private:
    int max_players;

protected:
    int won_rounds;
    std::vector<std::shared_ptr<Player>> players;

    Team(std::vector<std::shared_ptr<Player>> players, int won_rounds);

    bool players_are_alive();

    void switch_player_sides();

    void restart_players();

public:
    Team() = default;

    void update(float dt);

    virtual std::shared_ptr<Player> add_player(
        int id, const PlayerFactory& player_factory) = 0;

    virtual void restart() = 0;

    void sum_won_round();

    int get_won_rounds();

    virtual bool lost_round(const BombState& bomb, const Timer& round_time) = 0;

    void switch_sides(Team& other);

    bool is_full() const { return players.size() >= max_players; }

    void push_player_data(std::vector<PlayerDTO>& data);
};

#endif
