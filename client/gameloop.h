#ifndef CLIENT_GAMELOOP_H
#define CLIENT_GAMELOOP_H

#include <memory>

#include "client/input_handler.h"
#include "client/render.h"
#include "common/maploader.h"
#include "common/network/dto.h"
#include "common/network/dtos/snapshot_dto.h"
#include "common/queue.h"

const static int FRAME_RATE = 70;
// Va con milisegundos ya que utilizo el timer de SDL
const static int RATE = 1000 / FRAME_RATE;

class GameLoop {
private:
    Render render;

    bool is_running = true;

    Queue<std::unique_ptr<DTO>>& snapshots_queue;
    Queue<std::shared_ptr<DTO>>& commands_queue;

    InputHandler input_handler;

public:
    GameLoop(Queue<std::unique_ptr<DTO>>& snapshots,
             Queue<std::shared_ptr<DTO>>& commands, const MapData& map_data);
    void run();

    void debug_get_fps(uint32_t& fps_timer, int& frame_count);

    void handle_frame_timing(uint32_t& t1);

    // void handle_frame_timing(uint32_t& t1);

    void get_snapshot_from_queue(SnapshotDTO& last_snapshot, PrivatePlayerDTO& user_data);
};

#endif  // GAMELOOP_H
