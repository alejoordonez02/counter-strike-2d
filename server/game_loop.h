#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <chrono>

#include "common/network/dtos/game_details_dto.h"
#include "common/map_name.h"
#include "server/client_session.h"
#include "common/queue.h"
#include "common/thread.h"
#include "server/model/game.h"
#include "server/player_handler.h"

using Duration = std::chrono::duration<float>;
using Clock = std::chrono::steady_clock;
using Ms = std::chrono::milliseconds;
#include "server/model/game.h"
#include "server/player_handler.h"

// #define MAX_PLAYERS 10
class Player;

class GameLoop: public Thread {
private:
    std::vector<std::unique_ptr<PlayerHandler>> players;
    Game game;
    Clock::duration tick_duration;
    const std::string name;
    // int n_players;
    MapName map_name; // falta usar esto para construir Game
    bool _is_joinable;
    Game game;
    std::vector<ClientSession*> clients;
    std::vector<PlayerHandler*> handlers;

public:
    GameLoop(std::vector<std::unique_ptr<PlayerHandler>>&& handlers,
             std::vector<std::shared_ptr<Player>>&& players,
             std::shared_ptr<Map>&& map, int tick_rate, int rounds,
             float round_time, float time_out):
            players(std::move(handlers)),
            game(std::move(players), std::move(map), rounds, round_time,
                 time_out),
            tick_duration(Ms(1000) / tick_rate) {}
    GameLoop(const std::string& name, MapName mn): name(name), map_name(mn), _is_joinable(true) {}

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
    void run() override {
        // // en el while de team-selection:
        // if (not incoming_client.empty()) {
        //     if (++n_players == MAX_PLAYERS)
        //         incoming_client.close();
        //     // popearlo, agregarlo a clients, crearle Player, start_game_phase, etc
        // }
    }

    void start() override {
        Thread::start();
        _is_joinable = false;

        for (auto& c : clients)
            handlers.push_back(c->start_game_phase());
    }

    std::unique_ptr<GameDetailsDTO> get_details_dto() {
        return std::make_unique<GameDetailsDTO>(
            name,
            game.get_tt_count(),
            game.get_ct_count(),
            map_name,
            _is_joinable);
    }

    bool add_client(ClientSession* c_session, Team team) {
        std::shared_ptr<Player> p = game.add_player(/* cs->get_username(),  */team);
        if (not p)
            return false;

        c_session->set_player(p);
        clients.push_back(c_session);
        return true;
    }

    ~GameLoop() = default;
};

#endif

