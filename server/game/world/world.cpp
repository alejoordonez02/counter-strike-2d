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
    map(std::move(map)), max_rounds(max_rounds), round_time(round_time),
    time_out(time_out), round_ongoing(false), ended(false),
    player_factory(player_factory) {}

/*
 * Update rounds
 * */
void World::start_round() {
    tt_team.restart();
    ct_team.restart();
    map->restart();
    round_time.restart();
}

void World::update_rounds(float dt) {
    round_time.update(dt);

    if (tt_team.lost_round(map->get_bomb_state(), round_time) ||
        ct_team.lost_round(map->get_bomb_state(), round_time))
        rounds++;
}

/*
 * Update world
 * */
void World::update(float dt) {
    if (ended) return;

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
Snapshot World::get_snapshot() {
    Snapshot snapshot;
    snapshot.round_finished = !round_ongoing;
    snapshot.game_finished = ended;
    snapshot.initial_phase = true;  // ?
    snapshot.round_number = rounds;
    snapshot.terrorists_score = tt_team.get_won_rounds();
    snapshot.counter_terrorists_score = ct_team.get_won_rounds();
    tt_team.push_player_data(snapshot.players);
    ct_team.push_player_data(snapshot.players);

    // TODO: Eliminar. Lo dejo asi para que se vea en el mapa y 
    // se sepa que esta disponible para usar
    snapshot.weapons_on_floor.push_back({WeaponType::AK47, 224, 228});
    snapshot.weapons_on_floor.push_back({WeaponType::Glock, 128, 96});
    snapshot.weapons_on_floor.push_back({WeaponType::Bomb, 100, 196});

    return snapshot;
}
