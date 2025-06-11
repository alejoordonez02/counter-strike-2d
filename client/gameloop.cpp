#include "client/gameloop.h"
#include "common/network/dtos/snapshot_dto.h"

#include <unistd.h>

#define FRAME_RATE 1000000.0f / 25.0f

GameLoop::GameLoop(Queue<std::unique_ptr<DTO>>& snapshots,
                   Queue<std::shared_ptr<DTO>>& commands, 
                    int user_player_id):
        render(user_player_id),
        snapshots_queue(snapshots),
        commands_queue(commands),
        input_handler(commands){
    input_handler.start();
}

Snapshot GameLoop::get_snapshot_from_queue(Snapshot last_snapshot) {
    std::unique_ptr<DTO> dto_ptr;
    SnapshotDTO* snapshot_dto = nullptr;

    // se asegura que la cola tenga el ultimo estado del juego
    while (snapshots_queue.try_pop(dto_ptr)) {
        if (!dto_ptr) {
            throw std::runtime_error(
                    "Received a null DTO from the snapshots queue.");
        }
        snapshot_dto = dynamic_cast<SnapshotDTO*>(dto_ptr.get());
    }
    if (snapshot_dto) {
        return snapshot_dto->snapshot;
    }
    // si no hay snapshot nueva, devuelve el último estado
    // -> Esto permite que siga renderizando
    return last_snapshot;
}

void GameLoop::run() {
    Snapshot last_snapshot;

    while (is_running) {
        last_snapshot = this->get_snapshot_from_queue(last_snapshot);

        render.update(last_snapshot);
        render.render();

        is_running = input_handler.alive_status();

        usleep(FRAME_RATE);
    }
}
