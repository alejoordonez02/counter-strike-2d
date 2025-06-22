#include "client/renderables/map/renderable_map.h"
#include "client/providers/animation_provider.h"
#include <utility>

std::string weapon_type_to_string(WeaponType type) {
    switch(type) {
        case WeaponType::None:  return "none";
        case WeaponType::Bomb:  return "bomb";
        case WeaponType::Knife: return "knife";
        case WeaponType::Glock: return "glock";
        case WeaponType::AK47:  return "ak47";
        case WeaponType::M3:    return "m3";
        case WeaponType::AWP:   return "awp";
        default:                return "unknown";
    }
}

RenderableMap::RenderableMap(
        const MapData& map_data,
        std::shared_ptr<AnimationProvider> animation_provider):
        map_data(map_data),
        animation_provider(animation_provider) {
    load_background();
    load_blocks();
}

void RenderableMap::load_background() {
    std::string full_name = "background_" + map_data.background;
    std::cout << "LOG: Background path: " << full_name << std::endl;
    background = animation_provider->make_animation(full_name);
}

void RenderableMap::load_blocks() {
    // mostrar el nombre de los blockes por consola
    for (const auto& block : map_data.blocks) {
        // NOTE: tal vez aca se pueda eliminar, y que la info
        // de los dropeables venga desde el inicio de parte del server en el snapshot
        if (block.type.rfind("Droped", 0) == 0) {
            // si el tipo empieza con "Droped", es un arma caída
            // ej. DropedGlock, DropedAwp, ...
            droped_weapons.emplace_back(std::make_unique<RenderableBlock>(block, animation_provider));
            continue;
        }
        // Crear un RenderableBlock para cada bloque
        blocks.emplace_back(std::make_unique<RenderableBlock>(block, animation_provider));
    }
}

void RenderableMap::update(Snapshot& snapshot) {
    // actualizar dropeables. Vaciar droped_weapons antes de agregar nuevos
    droped_weapons.clear();
    for (const auto& weapon : snapshot.weapons_on_floor) {
        BlockData block;
        block.x = weapon.x;
        block.y = weapon.y;
        // block.type = "";
        block.texture = weapon_type_to_string(weapon.type);
        droped_weapons.emplace_back(std::make_unique<RenderableBlock>(block, animation_provider));
    }
}


void RenderableMap::render(SDL2pp::Renderer& renderer) {
    // TODO: Hardcodeado el mosaico
    // iniciar en 0,0 y repetir 10 veces en x & 10 veces en y
    background->render_tilling(renderer, SDL2pp::Point(0, 0), 10, 10);

    // render all blocks
    for (const auto& block : blocks) {
        block->render(renderer);
    }
    // render all droped weapons
    for (const auto& droped_weapon : droped_weapons) {
        droped_weapon->render(renderer);
    }
}

RenderableMap::~RenderableMap() {}
