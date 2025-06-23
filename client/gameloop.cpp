#include "client/gameloop.h"

#include <unistd.h>
#include <utility>

#include "common/network/dtos/snapshot_dto.h"

GameLoop::GameLoop(Queue<std::unique_ptr<DTO>>& snapshots,
                   Queue<std::unique_ptr<DTO>>& commands,
                   const MapData& map_data):
    render(map_data), snapshots_queue(snapshots), commands_queue(commands),
    input_handler(commands) {
    input_handler.start();
}

void GameLoop::get_snapshot_from_queue(SnapshotDTO& last_snapshot) {
    std::unique_ptr<DTO> dto_ptr;

    if (not snapshots_queue.try_pop(dto_ptr))
        return;

    auto s_dto_ptr = static_cast<SnapshotDTO*>(dto_ptr.get());
    last_snapshot = std::move(*s_dto_ptr);
    dto_ptr.reset();
    
    // si no hay snapshot nueva, devuelve el último estado
    // -> Esto permite que siga renderizando
}

void GameLoop::run() {
    SnapshotDTO last_snapshot;
    uint32_t frameStart = SDL_GetTicks();

    // FPS tracking
    // cuenta cuantos frames/bucles hay. Se reinicia luego de 1 segundo
    uint32_t fps_timer = SDL_GetTicks();

    while (is_running) {
        this->get_snapshot_from_queue(last_snapshot);

        render.update(last_snapshot, fps_timer);
        render.render();

        is_running = input_handler.alive_status();

        handle_frame_timing(frameStart);
    }
}

void GameLoop::handle_frame_timing(uint32_t& t1) {
    uint32_t t2 = SDL_GetTicks();

    // cuando tiempo debe dormir
    int rest = RATE - (t2 - t1);
    // si se pasó (frame negativo), hay que saltar frames
    // si no, dormir el tiempo restante
    if (rest < 0) {
        // std::cout << "LOG: Se pasó el tiempo de frame por " << -rest << "
        // milisegundos.\n";
        int behind = -rest;  // siempre positivo
        int lost = behind - behind % RATE;

        t1 += lost;
        uint8_t frames_to_skip = int(lost / RATE);  // truncar hacia abajo

        render.skip_frames(frames_to_skip);
    } else {
        // std::cout << "LOG: Debe dormir " << rest << " milisegundos.\n";
        SDL_Delay(rest);
    }

    // NOTE: No pongo el numero de iteración del loop
    // cada Animation se encarga de avanzar su frame

    // para el siguiente loop
    t1 = SDL_GetTicks();
}
