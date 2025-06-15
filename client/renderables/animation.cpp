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
        size(data.modify_size != 0 ? data.modify_size : frame_width / columns),  // siempre texturas con tamaño cuadrado
        elapsed(0),
        step(data.steps){}

Animation::~Animation() {
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
                       SDL_RendererFlip& flipType, double rotation_angle) {
    int frameX = (this->current_frame % columns) * size;
    int frameY = (this->current_frame / columns) * size;

    SDL2pp::Rect src = SDL2pp::Rect(frameX, frameY, size, size);
    SDL2pp::Rect dst = SDL2pp::Rect(position.x, position.y, size, size);

    // se modifica su posición para que este centrado en la cámara
    Camera::modify_center_rectangle(dst);

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
    int frameX = (this->current_frame % columns) * size;
    int frameY = (this->current_frame / columns) * size;

    SDL2pp::Rect src = SDL2pp::Rect(frameX, frameY, size, size);
    SDL2pp::Rect dst = SDL2pp::Rect(from_position.x, from_position.y, size, size);

    // se modifica su posición para que este centrado en la cámara
    Camera::modify_center_rectangle(dst);
    // guarda la posición modificada para sumar desde ahí
    int modified_x = dst.x;
    int modified_y = dst.y;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            dst.x = modified_x + j * size;
            dst.y = modified_y + i * size;
            renderer.Copy(texture, src, dst);
        }
    }
}