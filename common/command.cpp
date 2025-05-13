#include "command.h"

#include <cstdint>
#include <vector>

#include "common/serializer.h"
#include "server/player.h"

#include "direction.h"

/*
 * Move
 * */
Move::Move(const Direction& dir): dir(dir) {}

void Move::execute(Player& player) const { player.move(dir); }

std::vector<uint8_t> Move::serialize() const { return Serializer::serialize_move_cmd(*this); }

Direction Move::get_dir() const { return dir; }


/*
 * Attack
 * */
Attack::Attack(const Position& pos): pos(pos) {}

void Attack::execute(Player& player) const { player.attack(pos); }

std::vector<uint8_t> Attack::serialize() const { return Serializer::serialize_attack_cmd(*this); }

Position Attack::get_pos() const { return pos; }
