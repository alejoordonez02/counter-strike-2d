#ifndef CLIENT_FIELD_OF_VIEW_H
#define CLIENT_FIELD_OF_VIEW_H
#include <SDL2pp/SDL2pp.hh>

class FieldOfView {
private:
    SDL2pp::Texture stencil;
    uint32_t width, height;

public:
    FieldOfView(SDL2pp::Renderer& renderer, uint32_t width, uint32_t height);

    void update(SDL2pp::Renderer& renderer);

    void render(SDL2pp::Renderer& renderer);
};

#endif
