#include "client/gameloop.h"

#include <unistd.h>
#include <utility>


GameLoop::GameLoop(Queue<std::unique_ptr<DTO>>& snapshots,
                   Queue<std::shared_ptr<DTO>>& commands,
                   const MapData& map_data, const GameConfig& game_config):
    render(map_data, game_config), snapshots_queue(snapshots), commands_queue(commands),
    input_handler(commands), FRAME_RATE(game_config.window.frame_rate) {
    input_handler.start();
}

void GameLoop::get_snapshot_from_queue(SnapshotDTO& last_snapshot,
        PrivatePlayerDTO& user_data, uint8_t skip_count) {
    // usa skip_count calculado en el frame anterior

    std::unique_ptr<DTO> dto_p;
    bool found_snapshot = false;
    bool found_private = false;
    int processed = 0;
    int skipped = 0;
    
    // Procesar DTOs hasta encontrar los más recientes
    while (snapshots_queue.try_pop(dto_p) && processed < 100) {
        processed++;
        
        if (dto_p->get_type() == DTOSerial::SNAPSHOT) {
            if (skipped < skip_count) {
                // saltear este snapshot
                skipped++;
            } else {
                // Usar este snapshot (siempre sobrescribir con el más reciente)
                auto ptr = static_cast<SnapshotDTO*>(dto_p.get());
                last_snapshot = std::move(*ptr);
                found_snapshot = true;
            }
        }
        else if (dto_p->get_type() == DTOSerial::PLAYER_PRIVATE) {
            if (skipped < skip_count) {
                // Saltear este private data
                skipped++;
            } else {
                // Usar este private data (siempre sobrescribir con el más reciente)
                auto ptr = static_cast<PrivatePlayerDTO*>(dto_p.get());
                user_data = std::move(*ptr);
                found_private = true;
            }
        }
        dto_p.reset();
        
        // Si encontramos ambos y no necesitamos saltear más, podemos parar
        if (found_snapshot && found_private && skipped >= skip_count) {
            // Pero seguimos procesando un poco más para no acumular
            if (processed > 10) break;
        }
    }
}

void GameLoop::run() {
    SnapshotDTO last_snapshot;
    PrivatePlayerDTO user_data;
    uint32_t frameStart = SDL_GetTicks();

    // FPS tracking
    uint32_t fps_timer = SDL_GetTicks();
    uint8_t frames_to_skip = 0;  // Del frame anterior

    while (is_running) {
        this->get_snapshot_from_queue(last_snapshot, user_data, frames_to_skip);

        render.update(last_snapshot, user_data, fps_timer);
        render.render();

        is_running = input_handler.alive_status();

        frames_to_skip = handle_frame_timing(frameStart);
    }
}

uint8_t GameLoop::handle_frame_timing(uint32_t& t1) {
    uint32_t t2 = SDL_GetTicks();
    uint8_t frames_to_skip = 0;

    // cuando tiempo debe dormir
    int rest = RATE - (t2 - t1);
    // si se pasó (frame negativo), hay que saltar frames
    // si no, dormir el tiempo restante
    if (rest < 0) {
        int behind = -rest;  // siempre positivo
        int lost = behind - behind % RATE;

        t1 += lost;
        frames_to_skip = int(lost / RATE);  // truncar hacia abajo

        render.skip_frames(frames_to_skip);
    } else {
        SDL_Delay(rest);
    }

    // para el siguiente loop
    t1 = SDL_GetTicks();
    
    return frames_to_skip;
}
