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

class Team {
private:
    std::vector<std::unique_ptr<Player>> players;
    int rounds_won;

    PlayerFactory player_factory;

    void switch_players(Team& other) {
        std::vector<std::unique_ptr<Player>> tmp;
        tmp = std::move(other.players);
        other.players = std::move(players);
        players = std::move(tmp);
    }

    void swicth_rounds_won(Team& other) {
        int tmp;
        tmp = other.rounds_won;
        other.rounds_won = rounds_won;
        rounds_won = tmp;
    }

public:
    std::shared_ptr<Player> add_player() {}

    virtual bool won_round() = 0;

    Team& switch_sides(Team& other) {
        switch_players(other);
        swicth_rounds_won(other);
        return *this;
    }
};

class Terorirsts: public Team {};

class CounterTerrorists: public Team {};

class World {
private:
    std::unique_ptr<Team> team1;
    std::unique_ptr<Team> team2;
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
