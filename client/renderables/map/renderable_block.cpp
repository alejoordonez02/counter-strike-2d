#include "client/renderables/renderable_block.h"
#include "client/animation_provider.h"

#include <utility>

RenderableBlock::RenderableBlock(
        const BlockData& block_data,
        std::shared_ptr<AnimationProvider> animation_provider):
        block_data(block_data),
        animation_provider(animation_provider)
{
    block = animation_provider->make_animation(block_data.texture);
}


// void RenderableBlock::update() {

// }

void RenderableBlock::render(SDL2pp::Renderer& renderer) {
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    if (block) {
        block->render(renderer, SDL2pp::Point(block_data.x, block_data.y), flip, 0);
    }
}

RenderableBlock::~RenderableBlock() {}
