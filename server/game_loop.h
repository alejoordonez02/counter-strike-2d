#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <memory>
#include <string>

#include "common/map_name.h"
#include "common/network/dtos/game_details_dto.h"
#include "common/queue.h"
#include "common/thread.h"

class ClientSession;

class GameLoop: public Thread {
    private:
    const std::string name;
    MapName mn;
    Queue<ClientSession*> incoming_clients;
    bool _has_started;

    public:
    GameLoop(const std::string& name, MapName map_name);

    void run() override;

    std::unique_ptr<GameDetailsDTO> get_details();

    bool has_started() const;

    void add_client(ClientSession* c_session);

    ~GameLoop() = default;
};

#endif
