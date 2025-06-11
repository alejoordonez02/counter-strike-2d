#include "server/game_loop.h"

#include "common/map_name.h"
#include "common/network/dtos/game_details_dto.h"
#include "common/queue.h"
#include "server/client_session.h"

GameLoop::GameLoop(const std::string& name, MapName map_name):
        name(name), mn(map_name) {}

void GameLoop::run() {}

// std::unique_ptr<GameDetailsDTO> GameLoop::get_details() {}

bool GameLoop::has_started() const { return _has_started; }

void GameLoop::add_client(ClientSession* c_session) {
    incoming_clients.push(c_session);
}
