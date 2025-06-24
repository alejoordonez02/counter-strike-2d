#ifndef SERVER_GAME_WORLD_DROP_H
#define SERVER_GAME_WORLD_DROP_H

#include "common/position.h"
#include "equipment/weapon.h"
#include "snapshot_dto.h"

/*
 * TODO: make this configurable
 * */
#define DROP_RADIUS 10

class Player;

class Drop {
private:
    int radius;

protected:
    Position pos;

public:
    Drop(Position pos): radius(DROP_RADIUS), pos(pos) {}

    virtual std::shared_ptr<Weapon> get_weapon() const = 0;

    virtual WeaponType get_type() const = 0;

    virtual void push_drop_data(std::vector<WeaponDTO>& snapshot) = 0;

    /*
     * TODO: misma lógica que en PlayerPhysics::intersects, a lo mejor
     * implementar Circle y que ambas hereden de ahí
     * */
    bool intersects(const Position& pos) const {
        float distance = this->pos.get_distance(pos);
        return distance < radius;
    }

    virtual ~Drop() = default;
};

class WeaponDrop: public Drop {
    std::shared_ptr<Weapon> weapon;

public:
    WeaponDrop(std::shared_ptr<Weapon> weapon, Position pos):
        Drop(pos), weapon(std::move(weapon)) {}

    std::shared_ptr<Weapon> get_weapon() const override { return weapon; }

    WeaponType get_type() const override { return weapon->get_type(); }

    void push_drop_data(std::vector<WeaponDTO>& snapshot) override {
        snapshot.push_back(WeaponDTO(weapon->get_name(), pos));
    }
};

class BombDrop: public Drop {
public:
    BombDrop(Position pos): Drop(pos) {}

    std::shared_ptr<Weapon> get_weapon() const override { return nullptr; }

    WeaponType get_type() const override { return WeaponType::BOMB; }

    void push_drop_data(std::vector<WeaponDTO>& snapshot) override {
        snapshot.push_back(WeaponDTO(WeaponName::BOMB, pos));
    }
};

#endif
