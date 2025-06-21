#include "player_factory.h"

#include "counter_terrorist.h"
#include "terrorist.h"

PlayerFactory::PlayerFactory(std::shared_ptr<Map> map,
                             const WorldConfig& config):
    map(std::move(map)), config(config) {}

std::shared_ptr<Player> PlayerFactory::create(int id, TeamName team) const {
    switch (team) {
        case TeamName::TERRORIST:
            return std::make_shared<Terrorist>(
                id, map, config.player_max_velocity, config.player_acceleration,
                config.player_radius, config.player_starting_money,
                config.player_max_health, std::nullopt);
        case TeamName::COUNTER_TERRORIST:
            return std::make_shared<CounterTerrorist>(
                id, map, config.player_max_velocity, config.player_acceleration,
                config.player_radius, config.player_starting_money,
                config.player_max_health);
        default:
            throw std::runtime_error("Unknown team");
    }
}
