#ifndef SERVER_GAME_MONITOR_H
#define SERVER_GAME_MONITOR_H

class GameMonitor {
    private:
    public:
    GameMonitor();

    void reap_dead_games();

    GameMonitor(const GameMonitor&) = delete;
    GameMonitor& operator=(const GameMonitor&) = delete;

    GameMonitor(GameMonitor&&) = delete;
    GameMonitor& operator=(GameMonitor&&) = delete;

    ~GameMonitor() = default;
};

#endif
