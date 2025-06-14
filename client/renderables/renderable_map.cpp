#include "client/renderables/renderable_map.h"

#include <utility>

#include "client/animation_provider.h"
#include "common/snapshot.h"

RenderableMap::RenderableMap(
        const MapData& map_data,
        std::shared_ptr<AnimationProvider> animation_provider):
        map_data(map_data),
        animation_provider(animation_provider) {
    
    load_blocks();
}

void RenderableMap::load_blocks() {
    // mostrar el nombre de los blockes por consola
    for (const auto& block : map_data.blocks) {
        std::cout << "Block at (" << block.x << ", " << block.y
                  << ") with texture: " << block.texture
                  << " and type: " << block.type << std::endl;
    }
}

// void RenderableMap::update() {

// }

// void RenderableMap::render(SDL2pp::Renderer& renderer) {
    
// }

RenderableMap::~RenderableMap() {}
