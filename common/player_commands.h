#ifndef COMMAND_H
#define COMMAND_H

#include <cstdint>
#include <vector>

// #include "server/player.h"

#include "position.h"
#include "network/serializable.h"
#include "network/serializer.h"

/*
 * Base class
 * */
class Command: Serializable {
protected:
    Command() = default;

public:
    virtual void execute() const = 0; // parametro const GameState& o const Player&?

    Command(const Command&) = delete;
    Command& operator=(const Command&) = delete;

    Command(Command&&) = default;
    Command& operator=(Command&&) = default;

    virtual ~Command() = default;
};


enum Direction {N, NE, E, SE, S, SW, W, NW};
/*
 * Move
 * */
class Move: public Command {
private:
    Direction dir;
public:
    Move(Direction d): dir(d) {}

    void execute() const override;
    std::string serialize(Serializer& szr) const override { return szr.serialize(*this); }
    Direction get_dir() const;
};

/*
 * Attack
 * */
class Attack: public Command {
private:
    float angle;
public:
    Attack(const float angle): angle(angle) {}
    
    void execute() const override;
    std::string serialize(Serializer& szr)  const override { return szr.serialize(*this); }
    Position get_pos() const;
};

// ReloadWeapon?
// ChangeWeapon
// PlantBomb
// DefuseBomb

// BuyWeapon
// PickUpWeapon
// DropWeapon?
// SellWeapon?
// BuyAmmo
// ...

#endif
