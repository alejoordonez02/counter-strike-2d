#ifndef SERVER_GAME_MAKER_ERROR_H
#define SERVER_GAME_MAKER_ERROR_H

#include <stdexcept>
#include <string>

class GameAlreadyExists: public std::runtime_error {
public:
    explicit GameAlreadyExists(const std::string& game_name):
        std::runtime_error("Game '" + game_name + "' already exists\n") {}
};

class GameNotFound: public std::runtime_error {
public:
    explicit GameNotFound(const std::string& game_name):
        std::runtime_error("Game '" + game_name + "' does not exist\n") {}
};

class TeamIsFull: public std::runtime_error {
public:
    explicit TeamIsFull(): std::runtime_error("Team is full\n") {}
};

#endif
