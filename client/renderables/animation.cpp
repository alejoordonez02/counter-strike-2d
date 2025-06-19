#include "client/renderables/animation.h"
#include "client/camera.h"

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include "animation.h"

Animation::Animation(SDL2pp::Texture& texture, const AnimationData& data):
        texture(texture),
        current_frame(data.frames),
        frame_width(this->texture.GetWidth()),
        frame_height(this->texture.GetHeight()),
        num_frames(data.frames),
        columns(data.columns),
        is_animated(data.is_animated),
        size_width(data.size_width != 0 ? data.size_width : frame_width / columns),
        size_height(data.size_height != 0 ? data.size_height : size_width),    // si no se especifica se asumen cuadradas
        modify_size(data.modify_size != 0 ? data.modify_size : 1.0f),
        elapsed(0),
        step(data.steps != 0 ? data.steps : 0) {}

Animation::~Animation() {
}

SDL2pp::Point Animation::get_animation_size() {
    // devuelve el tamaño del sprite, no de la textura completa
    return SDL2pp::Point(size_width * modify_size, size_height * modify_size);
}



void Animation::update() {
    if (!this->is_animated) {
        // sprite estatico. Solo tiene 1 frame, no avanzar al siguiente
        return;
    }

    elapsed++;
    if (elapsed < step) return;
    elapsed = 0;
    this->advanceFrame();
}

void Animation::skip_frames(uint8_t frames_to_skip){
    if (!this->is_animated) {
        // sprite estatico. Solo tiene 1 frame, no necesita skipear
        return;
    }
    // se salta los frames que no se renderizan
    this->current_frame += frames_to_skip;
    
    this->current_frame = this->current_frame % this->num_frames;
}

void Animation::advanceFrame() {
    this->current_frame += 1;
    // Se reinicia solo. EJ: si hay 4 frames, entonces 1%4=0, 2%4=1, 3%4=2,
    // 4%4=3, 5%4=0, 6%4=1, ...
    this->current_frame = this->current_frame % this->num_frames;
}

void Animation::render(SDL2pp::Renderer& renderer, const SDL2pp::Point position,
                       SDL_RendererFlip& flipType, double rotation_angle, bool is_camera_enabled) {
    int frameX = (this->current_frame % columns) * size_width;
    int frameY = (this->current_frame / columns) * size_height;

    SDL2pp::Rect src = SDL2pp::Rect(frameX, frameY, size_width, size_height);
    SDL2pp::Rect dst = SDL2pp::Rect(position.x, position.y, size_width * modify_size, size_height * modify_size);

    // se modifica su posición para que este centrado en la cámara
    if(is_camera_enabled){
        Camera::modify_center_rectangle(dst);
    }

    renderer.Copy(texture, src, dst, rotation_angle,
                  SDL2pp::NullOpt,  // rotation center - not needed
                  flipType);
}

/**
 * Repite una Animation en un área rectangular, tipo mosaico
 * Segun la cantidad de veces que se indique en columns y rows
 * */
void Animation::render_tilling(SDL2pp::Renderer& renderer, const SDL2pp::Point from_position, 
                               int columns, int rows) {
    // Renderiza la animación en un área rectangular desde from_position
    int frameX = (this->current_frame % columns) * size_width;
    int frameY = (this->current_frame / columns) * size_height;

    SDL2pp::Rect src = SDL2pp::Rect(frameX, frameY, size_width, size_height);
    SDL2pp::Rect dst = SDL2pp::Rect(from_position.x, from_position.y, size_width * modify_size, size_height * modify_size);

    // se modifica su posición para que este centrado en la cámara
    Camera::modify_center_rectangle(dst);
    // guarda la posición modificada para sumar desde ahí
    int modified_x = dst.x;
    int modified_y = dst.y;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            dst.x = modified_x + j * size_width * modify_size;
            dst.y = modified_y + i * size_height * modify_size;
            renderer.Copy(texture, src, dst);
        }
    }
}