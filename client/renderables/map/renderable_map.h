#ifndef CLIENT_RENDERABLES_RENDERABLE_MAP_H
#define CLIENT_RENDERABLES_RENDERABLE_MAP_H

#include <memory>
#include <string>
#include <unordered_map>

#include "SDL2pp/Point.hh"
#include "SDL2pp/Renderer.hh"
#include "client/providers/animation_provider.h"
#include "client/renderables/animation.h"
#include "client/renderables/map/renderable_block.h"
#include "common/maploader.h"
#include "common/network/dtos/snapshot_dto.h"


class RenderableMap {
    private:
    const MapData& map_data;
    std::shared_ptr<AnimationProvider> animation_provider;

    std::vector<std::unique_ptr<RenderableBlock>> blocks;
    std::vector<std::unique_ptr<RenderableBlock>> droped_weapons;
    std::unique_ptr<Animation> background;

    public:
    RenderableMap(const MapData& map_data, std::shared_ptr<AnimationProvider> animation_provider);

    void load_background();

    void update(const SnapshotDTO& snapshot);

    void render(SDL2pp::Renderer& renderer);

    void load_blocks();

    ~RenderableMap();
};

#endif
