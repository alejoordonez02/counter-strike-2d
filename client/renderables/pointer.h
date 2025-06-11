#ifndef CLIENT_RENDERABLES_POINTER_H
#define CLIENT_RENDERABLES_POINTER_H

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

class Pointer {
    private:
    int x, y;
    SDL2pp::Texture& texture;

    public:
    explicit Pointer(SDL2pp::Texture& tex);

    void update();

    void render(SDL2pp::Renderer& renderer);
};

#endif  // __POINTER_H__
