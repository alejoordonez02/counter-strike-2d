#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>

#include "pointer.h"

Pointer::Pointer(SDL2pp::Texture& tex) : x(0), y(0), texture(tex) {}

void Pointer::update() {
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    x = mx;
    y = my;
}

void Pointer::render(SDL2pp::Renderer& renderer) {
    renderer.Copy(texture, SDL2pp::NullOpt, SDL2pp::Rect(x, y, 32, 32));
}
