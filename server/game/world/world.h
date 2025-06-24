#ifndef SERVER_MODEL_WORLD_H
#define SERVER_MODEL_WORLD_H

#include <chrono>
#include <memory>
#include <stdexcept>

#include "common/team_name.h"
#include "map.h"
#include "player.h"
#include "server/game/factory/player_factory.h"
#include "team/counter_terrorists.h"
#include "team/terrorists.h"
#include "weapon_factory.h"

namespace WorldTiming {
constexpr int constant_tick_rate = 60;
using Duration = std::chrono::duration<float>;
using Ms = std::chrono::milliseconds;
constexpr float DT(Duration(Ms(1000) / constant_tick_rate).count());
}  // namespace WorldTiming

class World {
private:
    Terrorists tt_team;
    CounterTerrorists ct_team;
    std::shared_ptr<Map> map;
    int id_gen;
    int max_rounds;
    int rounds;
    Timer round_time;
    Timer time_out;
    bool round_ongoing;
    bool started;
    bool ended;

    PlayerFactory player_factory;
    std::shared_ptr<WeaponFactory> weapon_factory;

    void start_round();

    void sum_won_round(Team& team);

    void update_rounds(float dt);

public:
    World(std::shared_ptr<Map>&& map, int max_rounds, float round_time,
          float time_out, /* int max_terrorists, int max_counter_terrorists, */
          const PlayerFactory& player_factory,
          std::shared_ptr<WeaponFactory> weapon_factory);

    void update(float dt);

    void start() { started = true; }

    std::shared_ptr<Player> add_player(TeamName team);

    bool team_is_full(TeamName team) const {
        switch (team) {
            case TeamName::TERRORIST:
                return tt_team.is_full();
            case TeamName::COUNTER_TERRORIST:
                return tt_team.is_full();
            default:
                throw std::runtime_error("World error: unknown team name");
        }
    }

    bool has_ended() const;

    std::shared_ptr<SnapshotDTO> get_snapshot();
};

#endif
