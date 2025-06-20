#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <chrono>

#include "common/thread.h"
#include "server/model/game.h"
#include "server/player_handler.h"

using Duration = std::chrono::duration<float>;
using Clock = std::chrono::steady_clock;
using Ms = std::chrono::milliseconds;

/*
 * Es importante que una sóla clase conozca GameSetup. En realidad, GameSetup
 * debería ser GameConfig, GameLoop Game y Game World, son sólo nombres, pero a
 * lo que voy es a las responsabilidades que los mismos implican para cada clase
 * */
class GameLoop: public Thread {
private:
    std::mutex m;
    std::vector<Connection> pending;
    std::vector<std::unique_ptr<PlayerHandler>> players;
    Game game;
    Clock::duration tick_duration;
    int commands_per_tick;

    void add_pending_players();

public:
    /*
     * Acá estaría bueno poder pasarle la game config para que la use para
     * construirse
     * */
    GameLoop(/* GameConfig& config */);

    void run() override;

    void add_player(Connection&& con);
};

#endif
