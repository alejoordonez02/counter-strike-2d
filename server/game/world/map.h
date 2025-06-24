#ifndef SERVER_MODEL_MAP_H
#define SERVER_MODEL_MAP_H

#include <memory>
#include <vector>

#include "drop.h"
#include "equipment/bomb.h"
#include "physics/hitbox.h"
#include "physics/structure.h"
#include "snapshot_dto.h"

class Map {
private:
    std::vector<std::shared_ptr<Hitbox>> collidables;
    std::vector<std::unique_ptr<Drop>> drops;
    std::vector<Structure> bomb_site;
    std::vector<Position> tt_spawn;
    std::vector<Position> ct_spawn;
    std::optional<Bomb> bomb;

public:
    Map(const std::vector<std::shared_ptr<Hitbox>>& collidables,
        std::vector<std::unique_ptr<Drop>>&& drops,
        const std::vector<Structure>& bomb_site,
        const std::vector<Position>& tt_spawn,
        const std::vector<Position>& ct_spawn);

    void update(float dt);

    void restart();

    Position get_tt_spawn() const;

    Position get_ct_spawn() const;

    void add_collidable(std::shared_ptr<Hitbox> cll);

    std::vector<std::shared_ptr<Hitbox>>& get_collidables();

    std::unique_ptr<Drop> pickup(const Position& pos) {
        for (auto d = drops.begin(); d != drops.end(); ++d) {
            if ((*d)->intersects(pos)) {
                auto item = std::move(*d);
                drops.erase(d);
                return item;
            }
        }
        return nullptr;
    }

    void drop(std::unique_ptr<Drop> item) {
        if (!item) return;
        drops.push_back(std::move(item));
    }

    std::vector<Structure>& get_bomb_site();
    Position get_bomb_position();

    void plant_bomb(const Position& pos);
    void defuse_bomb();

    BombState get_bomb_state() {
        if (!bomb) return BombState::NOT_PLANTED;
        return bomb->get_state();
    }

    void push_map_data(std::shared_ptr<SnapshotDTO> snapshot);
};

#endif
