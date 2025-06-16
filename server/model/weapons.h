#ifndef SERVER_MODEL_EAPONS_H
#define SERVER_MODEL_EAPONS_H

#include "server/model/weapon.h"

class Fist: public Weapon {
    public:
    Fist(): Weapon(0, 0, 0, 0, 0, 0, 0) {}
};

class Knife: public Weapon {
    public:
    Knife(): Weapon(20, 30, 0.8, 0, 0, 0, 0) {}
};

class Glock: public Weapon {
    public:
    Glock(): Weapon(20, 30, 0.8, 30, 4, 700, 1) {}
};

class Ak47: public Weapon {
    public:
    Ak47(): Weapon(30, 30, 0.8, 50, 6, 2500, 1) {}
};

class M3: public Weapon {
    public:
    M3(): Weapon(20, 30, 0.5, 10, 10, 1200, 1) {}
};

class Awp: public Weapon {
    public:
    Awp(): Weapon(100, 30, 1, 100, 0.3, 3500, 1) {}
};

#endif
