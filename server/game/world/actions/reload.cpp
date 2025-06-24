#include "reload.h"

#include "equipment/weapon.h"

Reload::Reload(std::shared_ptr<Weapon> weapon):
    weapon(weapon), reload_time(weapon->get_reload_time()) {}

void Reload::update(float dt) {
    reload_time.update(dt);
    if (!reload_time.is_done()) return;
    weapon->reload();
}
