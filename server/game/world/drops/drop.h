#ifndef SERVER_GAME_WORLD_DROP_H
#define SERVER_GAME_WORLD_DROP_H

#include "common/position.h"
#include "equipment/weapon.h"
#include "snapshot_dto.h"

/*
 * TODO: make this configurable
 * */
#define DROP_RADIUS 10

class Drop {
private:
    int radius;

protected:
    Position pos;

public:
    Drop(Position pos);

    virtual std::shared_ptr<Weapon> get_weapon() const = 0;

    virtual WeaponType get_type() const = 0;

    virtual void push_drop_data(std::vector<WeaponDTO>& snapshot) = 0;

    bool intersects(const Position& pos) const;

    virtual ~Drop() = default;
};

#endif
