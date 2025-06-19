#ifndef CLIENT_GAMELOOP_H
#define CLIENT_GAMELOOP_H

#include <memory>

#include "client/input_handler.h"
#include "client/render.h"
#include "common/network/dto.h"
#include "common/queue.h"
#include "common/snapshot.h"
#include "common/maploader.h"

const static int FRAME_RATE = 30;
// Va con milisegundos ya que utilizo el timer de SDL
const static int RATE = 1000 / FRAME_RATE;


class GameLoop {
    private:
    Render render;

    bool is_running = true;

    Queue<std::unique_ptr<DTO>>& snapshots_queue;
    Queue<std::unique_ptr<DTO>>& commands_queue;

    InputHandler input_handler;

    public:
    GameLoop(Queue<std::unique_ptr<DTO>>& snapshots,
             Queue<std::unique_ptr<DTO>>& commands, int user_player_id, const MapData& map_data);
    void run();

    void debug_get_fps(uint32_t& fps_timer, int& frame_count);

    void handle_frame_timing(uint32_t& t1);

    // void handle_frame_timing(uint32_t& t1);

    Snapshot get_snapshot_from_queue(Snapshot last_snapshot);
};

#endif  // GAMELOOP_H
