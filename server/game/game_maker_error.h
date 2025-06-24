#ifndef SERVER_GAME_MAKER_ERROR_H
#define SERVER_GAME_MAKER_ERROR_H

#include <stdexcept>
#include <string>

class GameAlreadyExists: public std::runtime_error {
public:
    explicit GameAlreadyExists(const std::string& game_name);
};

class GameNotFound: public std::runtime_error {
public:
    explicit GameNotFound(const std::string& game_name);
};

class TeamIsFull: public std::runtime_error {
public:
    explicit TeamIsFull();
};

#endif
