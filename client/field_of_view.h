#ifndef CLIENT_FIELD_OF_VIEW_H
#define CLIENT_FIELD_OF_VIEW_H

#include <SDL2pp/SDL2pp.hh>
#include "client/game_config.h"

class FieldOfView {
private:
    uint32_t W_WIDTH, W_HEIGHT, FOV_CONE_RADIUS;
    SDL2pp::Texture stencil;

public:
    FieldOfView(SDL2pp::Renderer& renderer, const GameConfig& game_config);

    void update(SDL2pp::Renderer& renderer);

    void render(SDL2pp::Renderer& renderer);
};

#endif
