#ifndef __POINTER_H__
#define __POINTER_H__
#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>

class Pointer {
private:
    int x, y;
    SDL2pp::Texture& texture;

public:
    Pointer(SDL2pp::Texture& tex);

    void update();

    void render(SDL2pp::Renderer& renderer);
};

#endif // __POINTER_H__