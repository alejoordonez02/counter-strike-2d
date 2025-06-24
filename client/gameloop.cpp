#include "client/gameloop.h"

#include <unistd.h>
#include <utility>
#include <chrono>


GameLoop::GameLoop(Queue<std::unique_ptr<DTO>>& snapshots,
                   Queue<std::shared_ptr<DTO>>& commands,
                   const MapData& map_data, const GameConfig& game_config):
    render(map_data, game_config), snapshots_queue(snapshots), commands_queue(commands),
    input_handler(commands), FRAME_RATE(game_config.window.frame_rate) {
    input_handler.start();
}

void GameLoop::get_snapshot_from_queue(SnapshotDTO& last_snapshot,
        PrivatePlayerDTO& user_data) {
    auto start_time = std::chrono::high_resolution_clock::now();
    
    // Estrategia más eficiente: procesar por lotes pequeños para evitar acumulación
    std::unique_ptr<DTO> dto_p;
    int processed_count = 0;
    int snapshot_count = 0;
    int private_count = 0;
    int discarded_snapshots = 0;
    int discarded_private = 0;
    
    // Limitar el procesamiento a un máximo por frame para evitar bloqueo
    const int MAX_PROCESS_PER_FRAME = 50;
    
    SnapshotDTO temp_snapshot;
    PrivatePlayerDTO temp_private;
    bool has_new_snapshot = false;
    bool has_new_private = false;
    
    // Procesar DTOs hasta el límite o hasta que se agote la cola
    while (processed_count < MAX_PROCESS_PER_FRAME && snapshots_queue.try_pop(dto_p)) {
        processed_count++;
        
        if (dto_p->get_type() == DTOSerial::SNAPSHOT) {
            if (has_new_snapshot) {
                discarded_snapshots++;  
            } else {
                auto ptr = static_cast<SnapshotDTO*>(dto_p.get());
                temp_snapshot = std::move(*ptr);
                snapshot_count++;
                has_new_snapshot = true;
            }
        }
        else if (dto_p->get_type() == DTOSerial::PLAYER_PRIVATE) {
            if (has_new_private) {
                discarded_private++;  
            } else {
                auto ptr = static_cast<PrivatePlayerDTO*>(dto_p.get());
                temp_private = std::move(*ptr);
                private_count++;
                has_new_private = true;
            }
        }
        dto_p.reset();
    }
    
    // Solo actualizar si encontramos nuevos datos
    if (has_new_snapshot) {
        last_snapshot = std::move(temp_snapshot);
    }
    if (has_new_private) {
        user_data = std::move(temp_private);
    }
    
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    
    // Solo mostrar estadísticas si procesamos algo
    if (processed_count > 0) {
        static int frame_counter = 0;
        static auto last_stats_time = std::chrono::high_resolution_clock::now();
        frame_counter++;
        
        // Mostrar estadísticas cada segundo
        if (std::chrono::duration_cast<std::chrono::milliseconds>(end_time - last_stats_time).count() > 1000) {
            // Verificar si hay más DTOs en cola
            size_t remaining = 0;
            std::unique_ptr<DTO> peek_dto;
            while (snapshots_queue.try_pop(peek_dto)) {
                remaining++;
                if (remaining > 100) break; // Evitar contar infinitamente
            }
            
            std::cout << "Queue Stats - Processed: " << processed_count 
                      << ", Used S: " << snapshot_count << "/" << (snapshot_count + discarded_snapshots)
                      << ", Used P: " << private_count << "/" << (private_count + discarded_private)
                      << ", Remaining: " << remaining
                      << ", Time: " << duration.count() << "μs"
                      << ", FPS: " << frame_counter << std::endl;
            frame_counter = 0;
            last_stats_time = end_time;
        }
    }
}

void GameLoop::run() {
    SnapshotDTO last_snapshot;
    PrivatePlayerDTO user_data;
    uint32_t frameStart = SDL_GetTicks();

    // FPS tracking
    uint32_t fps_timer = SDL_GetTicks();
    
    // Timing statistics
    static auto last_perf_report = std::chrono::high_resolution_clock::now();
    static double total_queue_time = 0;
    static double total_update_time = 0;
    static double total_render_time = 0;
    static int frame_count = 0;
    static int slow_frames = 0;
    
    const double target_frame_time = RATE * 1000.0; // en microsegundos

    while (is_running) {
        auto frame_start = std::chrono::high_resolution_clock::now();
        
        // Medir tiempo de procesamiento de cola
        auto queue_start = std::chrono::high_resolution_clock::now();
        this->get_snapshot_from_queue(last_snapshot, user_data);
        auto queue_end = std::chrono::high_resolution_clock::now();
        
        // Medir tiempo de actualización
        auto update_start = std::chrono::high_resolution_clock::now();
        render.update(last_snapshot, user_data, fps_timer);
        auto update_end = std::chrono::high_resolution_clock::now();
        
        // Medir tiempo de renderizado
        auto render_start = std::chrono::high_resolution_clock::now();
        render.render();
        auto render_end = std::chrono::high_resolution_clock::now();

        is_running = input_handler.alive_status();

        // Calcular tiempo total del frame
        auto frame_end = std::chrono::high_resolution_clock::now();
        double frame_time = std::chrono::duration<double, std::micro>(frame_end - frame_start).count();
        
        if (frame_time > target_frame_time) {
            slow_frames++;
        }

        handle_frame_timing(frameStart);
        
        // Acumular tiempos
        double queue_time = std::chrono::duration<double, std::micro>(queue_end - queue_start).count();
        double update_time = std::chrono::duration<double, std::micro>(update_end - update_start).count();
        double render_time = std::chrono::duration<double, std::micro>(render_end - render_start).count();
        
        total_queue_time += queue_time;
        total_update_time += update_time;
        total_render_time += render_time;
        frame_count++;
        
        auto now = std::chrono::high_resolution_clock::now();
        // Reportar estadísticas cada 2 segundos
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - last_perf_report).count() > 2000) {
            std::cout << "Performance Report (avg per frame):" << std::endl;
            std::cout << "  Queue: " << (total_queue_time / frame_count) << "μs" << std::endl;
            std::cout << "  Update: " << (total_update_time / frame_count) << "μs" << std::endl;
            std::cout << "  Render: " << (total_render_time / frame_count) << "μs" << std::endl;
            std::cout << "  Total: " << ((total_queue_time + total_update_time + total_render_time) / frame_count) << "μs" << std::endl;
            std::cout << "  Target: " << target_frame_time << "μs (" << RATE << "ms)" << std::endl;
            std::cout << "  Slow frames: " << slow_frames << "/" << frame_count 
                      << " (" << (100.0 * slow_frames / frame_count) << "%)" << std::endl;
            
            // Reset
            total_queue_time = total_update_time = total_render_time = 0;
            frame_count = 0;
            slow_frames = 0;
            last_perf_report = now;
        }
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
