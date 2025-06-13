#ifndef MOCK_SERVER_H
#define MOCK_SERVER_H

#include <algorithm>
#include <iostream>
#include <memory>
#include <thread>
#include <utility>

#include "common/network/dtos/snapshot_dto.h"
#include "common/snapshot.h"
#include "server/acceptor.h"
#include "server/client_handler.h"
#include "server/cmd_constructor.h"
#include "server/model/equipment.h"
#include "server/model/player.h"
#include "server/model/weapons.h"

using Duration = std::chrono::duration<float>;
using Clock = std::chrono::steady_clock;
using Ms = std::chrono::milliseconds;

#define TICK_RATE 64

class MockServer {
    private:
    static inline int id = 0;
    static inline int get_player_id() { return id++; }
    static inline std::unique_ptr<Equipment> get_starting_equipment1() {
        return std::make_unique<Equipment>(std::make_unique<Fist>(),
                                           std::make_unique<Glock>(),
                                           std::make_unique<Knife>(), 0);
    };
    static inline float get_player_max_velocity() { return 20; }
    static inline float get_player_acceleration() { return 10; }
    static inline float get_player_radius() { return 1; }
    static inline int get_player_starting_money() { return 500; }
    static inline int get_player_max_health() { return 1; }

    static inline std::shared_ptr<Player> get_player(Map& map) {
        return std::make_shared<Player>(
                get_player_id(), Position(0, 0), get_starting_equipment1(), map,
                get_player_max_velocity(), get_player_acceleration(),
                get_player_radius(), get_player_starting_money(),
                get_player_max_health());
    }

    public:
    void start(const std::string& servname) {
        std::vector<std::unique_ptr<ClientHandler>> clients;

        Acceptor acceptor(servname, clients);
        acceptor.start();

        std::string start;
        do {
            getline(std::cin, start);
        } while (start != "s");

        acceptor.stop();
        acceptor.join();

        std::vector<std::unique_ptr<PlayerHandler>> handlers;
        std::vector<std::shared_ptr<Player>> players;

        Map map;

        for (auto& c : clients) {
            auto p = get_player(map);
            map.add_collidable(*p);
            auto h = c->play(p);
            h->start();
            players.push_back(std::move(p));
            handlers.push_back(std::move(h));
        }

        Snapshot s;
        s.round_number = 0;
        for (auto& p : players) s.players.push_back(p->get_data());

        for (auto& h : handlers) {
            h->send_snapshot(s);
        }

        CmdConstructor constructor;

        auto t1 = Clock::now();
        Clock::duration tick_duration = Ms(1000) / TICK_RATE;
        float elapsed_seconds = Duration(tick_duration).count();

        while (true) {
            for (auto& h : handlers) h->play();

            for (auto& p : players) p->update(elapsed_seconds);

            Snapshot s;
            s.round_number = 1;
            for (auto& p : players) s.players.push_back(p->get_data());

            for (auto& h : handlers) {
                h->send_snapshot(s);
            }

            auto t2 = Clock::now();
            auto work_time = t2 - t1;
            auto rest_time = tick_duration - work_time;

            if (rest_time.count() > 0) {
                std::this_thread::sleep_for(rest_time);
                t1 += tick_duration;
            }
        }
    }
};

#endif
