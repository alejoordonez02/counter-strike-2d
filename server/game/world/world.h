#ifndef SERVER_MODEL_WORLD_H
#define SERVER_MODEL_WORLD_H

#include <chrono>
#include <memory>

#include "common/team_name.h"
#include "map.h"
#include "player.h"
#include "server/game/factory/player_factory.h"

/*
 * Deltas de tiempo correspondientes a un tick rate constante, de éste forma
 * queda desacoplada la noción de tiempo en World del tick rate del server
 * */
namespace WorldTiming {
constexpr int constant_tick_rate = 60;
using Duration = std::chrono::duration<float>;
using Ms = std::chrono::milliseconds;
constexpr float DT(Duration(Ms(1000) / constant_tick_rate).count());
}  // namespace WorldTiming

class World {
private:
    std::vector<std::shared_ptr<Player>> players;
    std::shared_ptr<Map> map;
    int rounds;
    Timer round_time;
    float time_out;
    bool round_ongoing;
    bool ended;
    int tt_won_rounds;
    int ct_won_rounds;

    PlayerFactory player_factory;

    bool terrorists_won_round() const;

    bool counter_terrorists_won_round() const;

    void start_round();

    void sum_round(int& team_won_rounds);

    void update_rounds(float dt);

public:
    World(std::shared_ptr<Map>&& map, int rounds, float round_time,
          float time_out, const PlayerFactory& player_factory);

    void update(float dt);

    std::shared_ptr<Player> add_player(TeamName team);

    Snapshot get_snapshot();

    bool has_ended() const;
};

#endif
