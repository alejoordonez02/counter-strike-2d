#include "client/renderables/renderable_map.h"

#include <utility>

#include "client/animation_provider.h"
#include "common/snapshot.h"
#include "renderable_map.h"

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
        std::cout << "Block at (" << block.x << ", " << block.y
                  << ") with texture: " << block.texture
                  << " and type: " << block.type << std::endl;
    }
}

void RenderableMap::update() {
    background->update();
}

void RenderableMap::render(SDL2pp::Renderer& renderer) {
    double angle = 0;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL2pp::Point position(0, 0);

    background->render(renderer, position, flip, angle);
}

RenderableMap::~RenderableMap() {}
