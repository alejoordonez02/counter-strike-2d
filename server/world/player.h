#ifndef SERVER_MODEL_PLAYER_H
#define SERVER_MODEL_PLAYER_H

#include <memory>

#include "common/direction.h"
#include "common/position.h"
#include "common/snapshot.h"
#include "server/world/actions/action_strategy.h"
#include "server/world/actions/attack.h"
#include "server/world/equipment/equipment.h"
#include "server/world/equipment/weapon.h"
#include "server/world/map.h"
#include "server/world/physics/player_physics.h"

class Player: public Hitbox {
protected:
    std::weak_ptr<Map> map;

private:
    int id;
    std::vector<size_t> sorted_collidables_idx;
    PlayerPhysics physics;
    std::unique_ptr<ActionStrategy> action;
    Direction dir;
    std::unique_ptr<Equipment> equipment;
    Weapon& current;
    int max_health;
    int health;
    bool alive;
    int kills;
    int money;

    bool pay(const int& cost);

    void stop_action();

    virtual void teleport_to_spawn() {}  // = 0;

public:
    Player(int id, Position pos, std::unique_ptr<Equipment>&& equipment,
           std::weak_ptr<Map> map, float max_velocity, float acceleration,
           float radius, int money, int health);

    void update(float dt);

    void restart();

    bool is_alive();

    std::optional<Position> intersect(const Trajectory& t) const override;

    void get_attacked(int damage) override;

    virtual void start_moving(Direction dir);
    void stop_moving();

    virtual void start_attacking();
    void stop_attacking();

    void aim(Direction dir);

    void use_primary();
    void use_secondary();
    void use_knife();

    void buy_primary(Weapon& weapon);
    void buy_secondary(Weapon& weapon);
    void buy_primary_ammo(const int& count);
    void buy_secondary_ammo(const int& count);

    virtual void plant_bomb() {}
    virtual void stop_planting() {}

    virtual void defuse_bomb() {}
    virtual void stop_defusing() {}

    PlayerData get_data() const;

    virtual ~Player() = default;
};

#endif
