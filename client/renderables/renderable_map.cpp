#include "client/renderables/renderable_map.h"
#include "client/animation_provider.h"
#include "renderable_map.h"

#include <utility>


RenderableMap::RenderableMap(
        const MapData& map_data,
        std::shared_ptr<AnimationProvider> animation_provider):
        map_data(map_data),
        animation_provider(animation_provider) {
}

void RenderableMap::load_map_info(){
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
        // Crear un RenderableBlock para cada bloque
        blocks[block.texture] = std::make_unique<RenderableBlock>(block, animation_provider);
        blocks[block.texture]->load_block();
    }
}

void RenderableMap::render(SDL2pp::Renderer& renderer) {
    // TODO: Hardcodeado el mosaico
    // iniciar en 0,0 y repetir 10 veces en x & 10 veces en y
    background->render_tilling(renderer, SDL2pp::Point(0, 0), 10, 10);

    // render all blocks
    for (const auto& [key, block] : blocks) {
        block->render(renderer);
    }
}

RenderableMap::~RenderableMap() {}
