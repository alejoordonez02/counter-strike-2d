#include "game.h"

#include <memory>
#include <utility>

#include "../game_setup.h"
#include "server/model/map.h"
#include "server/model/player.h"

/*
 * Check if any team won the round
 * */
bool Game::terrorists_won_round() const {
    return map->bomb_has_exploded();

    /* bool all_alive;
    for (auto& p : players) all_alive &= p->is_alive();
    return all_alive; */
}

bool Game::counter_terrorists_won_round() const {
    return map->bomb_is_defused();

    /* bool all_alive;
    for (auto& p : players) all_alive &= p->is_alive();
    return all_alive; */
}

/*
 * Update rounds
 * */
void Game::start_round() {
    for (auto& p : players) p->restart();
    map->restart();
    round_time.restart();
}

void Game::sum_round(int& team_won_rounds) {
    team_won_rounds++;
    if (tt_won_rounds + ct_won_rounds >= rounds) ended = true;

    start_round();
}

void Game::update_rounds(float dt) {
    round_time.update(dt);

    if (terrorists_won_round())
        return sum_round(tt_won_rounds);

    else if (round_time.is_done() || counter_terrorists_won_round())
        return sum_round(ct_won_rounds);
}

/*
 * Constructor
 * */
Game::Game(std::shared_ptr<Map>&& map, int rounds, float round_time,
           float time_out):
    map(std::move(map)), rounds(rounds), round_time(round_time),
    time_out(time_out), round_ongoing(false), ended(false), tt_won_rounds(0),
    ct_won_rounds(0) {}

/*
 * Update world
 * */
void Game::update(float dt) {
    if (ended) return;

    int updates = 1;
    if (dt > DT) {
        updates = (int)(dt / DT);
        dt = DT;
    }

    for (int i = 0; i < updates; i++) {
        for (auto& p : players) p->update(dt);
        map->update(dt);
        update_rounds(dt);
    }
}

/*
 * Add a player
 * */
std::shared_ptr<Player> Game::add_player() {
    auto p = GameSetup::create_player(map);
    map->add_collidable(p);
    players.push_back(p);
    return p;
}

/*
 * Check wheter the game has ended
 * */
bool Game::has_ended() const { return ended; }

/*
 * Get a snapshot of the current state of the world
 * */
Snapshot Game::get_snapshot() {
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
