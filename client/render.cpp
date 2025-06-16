#include "client/render.h"

#include <utility>

#include "client/animation_provider.h"
#include "client/texture_provider.h"
#include "client/camera.h"
#include "render.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

Render::Render(int user_player_id, const MapData& map_data):
        sdl(SDL_INIT_VIDEO),
        window("Counter Strike 2D", SDL_WINDOWPOS_UNDEFINED,
               SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN),
        renderer(window, -1, SDL_RENDERER_ACCELERATED),
        animation_provider(std::make_shared<AnimationProvider>()),
        user_player_id(user_player_id),
        renderable_map(map_data, animation_provider),
        font(DATA_PATH "/assets/gfx/fonts/sourcesans.ttf", 16) {
    // color de fondo negro
    renderer.SetDrawColor(0, 0, 0, 0);

    // cargar texturas
    TextureProvider::load_textures(renderer);
    animation_provider->load_animations();

    // carga info del mapa
    renderable_map.load_map_info();
}

void Render::update(Snapshot snapshot) {
    // TODO: actualizar dropeables

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
}


void Render::skip_frames(uint8_t frames) {
    if(frames == 0) {
        return;
    }
    // se salta los frames que no se renderizan
    std::cout << "LOG: Debe saltearse " << (int)frames << " frames." << std::endl;
    for (auto& [id, renderable_player] : players_renderables) {
        renderable_player->skip_frames(frames);
    }
}

void Render::render() {
    // limpiar la ventana
    renderer.Clear();

    // renderizar mapa
    renderable_map.render(renderer);

    // iterar todos los jugadores
    for (auto& [id, renderable_player] : players_renderables) {
        // renderizar cada jugador
        renderable_player->render(renderer);
    }

    // TODO: renderizar dropeables

    // texturas
    SDL2pp::Surface text_surface = font.RenderText_Blended("Hola Mundo", SDL_Color{255,255,255,255});
    SDL2pp::Texture text_texture(renderer, text_surface);

    SDL2pp::Point punto = renderer.GetOutputSize();
    int text_w = text_texture.GetWidth();
    int text_h = text_texture.GetHeight();
    SDL2pp::Rect dst((punto.x - text_w)/2, (punto.y - text_h)/2, text_w, text_h);
    renderer.Copy(text_texture, SDL2pp::NullOpt, dst);

    // mostrar la ventana
    renderer.Present();
}


Render::~Render() {
    // Limpiar los renderables de jugadores
    players_renderables.clear();
}