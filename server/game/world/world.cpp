#include "world.h"

#include <memory>
#include <stdexcept>
#include <utility>

#include "factory/player_factory.h"
#include "map.h"
#include "player.h"

/*
 * Constructor
 * */
World::World(std::shared_ptr<Map>&& map, int max_rounds, float round_time,
             float time_out, const PlayerFactory& player_factory):
    map(std::move(map)), id_gen(0), max_rounds(max_rounds),
    round_time(round_time), time_out(time_out), round_ongoing(false),
    ended(false), player_factory(player_factory) {}

/*
 * Update rounds
 * */
void World::start_round() {
    time_out.restart();
    tt_team.restart();
    ct_team.restart();
    map->restart();
    round_time.restart();
}

void World::sum_won_round(Team& team) {
    team.sum_won_round();
    start_round();
}

void World::update_rounds(float dt) {
    round_time.update(dt);

    if (tt_team.lost_round(map->get_bomb_state(), round_time))
        sum_won_round(ct_team);

    if (ct_team.lost_round(map->get_bomb_state(), round_time))
        sum_won_round(tt_team);
}

/*
 * Update world
 * */
void World::update(float dt) {
    if (ended) return;
    time_out.update(dt);
    if (!time_out.is_done()) return;

    int updates = 1;
    if (dt > WorldTiming::DT) {
        updates = (int)(dt / WorldTiming::DT);
        dt = WorldTiming::DT;
    }

    for (int i = 0; i < updates; i++) {
        tt_team.update(dt);
        ct_team.update(dt);
        map->update(dt);
        update_rounds(dt);
    }
}

/*
 * Add a player
 * */
std::shared_ptr<Player> World::add_player(TeamName team) {
    std::shared_ptr<Player> p;
    switch (team) {
        case TeamName::TERRORIST:
            p = tt_team.add_player(id_gen++, player_factory);
            break;
        case TeamName::COUNTER_TERRORIST:
            p = ct_team.add_player(id_gen++, player_factory);
            break;
        default:
            throw std::runtime_error("World error: team does not exist");
    }

    map->add_collidable(p);
    return p;
}

/*
 * Check wheter the game has ended
 * */
bool World::has_ended() const { return ended; }

/*
 * Get a snapshot of the current state of the world
 * */
std::shared_ptr<SnapshotDTO> World::get_snapshot() {
    auto snapshot = std::make_shared<SnapshotDTO>();
    snapshot->round_finished = !round_ongoing;
    snapshot->game_finished = ended;
    snapshot->initial_phase = true;  // ?
    snapshot->round_number = rounds;
    snapshot->terrorists_score = tt_team.get_won_rounds();
    snapshot->counter_terrorists_score = ct_team.get_won_rounds();
    tt_team.push_player_data(snapshot->players);
    ct_team.push_player_data(snapshot->players);

    // TODO: Eliminar. Lo dejo asi para que se vea en el mapa y
    // se sepa que esta disponible para usar
    WeaponDTO w1;
    w1.w_type = WeaponName::AK47;
    w1.x = 224;
    w1.y = 228;
    snapshot->weapons_on_floor.push_back(std::move(w1));
    WeaponDTO w2;
    w2.w_type = WeaponName::GLOCK;
    w2.x = 128;
    w2.y = 96;
    snapshot->weapons_on_floor.push_back(std::move(w2));
    WeaponDTO w3;
    w3.w_type = WeaponName::BOMB;
    w3.x = 100;
    w3.y = 196;
    snapshot->weapons_on_floor.push_back(std::move(w3));

    snapshot->serialize();
    return snapshot;
}
