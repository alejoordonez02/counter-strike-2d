#ifndef WEAPONS_H
#define WEAPONS_H

#include <cstdint>

enum class WeaponName : uint8_t { NONE, KNIFE, GLOCK, AK47, M3, AWP, BOMB };
enum class WeaponType : uint8_t { NONE, PRIMARY, SECONDARY, KNIFE };

#endif
