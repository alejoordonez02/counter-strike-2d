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
    std::cout << "Background path: " << map_data.backgroundPath << std::endl;
    background = animation_provider->make_animation("background_sand1");

}

void RenderableMap::load_blocks() {
    // mostrar el nombre de los blockes por consola
    for (const auto& block : map_data.blocks) {
        // Crear un RenderableBlock para cada bloque
        blocks[block.texture] = std::make_unique<RenderableBlock>(block, animation_provider);
        blocks[block.texture]->load_block();
        std::cout << "Block at (" << block.x << ", " << block.y
                  << ") with texture: " << block.texture
                  << " and type: " << block.type << std::endl;
    }
}

void RenderableMap::update() {
    // NOTE: no es necesario, salvo que haya algun bloque animado
    // background->update();
}

void RenderableMap::render(SDL2pp::Renderer& renderer) {
    // TODO: Hardcodeado el mosaico
    // iniciar en 0,0 y repetir 10 en x & 10 en y
    background->render_tilling(renderer, SDL2pp::Point(0, 0), 10, 10);

    // render all blocks
    for (const auto& [key, block] : blocks) {
        block->render(renderer);
    }
}

RenderableMap::~RenderableMap() {}
