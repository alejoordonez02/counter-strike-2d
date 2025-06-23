#include "client/camera.h"

SDL2pp::Point Camera::camera_offset = SDL2pp::Point(0, 0);
SDL2pp::Point Camera::screen_size = SDL2pp::Point(0, 0);


void Camera::set_center(int jugador_x, int jugador_y){
    // Calcula el offset de la cámara basado en la posición del jugador
    camera_offset.x = jugador_x - screen_size.x / 2;
    camera_offset.y = jugador_y - screen_size.y / 2;
}

void Camera::set_screen_size(const SDL2pp::Point& size) {
    screen_size = size;
}

void Camera::modify_center_point(SDL2pp::Point& point) {
    // centra el punto en la pantalla usando el offset de la cámara
    point.x -= camera_offset.x;
    point.y -= camera_offset.y;

}

void Camera::modify_center_rectangle(SDL2pp::Rect& rect) {
    // centra el rectángulo en la pantalla usando el offset de la cámara
    rect.x -= camera_offset.x;
    rect.y -= camera_offset.y;
}

void Camera::revert_center_point(SDL2pp::Point& rect) {
    // revierte el efecto del offset de la cámara
    rect.x -= screen_size.x / 2;
    rect.y -= screen_size.y / 2;
}

// funcion utilitaria, dibuja una pequeña cruz roja para identificar un punto
void Camera::debug_point(SDL2pp::Renderer& renderer, const SDL2pp::Point& position) {
    // Dibuja una cruz roja en la posición del jugador
    SDL2pp::Point new_point = position;
    Camera::modify_center_point(new_point);
    renderer.SetDrawColor(255, 0, 0, 255); // Rojo
    int size = 6;
    SDL_RenderDrawLine(renderer.Get(), new_point.x - size, new_point.y, new_point.x + size, new_point.y);
    SDL_RenderDrawLine(renderer.Get(), new_point.x, new_point.y - size, new_point.x, new_point.y + size);
    renderer.SetDrawColor(0, 0, 0, 0);
}
