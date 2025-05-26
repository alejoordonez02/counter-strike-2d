#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>

#define FRAME_RATE 1000000.0f/25.0f

class SdlTexture;
class Area;

class Animation {
   public:
    Animation(SDL2pp::Texture &texture);
    ~Animation();
    void update(float dt);
    void render(SDL2pp::Renderer &renderer, const SDL2pp::Rect dest, SDL_RendererFlip &flipType, double rotation_angle = 0.0);
    


   private:
    void advanceFrame();
    /** SDL texture of the raw image. */
    SDL2pp::Texture &texture;
    /** Current animation frame. */
    int currentFrame;
    /** Total number of frames in the sprite. */
    int numFrames;
    /** Size of the sprite (height and width). */
    int size;
    /** Time elapsed since last update. */
    float elapsed;
};

#endif  //__ANIMATION_H__
