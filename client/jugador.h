#ifndef __JUGADOR_H__
#define __JUGADOR_H__

#include <SDL2pp/SDL2pp.hh>
#include "animation.h"

class Jugador {
public:
    Jugador(SDL2pp::Texture &texture);
    ~Jugador();
    void update(float dt);
    void render(SDL2pp::Renderer &renderer);
    void moveUpRight();
    void moveUpLeft();
    void moveDownRight();
    void moveDownLeft();
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

#endif // __JUGADOR_H__