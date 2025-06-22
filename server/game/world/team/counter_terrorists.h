#ifndef SERVER_GAME_WORLD_TEAM_COUNTER_TERRORISTS_H
#define SERVER_GAME_WORLD_TEAM_COUNTER_TERRORISTS_H

#include "team.h"

class CounterTerrorists: public Team {
public:
    std::shared_ptr<Player> add_player(
        int id, const PlayerFactory& player_factory) override {
        auto p = player_factory.create(id, TeamName::COUNTER_TERRORIST);
        players.push_back(p);
        return p;
    }

    bool lost_round(const BombState& bomb, const Timer& round_time) override {
        if (bomb == BombState::EXPLODED) return true;
        if (bomb == BombState::PLANTED && !players_are_alive()) return true;
        return false;
    }
};

#endif
