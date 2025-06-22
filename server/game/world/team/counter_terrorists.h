#ifndef SERVER_GAME_WORLD_TEAM_COUNTER_TERRORISTS_H
#define SERVER_GAME_WORLD_TEAM_COUNTER_TERRORISTS_H

#include "team.h"

class CounterTerrorists: public Team {
public:
    std::shared_ptr<Player> add_player(
        int id, const PlayerFactory& player_factory) override;

    bool lost_round(const BombState& bomb, const Timer& round_time) override;
};

#endif
