#include "player_factory.h"

#include "server/game/world/counter_terrorist.h"
#include "server/game/world/terrorist.h"

PlayerFactory::PlayerFactory(std::shared_ptr<Map> map,
                             const PlayerConfig& config):
    map(std::move(map)), config(config) {}

std::shared_ptr<Player> PlayerFactory::create(int id, TeamName team) const {
    switch (team) {
        case TeamName::TERRORIST:
            return std::make_shared<Terrorist>(
                id, map, config.max_velocity, config.acceleration,
                config.radius, config.starting_money, config.max_health);
        case TeamName::COUNTER_TERRORIST:
            return std::make_shared<CounterTerrorist>(
                id, map, config.max_velocity, config.acceleration,
                config.radius, config.starting_money, config.max_health);
        default:
            throw std::runtime_error("Unknown team");
    }
}
