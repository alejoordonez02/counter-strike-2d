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

Position Animation::get_animation_size() {
    // devuelve el tamaño del sprite, no de la textura completa
    return Position(size_width * modify_size, size_height * modify_size);
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

void Animation::reset() {
    this->current_frame = 0;
}

void Animation::render(SDL2pp::Renderer& renderer, const Position& position,
                       SDL_RendererFlip& flipType, double rotation_angle, bool is_camera_enabled) {
    SDL2pp::Point point(position.x, position.y);
    int frameX = (this->current_frame % columns) * size_width;
    int frameY = (this->current_frame / columns) * size_height;

    SDL2pp::Rect src = SDL2pp::Rect(frameX, frameY, size_width, size_height);
    SDL2pp::Rect dst = SDL2pp::Rect(point.x, point.y, size_width * modify_size, size_height * modify_size);

    // se modifica su posición para que este centrado en la cámara
    if(is_camera_enabled){
        Camera::modify_center_rectangle(dst);
    }

    // transparencia. Permite que la animación se desvanezca
    // si no se está haciendo fadeout, se usa el alpha original
    Uint8 old_alpha;
    old_alpha = texture.GetAlphaMod();
    texture.SetAlphaMod(fadeout_alpha);

    renderer.Copy(texture, src, dst, rotation_angle,
                  SDL2pp::NullOpt,  // rotation center - not needed
                  flipType);

    // restaurar el alpha original
    texture.SetAlphaMod(old_alpha);
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

void Animation::start_fadeout() {
    // Solo inicia el fadeout si está completamente visible
    if (fadeout_alpha < 255){
        return;
    }
    is_fading_out = true;
    fadeout_counter = 0;
    fadeout_alpha = 255;
}

bool Animation::update_fadeout() {
    if (fadeout_alpha <= 0) return false;

    fadeout_counter++;
    // velocidad de fadeout
    fadeout_alpha = std::max(0, 255 - fadeout_counter * 8);
    return true; // sigue visible
}