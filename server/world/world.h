#ifndef SERVER_MODEL_WORLD_H
#define SERVER_MODEL_WORLD_H

#include <chrono>
#include <memory>

#include "server/world/map.h"
#include "server/world/player.h"

/*
 * Deltas de tiempo correspondientes a un tick rate constante
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

    bool terrorists_won_round() const;

    bool counter_terrorists_won_round() const;

    void start_round();

    void sum_round(int& team_won_rounds);

    void update_rounds(float dt);

public:
    World(std::shared_ptr<Map>&& map, int rounds, float round_time,
          float time_out);

    void update(float dt);

    std::shared_ptr<Player> add_player();

    Snapshot get_snapshot();

    bool has_ended() const;
};

#endif
