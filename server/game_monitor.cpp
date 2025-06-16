#include "game_monitor.h"

#include "common/network/dtos/game_details_dto.h"

std::vector<std::unique_ptr<GameDetailsDTO>> GameMonitor::list_games() {
    std::unique_lock<std::mutex> lck(mtx);

    std::vector<std::unique_ptr<GameDetailsDTO>> list;
    for (const auto& [k, v] : games) {
        list.push_back(v->get_details());
    }

    return list;
}

bool GameMonitor::create_game(ClientSession* client_s,
                              const std::string& g_name, MapName map_name) {
    std::unique_lock<std::mutex> lck(mtx);

    if (_is_shutdown)
        return false;
    if (games.count(g_name))
        return false;

    auto new_game = std::make_unique<GameLoop>(g_name, map_name);
    new_game->start();
    new_game->add_client(client_s);
    games[g_name] = std::move(new_game);
    player_count[g_name] = 1;

    return true;
}

bool GameMonitor::join_game(ClientSession* client_s,
                            const std::string& g_name) {
    std::unique_lock<std::mutex> lck(mtx);

    if (_is_shutdown)
        return false;
    if (not games.count(g_name) || player_count[g_name] == MAX_PLYS_PER_GAME)
        return false;
    auto game = games[g_name].get();
    if (game->has_started())
        return false;

    game->add_client(client_s);
    player_count[g_name]++;

    return true;
}

bool GameMonitor::add_username(const std::string& name) {
    std::unique_lock<std::mutex> lck(mtx);

    if (player_usernames.count(name))
        return false;

    player_usernames.insert(name);
    return true;
}

void GameMonitor::remove_username(const std::string& name) {
    std::unique_lock<std::mutex> lck(mtx);

    if (not player_usernames.count(name))
        std::runtime_error("GameMonitor error: username to remove not found");

    player_usernames.erase(name);
}

void GameMonitor::reap_dead_games() {
    std::unique_lock<std::mutex> lck(mtx);

    for (auto it = games.begin(); it != games.end();) {
        if (not it->second->is_alive()) {
            it->second->join();
            it = games.erase(it);
        } else {
            it++;
        }
    }
}

void GameMonitor::shutdown() {
    std::unique_lock<std::mutex> lck(mtx);
    // manejar cierre de server
}
