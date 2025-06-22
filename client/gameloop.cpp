#include "client/gameloop.h"

#include <unistd.h>

#include "common/network/dtos/snapshot_dto.h"

GameLoop::GameLoop(Queue<std::unique_ptr<DTO>>& snapshots,
                   Queue<std::unique_ptr<DTO>>& commands,
                   const MapData& map_data):
    render(map_data), snapshots_queue(snapshots), commands_queue(commands),
    input_handler(commands) {
    input_handler.start();
}

SnapshotDTO GameLoop::get_snapshot_from_queue(SnapshotDTO last_snapshot) {
    std::unique_ptr<DTO> dto_ptr;
    SnapshotDTOB* snapshot_dto = nullptr;

    if (snapshots_queue.try_pop(dto_ptr)) {
        if (!dto_ptr) {
            throw std::runtime_error(
                "Received a null DTO from the snapshots queue.");
        }
        snapshot_dto = dynamic_cast<SnapshotDTOB*>(dto_ptr.get());
    }
    if (snapshot_dto) {
        return snapshot_dto->snapshot;
    }
    // si no hay snapshot nueva, devuelve el último estado
    // -> Esto permite que siga renderizando
    return last_snapshot;
}

void GameLoop::run() {
    SnapshotDTO last_snapshot;
    uint32_t frameStart = SDL_GetTicks();

    // FPS tracking
    uint32_t fps_timer = SDL_GetTicks();  // marca el inicio de un segundo
    // cuenta cuantos frames/bucles hay. Se reinicia luego de 1 segundo
    int frame_count = 0;

    while (is_running) {
        last_snapshot = this->get_snapshot_from_queue(last_snapshot);

        render.update(last_snapshot);
        render.render();

        debug_get_fps(fps_timer, frame_count);

        is_running = input_handler.alive_status();

        handle_frame_timing(frameStart);
    }
}

void GameLoop::debug_get_fps(uint32_t& fps_timer, int& frame_count) {
    frame_count++;  // contar frame renderizado

    uint32_t now = SDL_GetTicks();
    // si pasó 1 segundo imprime los frames y resetea contador
    if (now - fps_timer >= 1000) {
        // std::cout << "FPS: " << frame_count << std::endl;
        frame_count = 0;
        fps_timer = now;
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
