#ifndef WEAPON_H
#define WEAPON_H

#include <random>

#include "collidable.h"

/*
 * Claramente estos los vamos a tener que generar más rápido, esto
 * es sólo un proto
 * */
namespace Random {
float get(const float& n, const float& m) {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<float> dist(n, m);
    return dist(gen);
}
}  // namespace Random

/*
 * la trayectoria podría ser un atributo de Weapon, de esa forma
 * se podría sobrecargar intersects según, por ejemplo, la accuracy
 * de la misma
 * */
class Trajectory {
private:
    Position origin;
    int angle;

public:
    Trajectory(const Position& origin, const int& angle): origin(origin), angle(angle) {}
    bool intersects(const Position& pos);
};
class Weapon {
private:
    int damage;
    int ammo;
    float accuracy; /* entre 0 y 1, es una proba */
public:
    int get_damage();
    /*
     * attack() lo vamos a tener que sobrecargar según el arma, además
     * por el modo en el que esté la misma... patrón Strategy va como piña
     * */
    void attack(Collidable& coll) {
        if (Random::get(0, 1) < accuracy) {
            coll.get_attacked(damage);
            ammo--;
        }
    }
};

#endif
