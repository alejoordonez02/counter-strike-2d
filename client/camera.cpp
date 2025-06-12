#include "client/camera.h"
#include "camera.h"

SDL2pp::Point Camera::camera_offset = SDL2pp::Point(0, 0);
SDL2pp::Point Camera::screen_size = SDL2pp::Point(640, 480);


void Camera::set_center(int jugador_x, int jugador_y){
    // Calcula el offset de la cámara basado en la posición del jugador
    camera_offset.x = jugador_x - screen_size.x / 2;
    camera_offset.y = jugador_y - screen_size.y / 2;
}


void Camera::set_screen_size(const SDL2pp::Point& size) {
    screen_size = size;
}


void Camera::center_rectangle(SDL2pp::Rect& rect) {
    // centra el rectángulo en la pantalla usando el offset de la cámara
    rect.x -= camera_offset.x;
    rect.y -= camera_offset.y;
}