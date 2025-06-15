#ifndef CLIENT_RENDERABLES_RENDERABLE_MAP_H
#define CLIENT_RENDERABLES_RENDERABLE_MAP_H

#include <memory>
#include <string>
#include <unordered_map>

#include "SDL2pp/Point.hh"
#include "SDL2pp/Renderer.hh"
#include "client/animation_provider.h"
#include "client/renderables/animation.h"
#include "client/renderables/renderable_block.h"
#include "common/maploader.h"


class RenderableMap {
    private:
    const MapData& map_data;
    std::shared_ptr<AnimationProvider> animation_provider;

    std::unordered_map<std::string, std::unique_ptr<RenderableBlock>> blocks;
    std::unique_ptr<Animation> background;

    public:
    RenderableMap(const MapData& map_data, std::shared_ptr<AnimationProvider> animation_provider);

    void load_map_info();

    void load_background();

    void update();
    void render(SDL2pp::Renderer& renderer);

    void load_blocks();

    ~RenderableMap();
};

#endif
