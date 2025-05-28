#ifndef COMMAND_H
#define COMMAND_H

#include <cstdint>
#include <vector>

#include "../model/player.h"

// class Command: public Serializable {
class Command {
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
