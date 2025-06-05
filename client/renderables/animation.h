#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>


struct AnimationData{
    int columns;
    int frames;
    bool is_animated;
};

class Animation {
   public:
    Animation(SDL2pp::Texture &texture, const AnimationData &data);
    ~Animation();
    void update();
    void render(SDL2pp::Renderer &renderer, const SDL2pp::Point position, SDL_RendererFlip &flipType, double rotation_angle = 0.0);
    


   private:
    void advanceFrame();

    /** SDL texture of the raw image. */
    SDL2pp::Texture &texture;
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

    /** Time elapsed since last update. */
    float elapsed;

};

#endif  //__ANIMATION_H__
