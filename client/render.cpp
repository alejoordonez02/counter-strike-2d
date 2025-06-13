#include "client/render.h"

#include <utility>

#include "client/animation_provider.h"
#include "client/texture_provider.h"
#include "client/camera.h"
#include "render.h"

Render::Render(int user_player_id):
        sdl(SDL_INIT_VIDEO),
        window("Counter Strike 2D", SDL_WINDOWPOS_UNDEFINED,
               SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN),
        renderer(window, -1, SDL_RENDERER_ACCELERATED),
        animation_provider(std::make_shared<AnimationProvider>()),
        user_player_id(user_player_id) {
    // poner color de fondo rosa
    renderer.SetDrawColor(0, 255, 0, 0);

    // cargar texturas
    TextureProvider::load_textures(renderer);
    animation_provider->load_animations();
}

void Render::update(Snapshot snapshot) {
    // actualizar jugadores
    for (auto& jugador : snapshot.players) {
        // si es el jugador actual actualiza el offset de la camara
        if (jugador.player_id == user_player_id) {
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

    // TODO: actualizar dropeables

    // TODO: actualizar mapa
}


void Render::skip_frames(uint8_t frames) {
    // se salta los frames que no se renderizan
    std::cout << "LOG: Debe saltearse " << (int)frames << " frames." << std::endl;
    for (uint8_t i = 0; i < frames; ++i) {
        renderer.Clear();
        renderer.Present();
    }
}

void Render::render() {
    // limpiar la ventana
    renderer.Clear();

    // iterar todos los jugadores
    for (auto& [id, renderable_player] : players_renderables) {
        // renderizar cada jugador
        renderable_player->render(renderer);
    }

    // TODO: renderizar dropeables

    // TODO: renderizar mapa

    // mostrar la ventana
    renderer.Present();
}


Render::~Render() {
    // Limpiar los renderables de jugadores
    players_renderables.clear();
}