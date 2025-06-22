#ifndef SERVER_GAME_WORLD_TEAM_H
#define SERVER_GAME_WORLD_TEAM_H

#include "server/game/factory/player_factory.h"
#include "server/game/world/player.h"

class Team {
protected:
    int won_rounds;
    std::vector<std::shared_ptr<Player>> players;

    Team(std::vector<std::shared_ptr<Player>> players, int won_rounds);

    bool players_are_alive() {
        bool alive = true;
        for (auto& p : players) alive &= p->is_alive();
        return alive;
    }

    void switch_player_sides() {
        for (auto& p : players) p->switch_side();
    }

public:
    Team() = default;

    void update(float dt) {
        for (auto& p : players) p->update(dt);
    }

    virtual std::shared_ptr<Player> add_player(
        int id, const PlayerFactory& player_factory) = 0;

    void restart() {
        for (auto& p : players) p->restart();
    }

    int get_won_rounds() { return won_rounds; }

    virtual bool lost_round(const BombState& bomb, const Timer& round_time) = 0;

    void switch_sides(Team& other) {
        switch_player_sides();
        other.switch_player_sides();
        auto won_rounds_tmp = std::move(other.won_rounds);
        auto players_tmp = std::move(other.players);
        other.won_rounds = std::move(won_rounds);
        other.players = std::move(players);
        won_rounds = std::move(won_rounds_tmp);
        players = std::move(players_tmp);
    }

    void push_player_data(std::vector<PlayerData>& data) {
        for (auto& p : players) data.push_back(p->get_data());
    }
};

#endif
