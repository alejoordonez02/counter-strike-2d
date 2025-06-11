#include "server/game_loop.h"

#include <chrono>

#include "common/map_name.h"
#include "common/network/dtos/game_details_dto.h"
#include "common/queue.h"
#include "server/client_session.h"
#include "server/model/player.h"
// #include "server/client_cmds/cmd.h"
#include "server/model/game.h"
#include "server/model/terrorist.h"

#define TICKS_PER_SECOND 64
#define TICK_DURATION 1 / TICKS_PER_SECOND
#define MAX_N_CLIENTS 2

GameLoop::GameLoop(const std::string& name, MapName map_name):
        name(name), mn(map_name) {}
/* Game game;
const std::string name;
MapName mn;
Queue<ClientSession*> incoming_clients;
bool _has_started; */

class ClientCommand;

void GameLoop::run() {
    Map map;

    ClientSession* creator;
    incoming_clients.try_pop(creator);
    clients[creator] = std::make_unique<Terrorist>(Position(0, 0), map);

    /*
     * Conectarse a la partida
     * */
    int n_clients = 1;
    while (should_keep_running()) {
        if (n_clients > MAX_N_CLIENTS)
            break;

        /*
         * Recibir comando del cliente para
         * checkear si arranca la partida
         * prematuramente (sin max_n_players)
         * */
        /* std::unique_ptr<Command> cmd;
        creator->try_pop_command(cmd); */

        /*
         * Join clients
         * */
        ClientSession* client;
        incoming_clients.try_pop(client);
        clients[client] = std::make_unique<Terrorist>(Position(0, 0), map);
        n_clients++;
    }

    Game game(std::move(map));

    /* for (auto& c : clients) {
        c.first->start_game_phase();
        game.add_
    } */

    /*
     * Elegir equipos
     * */
    /* while (should_keep_running()) {} */

    /*
     * Jugar partida
     * */
    using clock = std::chrono::steady_clock;
    auto last_time = clock::now();
    while (should_keep_running()) {
        auto now = clock::now();
        float dt = (now - last_time).count();

        // for (auto& c : clients)

        game.update(dt);
        last_time = now;
    }
}

// std::unique_ptr<GameDetailsDTO> GameLoop::get_details() {}

void GameLoop::add_client(ClientSession* c_session) {
    incoming_clients.push(c_session);
}
