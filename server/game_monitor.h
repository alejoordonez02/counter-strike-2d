#ifndef GAME_MONITOR_H
#define GAME_MONITOR_H

#include <map>
#include <string>
#include <mutex>
#include <vector>
#include <memory>
#include <unordered_set>

#include "game_loop.h"
#include "common/network/dtos/game_details_dto.h"
#include "common/map_name.h"

class ClientSession;

class GameMonitor {
private:
    std::map<std::string, std::unique_ptr<GameLoop>> games;
    std::unordered_set<std::string> player_usernames;
    bool _is_shutdown;

    std::mutex mtx;

public:
    GameMonitor(): _is_shutdown(false) {}

    std::vector<std::unique_ptr<GameDetailsDTO>> list_games();
    bool create_game(ClientSession* client_s, const std::string& g_name, MapName map_name, Team team);
    bool join_game(ClientSession* client_s, const std::string& g_name, Team team);
    std::unique_ptr<GameDetailsDTO> get_game_details(const std::string& g_name);
    void begin_game(const std::string& g_name);
    bool add_username(const std::string& name);
    void remove_username(const std::string& name);

    void reap_dead_games();
    void shutdown();

    GameMonitor(const GameMonitor&) = delete;
    GameMonitor& operator=(const GameMonitor&) = delete;

    GameMonitor(GameMonitor&&) = delete;
    GameMonitor& operator=(GameMonitor&&) = delete;

    ~GameMonitor() = default;
};

#endif
