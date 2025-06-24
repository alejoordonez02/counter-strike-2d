#include "client/render.h"
#include <chrono>


Render::Render(const MapData& map_data, const GameConfig& game_config):
    sdl(SDL_INIT_VIDEO), window(
          "Counter Strike 2D",
          SDL_WINDOWPOS_UNDEFINED,
          SDL_WINDOWPOS_UNDEFINED,
          game_config.window.window_width,
          game_config.window.window_height,
          game_config.window.use_fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN
      ),
    renderer(window, -1, SDL_RENDERER_ACCELERATED), map_data(map_data), USE_FOV(game_config.fov.use_field_of_view) {
    // color de fondo negro
    renderer.SetDrawColor(0, 0, 0, 0);

    // cargar texturas
    TextureProvider::load_textures(renderer);
    animation_provider = std::make_shared<AnimationProvider>();
    // cargar renderizables principales
    renderable_map =
        std::make_unique<RenderableMap>(map_data, animation_provider);
    hud_manager = std::make_unique<HUDManager>(animation_provider);
    field_of_view = std::make_unique<FieldOfView>(renderer, game_config);
}

void Render::update(const SnapshotDTO& snapshot, PrivatePlayerDTO& user_data,
        uint32_t& fps_timer) {
    
    // Medición de tiempo interno para diagnosticar
    static int update_counter = 0;
    static auto last_internal_report = std::chrono::high_resolution_clock::now();
    static double total_map_time = 0, total_players_time = 0, total_fov_time = 0, total_hud_time = 0;
    
    auto start_time = std::chrono::high_resolution_clock::now();
    
    // actualizar dropeables
    auto map_start = std::chrono::high_resolution_clock::now();
    renderable_map->update(snapshot);
    auto map_end = std::chrono::high_resolution_clock::now();
    
    // actualizar jugadores
    auto players_start = std::chrono::high_resolution_clock::now();
    int my_id = user_data.player_id;
    for (auto& jugador : snapshot.players) {
        // si es el jugador actual actualiza el offset de la camara
        if (jugador.player_id == my_id) {
            Camera::set_center(jugador.x, jugador.y);
            Camera::set_screen_size(renderer.GetOutputSize());
        }

        // iterar cada uno y buscarlo por ID
        auto it = players_renderables.find(jugador.player_id);
        if (it != players_renderables.end()) {
            // si existe, actualizarlo
            it->second->update(jugador);
        } else {
            // si no existe, crearlo (esto puede ser costoso)
            auto renderable_player = std::make_unique<RenderablePlayer>(
                jugador.player_id, animation_provider);
            players_renderables[jugador.player_id] =
                std::move(renderable_player);
        }
    }
    auto players_end = std::chrono::high_resolution_clock::now();

    // FOV update
    auto fov_start = std::chrono::high_resolution_clock::now();
    if(USE_FOV)
        field_of_view->update(renderer);
    auto fov_end = std::chrono::high_resolution_clock::now();

    // actualizar textos
    auto hud_start = std::chrono::high_resolution_clock::now();
    hud_manager->update(snapshot, user_data, fps_timer);
    auto hud_end = std::chrono::high_resolution_clock::now();
    
    // Acumular tiempos
    total_map_time += std::chrono::duration<double, std::micro>(map_end - map_start).count();
    total_players_time += std::chrono::duration<double, std::micro>(players_end - players_start).count();
    total_fov_time += std::chrono::duration<double, std::micro>(fov_end - fov_start).count();
    total_hud_time += std::chrono::duration<double, std::micro>(hud_end - hud_start).count();
    update_counter++;
    
    auto now = std::chrono::high_resolution_clock::now();
    // Reportar cada 3 segundos
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - last_internal_report).count() > 3000) {
        std::cout << "Render Update Breakdown (avg per call):" << std::endl;
        std::cout << "  Map: " << (total_map_time / update_counter) << "μs" << std::endl;
        std::cout << "  Players: " << (total_players_time / update_counter) << "μs" << std::endl;
        std::cout << "  FOV: " << (total_fov_time / update_counter) << "μs" << std::endl;
        std::cout << "  HUD: " << (total_hud_time / update_counter) << "μs" << std::endl;
        std::cout << "  Active players: " << players_renderables.size() << std::endl;
        
        // Reset
        total_map_time = total_players_time = total_fov_time = total_hud_time = 0;
        update_counter = 0;
        last_internal_report = now;
    }
}

void Render::skip_frames(uint8_t frames) {
    if (frames == 0) {
        return;
    }
    // se salta los frames que no se renderizan
    // std::cout << "LOG: Debe saltearse " << (int)frames << " frames."
    //           << std::endl;
    for (auto& [id, renderable_player] : players_renderables) {
        renderable_player->skip_frames(frames);
    }
}

void Render::render() {
    // Medición de tiempo interno para diagnosticar render
    static int render_counter = 0;
    static auto last_render_report = std::chrono::high_resolution_clock::now();
    static double total_clear_time = 0, total_map_render_time = 0, total_players_render_time = 0;
    static double total_fov_render_time = 0, total_hud_render_time = 0, total_present_time = 0;
    
    auto render_start = std::chrono::high_resolution_clock::now();
    
    // limpiar la ventana
    auto clear_start = std::chrono::high_resolution_clock::now();
    renderer.Clear();
    auto clear_end = std::chrono::high_resolution_clock::now();

    // renderizar mapa
    auto map_render_start = std::chrono::high_resolution_clock::now();
    renderable_map->render(renderer);
    auto map_render_end = std::chrono::high_resolution_clock::now();

    // iterar todos los jugadores
    auto players_render_start = std::chrono::high_resolution_clock::now();
    for (auto& [id, renderable_player] : players_renderables) {
        // renderizar cada jugador
        renderable_player->render(renderer);
    }
    auto players_render_end = std::chrono::high_resolution_clock::now();

    // FOV render
    auto fov_render_start = std::chrono::high_resolution_clock::now();
    if(USE_FOV)
        field_of_view->render(renderer);
    auto fov_render_end = std::chrono::high_resolution_clock::now();

    // mostrar textos en pantalla
    auto hud_render_start = std::chrono::high_resolution_clock::now();
    hud_manager->render(renderer);
    auto hud_render_end = std::chrono::high_resolution_clock::now();

    // mostrar la ventana
    auto present_start = std::chrono::high_resolution_clock::now();
    renderer.Present();
    auto present_end = std::chrono::high_resolution_clock::now();
    
    // Acumular tiempos
    total_clear_time += std::chrono::duration<double, std::micro>(clear_end - clear_start).count();
    total_map_render_time += std::chrono::duration<double, std::micro>(map_render_end - map_render_start).count();
    total_players_render_time += std::chrono::duration<double, std::micro>(players_render_end - players_render_start).count();
    total_fov_render_time += std::chrono::duration<double, std::micro>(fov_render_end - fov_render_start).count();
    total_hud_render_time += std::chrono::duration<double, std::micro>(hud_render_end - hud_render_start).count();
    total_present_time += std::chrono::duration<double, std::micro>(present_end - present_start).count();
    render_counter++;
    
    auto now = std::chrono::high_resolution_clock::now();
    // Reportar cada 3 segundos
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - last_render_report).count() > 3000) {
        std::cout << "Render Breakdown (avg per call):" << std::endl;
        std::cout << "  Clear: " << (total_clear_time / render_counter) << "μs" << std::endl;
        std::cout << "  Map Render: " << (total_map_render_time / render_counter) << "μs" << std::endl;
        std::cout << "  Players Render: " << (total_players_render_time / render_counter) << "μs" << std::endl;
        std::cout << "  FOV Render: " << (total_fov_render_time / render_counter) << "μs" << std::endl;
        std::cout << "  HUD Render: " << (total_hud_render_time / render_counter) << "μs" << std::endl;
        std::cout << "  Present: " << (total_present_time / render_counter) << "μs" << std::endl;
        double total_render_time = (total_clear_time + total_map_render_time + total_players_render_time + 
                                   total_fov_render_time + total_hud_render_time + total_present_time) / render_counter;
        std::cout << "  Total Render: " << total_render_time << "μs" << std::endl;
        std::cout << "  Render calls: " << render_counter << std::endl;
        
        // Reset
        total_clear_time = total_map_render_time = total_players_render_time = 0;
        total_fov_render_time = total_hud_render_time = total_present_time = 0;
        render_counter = 0;
        last_render_report = now;
    }
}

Render::~Render() {
    // Limpiar los renderables de jugadores
    players_renderables.clear();
}
