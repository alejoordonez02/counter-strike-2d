#ifndef DESERIALIZER_H
#define DESERIALIZER_H

#include <memory>

#include "../player_commands.h"

template <typename ReturnT>
class Deserializer;


template<>
class Deserializer<std::unique_ptr<Command>> {
public:
    Deserializer() = default;

    std::unique_ptr<Command> deserialize(const std::string& data); // switch

private:
    std::unique_ptr<Command> deserialize_move() {}

    std::unique_ptr<Command> deserialize_attack() {}

    // ...

public:
    Deserializer(const Deserializer&) = delete;
    Deserializer& operator=(const Deserializer&) = delete;

    Deserializer(Deserializer&&) = default;
    Deserializer& operator=(Deserializer&&) = default;

    ~Deserializer() = default;
};


// template<>
// class Deserializer<GameState> {
// public:
//     Deserializer() = default;

//     GameState deserialize(const std::string& data);

//     Deserializer(const Deserializer&) = delete;
//     Deserializer& operator=(const Deserializer&) = delete;

//     Deserializer(Deserializer&&) = default;
//     Deserializer& operator=(Deserializer&&) = default;

//     ~Deserializer() = default;
// };

#endif
