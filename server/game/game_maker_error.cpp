#include "game_maker_error.h"

#include <stdexcept>
#include <string>

GameAlreadyExists::GameAlreadyExists(const std::string& game_name):
    std::runtime_error("Game '" + game_name + "' already exists\n") {}

GameNotFound::GameNotFound(const std::string& game_name):
    std::runtime_error("Game '" + game_name + "' does not exist\n") {}

TeamIsFull::TeamIsFull(): std::runtime_error("Team is full\n") {}
