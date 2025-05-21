#ifndef COMMAND_H
#define COMMAND_H

#include <cstdint>
#include <vector>

#include "../../server/player.h"
#include "../serializable.h"

/*
 * Base class
 * */
class Command: public Serializable {
protected:
    Command() = default;

public:
    virtual void execute(Player& p) const = 0;

    Command(const Command&) = delete;
    Command& operator=(const Command&) = delete;

    Command(Command&&) = default;
    Command& operator=(Command&&) = default;

    virtual ~Command() = default;
};

#endif
