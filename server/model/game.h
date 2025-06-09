#ifndef GAME_H
#define GAME_H

#include <map>
#include <string>

#include "map.h"
#include "player.h"

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
        for (auto& p: players) p.second->update(dt);
    }
};

#endif
