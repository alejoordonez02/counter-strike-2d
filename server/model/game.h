#ifndef SERVER_MODEL_GAME_H
#define SERVER_MODEL_GAME_H

#include <map>
#include <memory>
#include <string>
#include <utility>

#include "server/model/map.h"
#include "server/model/player.h"

class Game {
    private:
    std::map<std::string, std::unique_ptr<Player>> players;
    Map map;

    public:
    Game() = default;

    void add_player(const std::string& id, std::unique_ptr<Player> p) {
        map.add_collidable(p->get_physics());
        players[id] = std::move(p);
    }

    Player& get_player(const std::string& id) { return *players.at(id); }

    void update(float dt) {
        for (auto& p : players) p.second->update(dt);
    }
};

#endif
