#ifndef GAME_H
#define GAME_H

#include <chrono>

#include "common/thread.h"
#include "config/game_config.h"
#include "server/player_handler.h"
#include "server/world/world.h"

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

    World create_world(const GameConfig& config);

    void add_pending_players();

public:
    /*
     * Acá estaría bueno poder pasarle la game config para que la use para
     * construirse
     * */
    Game(const GameConfig& config);

    void run() override;

    void add_player(Connection&& con, TeamName team);
};

#endif
