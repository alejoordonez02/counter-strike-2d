#include "terrorists.h"

#include <vector>

#include "server/game/world/player.h"

std::shared_ptr<Player> Terrorists::add_player(
    int id, const PlayerFactory& player_factory) {
    auto p = player_factory.create(id, TeamName::TERRORIST);
    players.push_back(p);
    return p;
}

bool Terrorists::lost_round(const BombState& bomb, const Timer& round_time) {
    if (bomb == BombState::DEFUSED) return true;
    if (bomb == BombState::NOT_PLANTED && !players_are_alive()) return true;
    return false;
}
