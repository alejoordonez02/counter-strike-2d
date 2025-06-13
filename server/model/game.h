#ifndef SERVER_MODEL_GAME_H
#define SERVER_MODEL_GAME_H

#include <memory>
#include <utility>

#include "server/model/map.h"
#include "server/model/player.h"

class Game {
private:
    std::vector<std::shared_ptr<Player>> players;
    Map map;
    int rounds;
    Timer round_time;
    float time_out;
    bool round_ongoing;
    bool ended;
    int tt_won_rounds;
    int ct_won_rounds;

    bool terrorists_won_round() const {
        return map.bomb_has_exploded();

        /* bool all_alive;
        for (auto& p : players) all_alive &= p->is_alive();
        return all_alive; */
    }

    bool counter_terrorists_won_round() const {
        return map.bomb_is_defused();

        /* bool all_alive;
        for (auto& p : players) all_alive &= p->is_alive();
        return all_alive; */
    }

    void start_round() {
        for (auto& p : players) p->restart();
        map.restart();
        round_time.restart();
    }

    void sum_round(int& team_won_rounds) {
        team_won_rounds++;
        if (tt_won_rounds + ct_won_rounds >= rounds)
            ended = true;

        start_round();
    }

    void update_rounds(float dt) {
        round_time.update(dt);

        if (terrorists_won_round())
            return sum_round(tt_won_rounds);

        else if (round_time.is_done() || counter_terrorists_won_round())
            return sum_round(ct_won_rounds);
    }

public:
    Game(std::vector<std::shared_ptr<Player>> players, Map&& map, int rounds,
         float round_time, float time_out):
            /* game(std::move(players), std::move(map), rounds, round_time,
                 time_out), */

            players(players),
            map(std::move(map)),
            rounds(rounds),
            round_time(round_time),
            time_out(time_out),
            round_ongoing(false),
            ended(false),
            tt_won_rounds(0),
            ct_won_rounds(0) {}

    void update(float dt) {
        if (ended)
            return;

        for (auto& p : players) p->update(dt);
        map.update(dt);
        update_rounds(dt);
    }

    Snapshot get_snapshot() {
        Snapshot snapshot;
        snapshot.round_finished = !round_ongoing;
        snapshot.game_finished = ended;
        snapshot.initial_phase = true;  // ?
        snapshot.round_number = tt_won_rounds + ct_won_rounds;
        snapshot.terrorists_score = tt_won_rounds;
        snapshot.counter_terrorists_score = ct_won_rounds;
        for (auto& p : players) snapshot.players.push_back(p->get_data());

        return snapshot;
    }

    bool has_ended() const { return ended; }
};

#endif
