#ifndef CLIENT_GAMELOOP_H
#define CLIENT_GAMELOOP_H

#include <memory>

#include "client/input_handler.h"
#include "client/render.h"
#include "common/maploader.h"
#include "common/network/dto.h"
#include "common/network/dtos/snapshot_dto.h"
#include "common/queue.h"
#include "client/game_config.h"


class GameLoop {
private:
    Render render;

    bool is_running = true;

    Queue<std::unique_ptr<DTO>>& snapshots_queue;
    Queue<std::shared_ptr<DTO>>& commands_queue;

    InputHandler input_handler;

    const int FRAME_RATE;
    // Va con milisegundos ya que utilizo el timer de SDL
    const int RATE = 1000 / FRAME_RATE;

public:
    GameLoop(Queue<std::unique_ptr<DTO>>& snapshots,
             Queue<std::shared_ptr<DTO>>& commands, const MapData& map_data, const GameConfig& game_config);
    void run();

    uint8_t handle_frame_timing(uint32_t& t1);

    void get_snapshot_from_queue(SnapshotDTO& last_snapshot, PrivatePlayerDTO& user_data, uint8_t skip_count);
};

#endif  // GAMELOOP_H
