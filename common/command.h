#ifndef COMMAND_H
#define COMMAND_H

#include <cstdint>
#include <vector>

#include "server/player.h"

#include "position.h"
#include "serializable.h"

/*
 * Base class
 * */
class Command: public Serializable {
public:
    virtual void execute(Player& player) const = 0;
};

/*
 * Move
 * */
class Move: public Command {
private:
    Direction dir;  // ángulo de dirección con respecto al eje x

public:
    Move(const Direction& dir);
    virtual std::vector<uint8_t> serialize() const override;
    virtual void execute(Player& player) const override;
    Direction get_dir() const;
};

/*
 * Attack
 * */
class Attack: public Command {
private:
    Position pos;

public:
    Attack(const Position& pos);
    virtual std::vector<uint8_t> serialize() const override;
    virtual void execute(Player& player) const override;
    Position get_pos() const;
};

#endif
