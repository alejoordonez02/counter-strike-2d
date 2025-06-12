#ifndef CLIENT_CAMERA_H
#define CLIENT_CAMERA_H

#include "SDL2pp/Point.hh"
#include "SDL2pp/Rect.hh"



class Camera {
    private:
    static SDL2pp::Point camera_offset;
    static SDL2pp::Point screen_size;    // width, height

    public:
    Camera() {}
    ~Camera() {}
    static void set_center(int jugador_x, int jugador_y);
    static void set_screen_size(const SDL2pp::Point& size);
    static void center_rectangle(SDL2pp::Rect& rect);
};

#endif
