#include "client/renderables/animation.h"
#include "client/camera.h"

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

Animation::Animation(SDL2pp::Texture& texture, const AnimationData& data):
        texture(texture),
        current_frame(0),
        frame_width(this->texture.GetWidth()),
        frame_height(this->texture.GetHeight()),
        num_frames(data.frames),
        columns(data.columns),
        is_animated(data.is_animated),
        size(frame_width / columns),  // siempre texturas con tamaño cuadrado
        elapsed(0),
        step(data.steps){}

Animation::~Animation() {
}

void Animation::update() {
    if (!this->is_animated) {
        // sprite estatico. Toma solo 1 frame y no permite avanzar al siguiente
        this->current_frame = this->num_frames;
        return;
    }

    elapsed++;
    if (elapsed < step) return;
    elapsed = 0;
    this->advanceFrame();
}

void Animation::advanceFrame() {
    this->current_frame += 1;
    // Se reinicia solo. EJ: si hay 4 frames, entonces 1%4=0, 2%4=1, 3%4=2,
    // 4%4=3, 5%4=0, ...
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
