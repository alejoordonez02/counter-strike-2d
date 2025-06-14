#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <chrono>

#include "common/thread.h"
#include "server/model/game.h"
#include "server/player_handler.h"

using Duration = std::chrono::duration<float>;
using Clock = std::chrono::steady_clock;
using Ms = std::chrono::milliseconds;

class GameLoop: public Thread {
private:
    std::vector<std::unique_ptr<PlayerHandler>> players;
    Game game;
    Clock::duration tick_duration;

public:
    GameLoop(std::vector<std::unique_ptr<PlayerHandler>>&& handlers,
             std::vector<std::shared_ptr<Player>>&& players,
             std::shared_ptr<Map>&& map, int tick_rate, int rounds,
             float round_time, float time_out):
            players(std::move(handlers)),
            game(std::move(players), std::move(map), rounds, round_time,
                 time_out),
            tick_duration(Ms(1000) / tick_rate) {}

    void run() override {
        auto t1 = Clock::now();
        float elapsed_seconds = Duration(tick_duration).count();
        while (should_keep_running()) {
            auto snapshot = game.get_snapshot();
            for (auto& p : players) p->send_snapshot(snapshot);

            for (auto& p : players) p->play();

            game.update(elapsed_seconds);
            auto t2 = Clock::now();
            auto work_time = t2 - t1;
            auto rest_time = tick_duration - work_time;
            if (rest_time.count() > 0) {
                std::this_thread::sleep_for(rest_time);
                t1 += tick_duration;
            }

            std::cout << "tick!\n";
        }
    }
};

#endif
