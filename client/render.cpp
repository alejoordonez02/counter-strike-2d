#include "client/render.h"
#include <unordered_set>


Render::Render(const MapData& map_data, const GameConfig& game_config):
    sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO), window(
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
    hud_manager = std::make_unique<HUDManager>(animation_provider, game_config);
    field_of_view = std::make_unique<FieldOfView>(renderer, game_config);

    // Inicializar sonidos
    sound_manager = std::make_unique<SoundManager>(game_config);
}

void Render::update(const SnapshotDTO& snapshot, PrivatePlayerDTO& user_data,
        uint32_t& fps_timer) {
    // actualizar dropeables
    renderable_map->update(snapshot);

    // actualizar jugadores
    update_players(snapshot, user_data);

    if(USE_FOV)
        field_of_view->update(renderer);

    // actualizar textos
    hud_manager->update(snapshot, user_data, fps_timer);
    
    // reproducir sonidos basados en cambios de estado
    sound_manager->check_and_play_game_sounds(snapshot, user_data);
}

void Render::update_players(const SnapshotDTO& snapshot, PrivatePlayerDTO& user_data) {
    // verificar jugadores eliminados
    // Crear set con IDs de jugadores activos en el snapshot
    std::unordered_set<int> active_players;
    for (const auto& jugador : snapshot.players) {
        active_players.insert(jugador.player_id);
    }
    // Eliminar jugadores que ya no existen en el snapshot
    auto it = players_renderables.begin();
    while (it != players_renderables.end()) {
        if (active_players.find(it->first) == active_players.end()) {
            std::cout << "LOG: Eliminando jugador con ID: " << it->first << std::endl;
            it = players_renderables.erase(it);
        } else {
            ++it;
        }
    }

    
    // update players
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
            std::cout << "LOG: Creando jugador con ID: " << jugador.player_id
                      << std::endl;
            // si no existe, crearlo
            auto renderable_player = std::make_unique<RenderablePlayer>(
                jugador.player_id, animation_provider);
            players_renderables[jugador.player_id] =
                std::move(renderable_player);
        }
    }
}



void Render::skip_frames(int frames) {
    if (frames == 0) {
        return;
    }
    // se salta los frames que no se renderizan
    std::cout << "LOG: Debe saltearse " << (int)frames << " frames."
              << std::endl;
    for (auto& [id, renderable_player] : players_renderables) {
        renderable_player->skip_frames(frames);
    }
}

void Render::render() {
    // limpiar la ventana
    renderer.Clear();

    // renderizar mapa
    renderable_map->render(renderer);

    // iterar todos los jugadores
    for (auto& [id, renderable_player] : players_renderables) {
        // renderizar cada jugador
        renderable_player->render(renderer);
    }

    if(USE_FOV)
    field_of_view->render(renderer);

    // mostrar textos en pantalla
    hud_manager->render(renderer);

    // mostrar la ventana
    renderer.Present();
}




Render::~Render() {
    // Limpiar los renderables de jugadores
    players_renderables.clear();
}
