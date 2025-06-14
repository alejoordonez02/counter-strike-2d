#ifndef SERVER_MODEL_ATTACK_H
#define SERVER_MODEL_ATTACK_H

#include "common/direction.h"
#include "server/model/action_strategy.h"
#include "server/model/weapon.h"

class Player;

/*
 * Attack
 * */
class Attack: public ActionStrategy {
private:
    /*
     * Las opciones acá eran o rediseñar todo para que map se encargue de las
     * colisiones (en éste punto me doy cuenta de que hubiera sido lo mejor de
     * un principio, aunque quede menos "elegante" a primera vista), pasar
     * player physics para que ordene los sorted idx y ref a los collidables
     * (excluyendo al player), o (lo más lindo): pasar los sorted idx y los
     * collidables, pero claro, debería estar constantemente actualizando los
     * sorted idx: costoso... o no, porque lo debería hacer igual en
     * PlayerPhysics, entonces podría hacerlo en Player, actualizar los sorted
     * idx y pasar la ref tanto a Attack (o cualquier strategy que lo necesite)
     * como a PlayerPhysics. Bueno, lo siguiente es el resultado de eso:
     * */
    Position& pos;
    Direction& dir;
    Weapon& weapon;
    std::vector<std::shared_ptr<Hitbox>>& collidables;
    std::vector<size_t>& sorted_idx;

public:
    Attack(Position& pos, Direction& dir, Weapon& weapon,
           std::vector<std::shared_ptr<Hitbox>>& collidables,
           std::vector<size_t>& sorted_idx);
    void update(float dt) override;
};

#endif
