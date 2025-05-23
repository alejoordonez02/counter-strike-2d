#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "../../common/direction.h"  //
#include "../../common/position.h"   // mover a model
                                     /* */

#include <vector>

#include "../../common/direction.h"
#include "../../common/position.h"

#include "collidable.h"
#include "map.h"
#include "weapon.h"


class Player: public Collidable {
private:
    Position pos;
    Map& map;
    int kills;
    Weapon primary;
    Weapon secondary;
    Weapon& current_weapon;

public:
    Player(const Position& pos, Map& map);
    virtual void move(const Direction& dir);
    void attack(const int& angle) {
        Trajectory t(pos, angle);
        std::vector<Collidable> collidable = map.get_collidable();
        auto sorted_idx = sort_by_distance_idx(collidable);
        for (size_t i: sorted_idx) {
            auto& c = collidable[i];
            if (t.intersects(c.get_pos())) {
                current_weapon.attack(c);
                break;
            }
        }
    }
    virtual void get_attacked(const int& damage) override;
    virtual ~Player() = default;
};

#endif
