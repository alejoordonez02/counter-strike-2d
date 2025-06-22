#ifndef SERVER_GAME_WORLD_TEAM_TERRORISTS_H
#define SERVER_GAME_WORLD_TEAM_TERRORISTS_H

#include <vector>

#include "server/game/world/player.h"
#include "team.h"

class Terrorists: public Team {
public:
    std::shared_ptr<Player> add_player(
        int id, const PlayerFactory& player_factory) override {
        auto p = player_factory.create(id, TeamName::TERRORIST);
        players.push_back(p);
        return p;
    }

    bool lost_round(const BombState& bomb, const Timer& round_time) override {
        if (bomb == BombState::DEFUSED) return true;
        if (bomb == BombState::NOT_PLANTED && !players_are_alive()) return true;
        return false;
    }
};

#endif
