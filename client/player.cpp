#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>

#include "player.h"

Player::Player(SDL2pp::Texture &texture): an(texture), moving(false), x(300), y(300) {}

Player::~Player() {}


void Player::update(float dt) {
    if (moving) {
        an.update(dt);
        if (facingLeft){
            x -= 3;
        } else if(facingRight){
            x += 3;
        } else if(facingUp){
            y -= 3;
        } else if(facingDown){
            y += 3;
        }
    }
}


void Player::render(SDL2pp::Renderer &renderer) {
    // SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    // an.render(renderer, SDL2pp::Rect(x, y, 32, 32), flip);

    double angle = 0.0;

    // rotar en función del movimiento
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (facingLeft) {
        angle = -90.0;
    } else if (facingRight) {
        angle = 90.0;
    } else if (facingUp) {
        flip = SDL_FLIP_NONE;
    } else if (facingDown) {
        flip = SDL_FLIP_VERTICAL;
    }
    an.render(renderer, SDL2pp::Rect(x, y, 32, 32), flip, angle);
}

void Player::moveRigth() {
    moving = true;
    facingRight = true;
    facingLeft = false;
    facingUp = false;
    facingDown = false;
}

void Player::moveLeft() {
    moving = true;
    facingLeft = true;
    facingRight = false;
    facingUp = false;
    facingDown = false;
}

void Player::moveUp() {
    moving = true;
    facingUp = true;
    facingDown = false;
    facingLeft = false;
    facingRight = false;
}

void Player::moveDown() {
    moving = true;
    facingDown = true;
    facingUp = false;
    facingLeft = false;
    facingRight = false;
}

void Player::stopMoving() {
    moving = false;
}
