#ifndef CLIENT_CAMERA_H
#define CLIENT_CAMERA_H

#include "SDL2pp/Point.hh"
#include "SDL2pp/Rect.hh"


#include <SDL2pp/Renderer.hh>
#include <SDL_render.h>

/**
 * Se encarga de centrar la cámara en el jugador actual.
 * Es quien convierte las posiciones absolutas en relativas a la posición del jugador
 */
class Camera {
    private:
    static SDL2pp::Point camera_offset;
    static SDL2pp::Point screen_size;    // width, height

    public:
    Camera() {}
    ~Camera() {}
    static void set_center(int jugador_x, int jugador_y);
    static void set_screen_size(const SDL2pp::Point& size);
    static void modify_center_rectangle(SDL2pp::Point& rect);
    static void modify_center_rectangle(SDL2pp::Rect& rect);
    static void debug_point(SDL2pp::Renderer& renderer, const SDL2pp::Point& position);
};

#endif
