#ifndef SERVER_MODEL_GAME_H
#define SERVER_MODEL_GAME_H

#include <map>
#include <memory>
#include <string>
#include <utility>

#include "server/model/map.h"
#include "server/model/player.h"

#define N_ROUNDS 15
#define ROUND_TIME 600
#define TIME_OUT 20

class Game {
private:
    Map map;
    std::map<std::string, std::unique_ptr<Player>> players;
    bool round_ongoing;
    bool ended;
    Timer round_time;
    float time_out;
    int tt_won_rounds;
    int ct_won_rounds;

    bool terrorists_won_round() const {
        if (map.bomb_has_exploded())
            return true;

        bool all_alive;
        for (auto& p : players) all_alive &= p.second->is_alive();
        return all_alive;
    }

    bool counter_terrorists_won_round() const {
        if (map.bomb_is_defused())
            return true;

        if (round_time.is_done() && !map.bomb_has_exploded())
            return true;

        bool all_alive;
        for (auto& p : players) all_alive &= p.second->is_alive();
        return all_alive;
    }

    void start_round() {
        for (auto& p : players) p.second->restart();
        map.restart();
        round_time.restart();
    }

    void sum_round(int& team_won_rounds) {
        team_won_rounds++;
        if (tt_won_rounds + ct_won_rounds >= N_ROUNDS)
            ended = true;

        start_round();
    }

    void update_rounds(float dt) {
        if (terrorists_won_round())
            return sum_round(tt_won_rounds);

        else if (counter_terrorists_won_round())
            return sum_round(ct_won_rounds);
    }

public:
    Game(Map&& map):
            map(std::move(map)),
            players(),
            round_time(ROUND_TIME),
            tt_won_rounds(0),
            ct_won_rounds(0) {}

    void update(float dt) {
        if (ended)
            return;

        for (auto& p : players) p.second->update(dt);
        map.update(dt);
        update_rounds(dt);
    }

    bool has_ended() const { return ended; }

    void add_player(const std::string& id, std::unique_ptr<Player> p) {
        map.add_collidable(p->get_physics());
        players[id] = std::move(p);
    }

    Player& get_player(const std::string& id) { return *players.at(id); }
};

#endif
