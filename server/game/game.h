#ifndef GAME_H
#define GAME_H

#include <chrono>

#include "common/thread.h"
#include "player_handler.h"
#include "world/world.h"

using Duration = std::chrono::duration<float>;
using Clock = std::chrono::steady_clock;
using Ms = std::chrono::milliseconds;

class Game: public Thread {
private:
    std::mutex m;
    std::vector<std::pair<Connection, TeamName>> pending;
    std::vector<std::unique_ptr<PlayerHandler>> players;
    World world;
    Clock::duration tick_duration;
    int commands_per_tick;

    void add_pending_players();

public:
    Game(World&& world, int tick_rate, int commands_per_tick);

    void run() override;

    void add_player(Connection&& con, TeamName team);

    bool team_is_full(TeamName team) const { return world.team_is_full(team); }
};

#endif
