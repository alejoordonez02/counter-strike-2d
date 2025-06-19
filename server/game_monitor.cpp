#include "game_monitor.h"
#include "common/network/dtos/game_details_dto.h"

std::vector<std::unique_ptr<GameDetailsDTO>> GameMonitor::list_games() {
    std::unique_lock<std::mutex> lck(mtx);

    std::vector<std::unique_ptr<GameDetailsDTO>> list;
    for (const auto& [n, g]: games) {
        list.push_back(g->get_details_dto());
    }

    return list;
}

bool GameMonitor::create_game(ClientSession* client_s, const std::string& g_name, MapName map_name, Team team) {
    std::unique_lock<std::mutex> lck(mtx);

    if (_is_shutdown)
        return false;
    if (games.count(g_name))
        return false;

    auto new_game = std::make_unique<GameLoop>(g_name, map_name);
    new_game->add_client(client_s, team);
    games[g_name] = std::move(new_game);

    return true;
}

bool GameMonitor::join_game(ClientSession* client_s, const std::string& g_name, Team team) {
    std::unique_lock<std::mutex> lck(mtx);

    if (_is_shutdown)
        return false;
    if (not games.count(g_name))
        return false;

    auto game = games[g_name].get();

    return game->add_client(client_s, team);
}

std::unique_ptr<GameDetailsDTO> GameMonitor::get_game_details(const std::string& g_name) {
    std::unique_lock<std::mutex> lck(mtx);

    if (not games.count(g_name))
        std::runtime_error("GameMonitor error: game not found");

    auto game = games[g_name].get();

    return game->get_details_dto();
}

void GameMonitor::begin_game(const std::string& g_name) {
    std::unique_lock<std::mutex> lck(mtx);

    if (not games.count(g_name))
        std::runtime_error("GameMonitor error: game not found");

    games[g_name]->start();
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

    for (auto it = games.begin(); it != games.end(); ) {
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

    _is_shutdown = true;
    // manejar cierre de server
}
