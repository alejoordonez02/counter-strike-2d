#ifndef ATTACK_H
#define ATTACK_H

#include "../../server/player.h"
#include "../serializer.h"

#include "command.h"

/*
 * Attack
 * */
class Attack: public Command {
private:
    float angle;

public:
    Attack(const float angle): angle(angle) {}

    void execute(Player& p) const override;
    std::string serialize() const override { return Serializer::serialize_attack(angle); }
};

#endif
