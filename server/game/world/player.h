#ifndef SERVER_MODEL_PLAYER_H
#define SERVER_MODEL_PLAYER_H

#include <memory>

#include "actions/action_strategy.h"
#include "actions/attack.h"
#include "common/direction.h"
#include "common/network/dtos/snapshot_dto.h"
#include "common/position.h"
#include "equipment/weapon.h"
#include "map.h"
#include "physics/hitbox.h"
#include "physics/player_physics.h"
#include "weapon_factory.h"

class Player: public Hitbox {
protected:
    std::weak_ptr<Map> map;
    std::unique_ptr<ActionStrategy> action;

    void respawn();

    PlayerPhysics physics;

private:
    int id;
    std::vector<size_t> sorted_collidables_idx;
    Direction dir;

    std::shared_ptr<Weapon> primary;
    std::shared_ptr<Weapon> secondary;
    std::shared_ptr<Weapon> knife;
    std::shared_ptr<Weapon>& current;

    float shield;

    int max_health;
    int health;
    bool alive;

    int kills;
    int money;

    bool pay(const int& cost);
    std::shared_ptr<Weapon> get_weapon(WeaponType type);

    virtual void teleport_to_spawn() = 0;

    std::shared_ptr<WeaponFactory> weapon_factory;

public:
    Player(int id, Position pos, std::shared_ptr<Weapon> primary,
           std::shared_ptr<Weapon> secondary, std::shared_ptr<Weapon> knife,
           std::weak_ptr<Map> map, float max_velocity, float acceleration,
           float radius, int money, int health,
           std::shared_ptr<WeaponFactory> weapon_factory);

    void update(float dt);

    virtual void switch_side() = 0;
    virtual void restart() = 0;

    /*
     * Hitbox interface
     * */
    std::optional<Position> intersect(const Trajectory& t) const override;
    void get_attacked(int damage) override;

    /*
     * Pasive commands: change what the player **is** doing
     * */
    virtual void start_moving(Direction dir);
    void stop_moving();

    virtual void start_attacking();
    void start_reloading();
    virtual void start_planting() = 0;
    virtual void start_defusing() = 0;

    void stop_action();

    /*
     * Active commands
     * */
    void aim(Direction dir);

    void pickup();

    void use_weapon(const WeaponType& type);

    void buy_weapon(WeaponName name);
    void buy_ammo(WeaponType type, int count);

    virtual void give_bomb() = 0;

    /*
     * Getters & setters (mostly for testing purposes)
     * */
    void set_weapon(std::shared_ptr<Weapon> weapon) { current = weapon; }
    bool is_alive();

    /*
     * DTOs
     * */
    std::shared_ptr<PrivatePlayerDTO> get_private_data() const;
    PlayerDTO get_data() const;

    virtual ~Player() = default;
};

#endif
