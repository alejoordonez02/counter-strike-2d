#include "counter_terrorists.h"

std::shared_ptr<Player> CounterTerrorists::add_player(
    int id, const PlayerFactory& player_factory) {
    auto p = player_factory.create(id, TeamName::COUNTER_TERRORIST);
    players.push_back(p);
    return p;
}

void CounterTerrorists::restart() { restart_players(); }

bool CounterTerrorists::lost_round(const BombState& bomb,
                                   const Timer& round_time) {
    if (bomb == BombState::EXPLODED) return true;
    if (bomb != BombState::DEFUSED && !players_are_alive()) return true;
    return false;
}
