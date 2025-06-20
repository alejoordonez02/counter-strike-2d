#ifndef CLIENT_RENDERABLES_ANIMATION_H
#define CLIENT_RENDERABLES_ANIMATION_H

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

struct AnimationData {
    int columns;        // cantidad de columnas de la imagen (ej. terrorista tiene 2)
    int frames;         // cantidad de frames de la animación (ej. terrorista tiene 6). Para frames fijos es el numero de frame en la imagen
    bool is_animated;       // true si es una animación, false si es un sprite estático
    int steps;          // velocidad del sprite, cada cuántos frames avanza al siguiente (solo si es animado)
    int modify_size = 0;    // si es 0 usa el tamaño de la textura original, otro valor modifica el tamaño del sprite
};

class Animation {
    public:
    Animation(SDL2pp::Texture& texture, const AnimationData& data);
    ~Animation();
    void update();
    void render(SDL2pp::Renderer& renderer, const SDL2pp::Point position,
                SDL_RendererFlip& flipType, double rotation_angle = 0.0);
    void render_tilling(SDL2pp::Renderer& renderer,
                        const SDL2pp::Point from_position, int columns,
                        int rows);
    void skip_frames(uint8_t frames_to_skip);

private:
    void advanceFrame();

    /** SDL texture of the raw image. */
    SDL2pp::Texture& texture;
    /** Current animation frame. */
    int current_frame;

    int frame_width;
    int frame_height;

    /** Total number of frames in the sprite or specific frame */
    int num_frames;
    int columns;
    bool is_animated;

    /** Size of the sprite (height and width). */
    int size;

    // contador para animaciones
    int elapsed;
    int step;
};

#endif
