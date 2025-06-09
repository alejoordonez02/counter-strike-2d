#include <unistd.h>

#include "gameloop.h"
#include "../common/network/dtos/snapshot_dto.h"

#define FRAME_RATE 1000000.0f/25.0f

GameLoop::GameLoop(Queue<std::unique_ptr<DTO>>& snapshots, Queue<std::shared_ptr<DTO>>& commands): 
    render(),
    snapshots_queue(snapshots),
    commands_queue(commands),
    input_handler(commands)
{}


Snapshot GameLoop::get_snapshot_from_queue(){
    std::unique_ptr<DTO> dto_ptr;
    SnapshotDTO* snapshot_dto = nullptr;

    // Esperar hasta recibir un SnapshotDTO válido
    while (true) {
        // se asegura que la cola tenga el ultimo estado del juego
        while (snapshots_queue.try_pop(dto_ptr)) {
            if (!dto_ptr) {
                throw std::runtime_error("Received a null DTO from the snapshots queue.");
            }
            snapshot_dto = dynamic_cast<SnapshotDTO*>(dto_ptr.get());
        }
        if (snapshot_dto) {
            return snapshot_dto->snapshot;
        }
        // REFACTOR: Si la cola está vacía, esperar un poco antes de volver a intentar
        usleep(1000);
    }
}


void GameLoop::run(){
    Snapshot last_snapshot;

    while (is_running) {
        last_snapshot = this->get_snapshot_from_queue();
        
        render.update(last_snapshot);
        render.render();
        
        is_running = input_handler.handle_events();

        usleep(FRAME_RATE);
        
    }
}

