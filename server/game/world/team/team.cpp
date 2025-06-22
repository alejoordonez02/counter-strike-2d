#include "team.h"

bool Team::players_are_alive() {
    bool alive = true;
    for (auto& p : players) alive &= p->is_alive();
    return alive;
}

void Team::switch_player_sides() {
    for (auto& p : players) p->switch_side();
}

void Team::update(float dt) {
    for (auto& p : players) p->update(dt);
}

void Team::restart() {
    for (auto& p : players) p->restart();
}

int Team::get_won_rounds() { return won_rounds; }

void Team::switch_sides(Team& other) {
    switch_player_sides();
    other.switch_player_sides();
    auto won_rounds_tmp = std::move(other.won_rounds);
    auto players_tmp = std::move(other.players);
    other.won_rounds = std::move(won_rounds);
    other.players = std::move(players);
    won_rounds = std::move(won_rounds_tmp);
    players = std::move(players_tmp);
}

void Team::push_player_data(std::vector<PlayerData>& data) {
    for (auto& p : players) data.push_back(p->get_data());
}
