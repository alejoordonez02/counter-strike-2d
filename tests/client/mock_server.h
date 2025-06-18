#ifndef MOCK_SERVER_H
#define MOCK_SERVER_H

#include <iostream>
#include <memory>
#include <thread>
#include <utility>

#include "common/maploader.h"
#include "common/snapshot.h"
#include "server/acceptor.h"
#include "server/client_handler.h"
#include "server/model/equipment.h"
#include "server/model/player.h"
#include "server/model/random.h"
#include "server/model/structure.h"
#include "server/model/weapons.h"

using Duration = std::chrono::duration<float>;
using Clock = std::chrono::steady_clock;
using Ms = std::chrono::milliseconds;

class Logger {
    static inline std::string secc = "<=========>\n";
    static inline std::string sec = "  <=====>\n";
    static inline std::string sepp = ",\n";
    static inline std::string sep = ", ";

    static void log(const PlayerData& p) {
        // clang-format off
        std::cout << sec
                  << "id: " << p.player_id << sepp
                  << "pos(" << p.x << sep << p.y << ")" << sep << sepp
                  << "dir(" << p.aim_x << sep << p.aim_y << ")" << sepp;
        // clang-format on
    }

public:
    static void log(const Snapshot& s) {
        std::cout << secc;
        for (auto& p : s.players) log(p);
    }
};

class MockServer {
private:
    std::string servname;
    static inline int tick_rate = 20;
    static inline int command_rate = 20;
    static inline int id = 1;
    static inline int get_player_id() { return id++; }
    static inline std::unique_ptr<Equipment> get_starting_equipment1() {
        return std::make_unique<Equipment>(std::make_unique<Fist>(),
                                           std::make_unique<Glock>(),
                                           std::make_unique<Knife>(), 0);
    };
    static inline float get_player_max_velocity() { return 50; }
    static inline float get_player_acceleration() { return 300; }
    static inline float get_player_radius() { return 10; }
    static inline int get_player_starting_money() { return 500; }
    static inline int get_player_max_health() { return 100; }
    static inline Position get_random_position() {
        return Position(Random::get(-100, 100), Random::get(-100, 100));
    }

    static inline std::shared_ptr<Player> get_player(
        std::weak_ptr<Map> map, Position pos = get_random_position()) {
        return std::make_shared<Player>(
            get_player_id(), pos, get_starting_equipment1(), map,
            get_player_max_velocity(), get_player_acceleration(),
            get_player_radius(), get_player_starting_money(),
            get_player_max_health());
    }

public:
    MockServer(const std::string& servname): servname(servname) {}

    void start() {
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

        auto map = std::make_shared<Map>();

        MapLoader map_loader;
        MapData map_data =
            map_loader.loadMapData("tests/client/prueba_mapa_mod.yaml");

        for (auto& b : map_data.blocks) {
            auto s = std::make_shared<Structure>(Position(b.x, b.y), 32);
            map->add_collidable(s);
        }

        int x = 0;
        int y = 0;
        for (auto& c : clients) {
            auto p = get_player(map, Position(x += 100, y));
            map->add_collidable(p);
            auto h = c->play(p);
            h->start();
            players.push_back(std::move(p));
            handlers.push_back(std::move(h));
        }

        Snapshot s;
        s.round_number = 0;
        for (auto& p : players) s.players.push_back(p->get_data());

        for (auto& h : handlers) h->send_snapshot(s);

        auto t1 = Clock::now();
        Clock::duration tick_duration = Ms(1000) / tick_rate;
        float elapsed_seconds = Duration(tick_duration).count();

        while (true) {
            /*
             * Cada handler ejecuta varios comandos por tick
             * */
            for (int i = 0; i < command_rate; i++)
                for (auto& h : handlers) h->play();

            for (auto& p : players) p->update(elapsed_seconds);

            Snapshot s;
            s.round_number = 1;
            for (auto& p : players) {
                s.players.push_back(p->get_data());
            }

            // Logger::log(s);

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
