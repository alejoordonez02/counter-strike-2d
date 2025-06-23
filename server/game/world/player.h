#ifndef SERVER_MODEL_PLAYER_H
#define SERVER_MODEL_PLAYER_H

#include <memory>

#include "actions/action_strategy.h"
#include "actions/attack.h"
#include "common/direction.h"
#include "common/network/dtos/snapshot_dto.h"
#include "common/position.h"
#include "equipment/equipment.h"
#include "equipment/weapon.h"
#include "map.h"
#include "physics/hitbox.h"
#include "physics/player_physics.h"

class Player: public Hitbox {
protected:
    std::weak_ptr<Map> map;
    std::unique_ptr<ActionStrategy> action;

    void respawn();

private:
    int id;
    std::vector<size_t> sorted_collidables_idx;
    PlayerPhysics physics;
    Direction dir;
    Equipment equipment;
    Weapon& current;
    int max_health;
    int health;
    bool alive;
    int kills;
    int money;

    bool pay(const int& cost);

    void stop_action();

    virtual void teleport_to_spawn() = 0;

public:
    Player(int id, Position pos, const Equipment& equipment,
           std::weak_ptr<Map> map, float max_velocity, float acceleration,
           float radius, int money, int health);

    void update(float dt);

    virtual void switch_side() = 0;

    virtual void restart() = 0;

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

    virtual void give_bomb() = 0;
    virtual void plant_bomb() = 0;
    void stop_planting();

    virtual void defuse_bomb() = 0;
    void stop_defusing();

    YourPlayerData get_special_data() const;

    PlayerData get_data() const;

    virtual ~Player() = default;
};

#endif
