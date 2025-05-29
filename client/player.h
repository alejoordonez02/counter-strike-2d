#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <SDL2pp/SDL2pp.hh>
#include "animation.h"

class Player {
public:
    Player(SDL2pp::Texture &texture);
    ~Player();
    void update(float dt);
    void render(SDL2pp::Renderer &renderer);
    void moveRigth();
    void moveLeft();
    void moveUp();
    void moveDown();
    void stopMoving();

private:
    Animation an;
    bool facingLeft;
    bool facingRight;
    bool facingUp;
    bool facingDown;
    bool moving;
    int x;
    int y;
};

#endif // __PLAYER_H__