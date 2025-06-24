#include "map_factory.h"

#include "common/maploader.h"
#include "server/game/world/map.h"
#include "weapon_factory.h"

std::shared_ptr<Map> MapFactory::create(
    const MapData& config, std::shared_ptr<WeaponFactory> weapon_factory) {
    std::vector<std::shared_ptr<Hitbox>> collidables;
    std::vector<std::unique_ptr<Drop>> drops;
    std::vector<Structure> bomb_site;
    std::vector<Position> tt_spawn;
    std::vector<Position> ct_spawn;
    for (auto& block : config.blocks) {
        if (block.type == "Solid")
            collidables.push_back(
                std::make_shared<Structure>(Position(block.x, block.y), 32));
        else if (block.type == "Plantable")
            bomb_site.push_back(Structure(Position(block.x, block.y), 32));
        else if (block.type == "TSpawn")
            tt_spawn.push_back(Position(block.x, block.y));
        else if (block.type == "CtSpawn")
            ct_spawn.push_back(Position(block.x, block.y));
        /*
         * por ésto son malas las strings para las configs, 20 mins para darme
         * cuenta que había un typo en prueba-mapa-mod.yaml (medio boludo yo
         * igual xd)
         * TODO: typo
         * */
        else if (block.type == "DropedAk47") {
            auto drop = std::make_unique<WeaponDrop>(
                weapon_factory->create(WeaponName::AK47),
                Position(block.x, block.y));
        } else if (block.type == "DropedGlock") {
            auto drop = std::make_unique<WeaponDrop>(
                weapon_factory->create(WeaponName::GLOCK),
                Position(block.x, block.y));
        } else if (block.type == "DropedAwp") {
            auto drop = std::make_unique<WeaponDrop>(
                weapon_factory->create(WeaponName::AWP),
                Position(block.x, block.y));
        } else if (block.type == "DropedM3") {
            auto drop = std::make_unique<WeaponDrop>(
                weapon_factory->create(WeaponName::M3),
                Position(block.x, block.y));
            drops.push_back(std::move(drop));
        } else if (block.type == "DropedBomb") {
            auto drop = std::make_unique<BombDrop>(Position(block.x, block.y));
            drops.push_back(std::move(drop));
        }
    }

    return std::make_shared<Map>(collidables, std::move(drops), bomb_site,
                                 tt_spawn, ct_spawn);
}
