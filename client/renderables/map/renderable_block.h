#ifndef CLIENT_RENDERABLES_RENDERABLE_BLOCK_H
#define CLIENT_RENDERABLES_RENDERABLE_BLOCK_H

#include <memory>
#include <string>
#include <unordered_map>

#include "SDL2pp/Renderer.hh"
#include "client/providers/animation_provider.h"
#include "client/renderables/animation.h"
#include "common/maploader.h"
#include "common/position.h"

class RenderableBlock {
    private:
    BlockData block_data;
    std::shared_ptr<AnimationProvider> animation_provider;

    std::unique_ptr<Animation> block;

    public:
    RenderableBlock(const BlockData& block_data, std::shared_ptr<AnimationProvider> animation_provider);

    void render(SDL2pp::Renderer& renderer);

    void load_block();

    ~RenderableBlock();
};

#endif
