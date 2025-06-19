#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <memory>
#include <string>

#include "common/network/dtos/game_details_dto.h"
#include "common/map_name.h"
#include "server/client_session.h"
#include "common/queue.h"
#include "common/thread.h"
#include "server/model/game.h"
#include "server/player_handler.h"

// #define MAX_PLAYERS 10
class Player;

class GameLoop: public Thread {
private:
    const std::string name;
    // int n_players;
    MapName map_name; // falta usar esto para construir Game
    bool _is_joinable;
    Game game;
    std::vector<ClientSession*> clients;
    std::vector<PlayerHandler*> handlers;

public:
    GameLoop(const std::string& name, MapName mn): name(name), map_name(mn), _is_joinable(true) {}

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

