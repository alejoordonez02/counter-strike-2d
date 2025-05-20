#include "player_commands.h"

#include <cstdint>
#include <vector>

// #include "server/player.h"

/*
 * Move
 * */
void Move::execute() const { player.move(dir); }

Direction Move::get_dir() const { return dir; }


/*
 * Attack
 * */
void Attack::execute() const { player.attack(pos); }

Position Attack::get_pos() const { return pos; }
