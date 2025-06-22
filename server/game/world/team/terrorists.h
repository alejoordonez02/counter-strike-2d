#ifndef SERVER_GAME_WORLD_TEAM_TERRORISTS_H
#define SERVER_GAME_WORLD_TEAM_TERRORISTS_H

#include "server/game/world/player.h"
#include "team.h"

class Terrorists: public Team {
public:
    std::shared_ptr<Player> add_player(
        int id, const PlayerFactory& player_factory) override;

    bool lost_round(const BombState& bomb, const Timer& round_time) override;
};

#endif
