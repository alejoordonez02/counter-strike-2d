#include "client/gameloop.h"

#include <unistd.h>
#include <utility>

#include "common/network/dtos/snapshot_dto.h"

GameLoop::GameLoop(Queue<std::unique_ptr<DTO>>& snapshots,
                   Queue<std::shared_ptr<DTO>>& commands,
                   const MapData& map_data, const GameConfig& game_config):
    render(map_data, game_config), snapshots_queue(snapshots), commands_queue(commands),
    input_handler(commands), FRAME_RATE(game_config.window.frame_rate) {
    input_handler.start();
}

void GameLoop::get_snapshot_from_queue(SnapshotDTO& last_snapshot,
        PrivatePlayerDTO& user_data) {
    std::vector<std::unique_ptr<DTO>> dtos(2);

    for (auto& dto_p : dtos) {
        if (not snapshots_queue.try_pop(dto_p))
            continue;
        if (dto_p->get_type() == DTOSerial::SNAPSHOT) {
            auto ptr = static_cast<SnapshotDTO*>(dto_p.get());
            last_snapshot = std::move(*ptr);
        }
        if (dto_p->get_type() == DTOSerial::PLAYER_PRIVATE) {
            auto ptr = static_cast<PrivatePlayerDTO*>(dto_p.get());
            user_data = std::move(*ptr);
        }
        dto_p.reset();
    }

    // si no hay snapshot nueva, devuelve el último estado
    // -> Esto permite que siga renderizando
}

void GameLoop::run() {
    SnapshotDTO last_snapshot;
    PrivatePlayerDTO user_data;
    uint32_t frameStart = SDL_GetTicks();

    // FPS tracking
    // cuenta cuantos frames/bucles hay. Se reinicia luego de 1 segundo
    uint32_t fps_timer = SDL_GetTicks();

    while (is_running) {
        this->get_snapshot_from_queue(last_snapshot, user_data);

        render.update(last_snapshot, user_data, fps_timer);
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
