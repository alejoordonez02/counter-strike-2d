#include "player_factory.h"

#include "server/game/world/counter_terrorist.h"
#include "server/game/world/terrorist.h"

PlayerFactory::PlayerFactory(std::shared_ptr<Map> map,
                             const PlayerConfig& config,
                             std::shared_ptr<WeaponFactory> weapon_factory):
    map(std::move(map)), config(config), weapon_factory(weapon_factory) {}

/* int id,
   std::shared_ptr<Weapon> primary,
   std::shared_ptr<Weapon> secondary,
   std::shared_ptr<Weapon> knife,
   std::weak_ptr<Map> map,
   float max_velocity,
   float acceleration,
   float radius,
   int money,
   int health,
   std::shared_ptr<WeaponFactory> weapon_factory); */
std::shared_ptr<Player> PlayerFactory::create(int id, TeamName team) const {
    switch (team) {
        case TeamName::TERRORIST:
            return std::make_shared<Terrorist>(
                id, nullptr, weapon_factory->create(WeaponName::GLOCK),
                weapon_factory->create(WeaponName::KNIFE), map,
                config.max_velocity, config.acceleration, config.radius,
                config.starting_money, config.max_health, weapon_factory);
        case TeamName::COUNTER_TERRORIST:
            return std::make_shared<CounterTerrorist>(
                id, nullptr, weapon_factory->create(WeaponName::GLOCK),
                weapon_factory->create(WeaponName::KNIFE), map,
                config.max_velocity, config.acceleration, config.radius,
                config.starting_money, config.max_health, weapon_factory);
        default:
            throw std::runtime_error("Unknown team");
    }
}
