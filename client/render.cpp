#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "texture_provider.h"
#include "animation_provider.h"
#include "render.h"
#include "../server/player_commands/command.h"


Render::Render(): 
    sdl(SDL_INIT_VIDEO),
    window("Counter Strike 2D",
                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                          640, 480,
                          SDL_WINDOW_SHOWN),
    renderer(window, -1, SDL_RENDERER_ACCELERATED),
    animation_provider(std::make_shared<AnimationProvider>())
    {
        // poner color de fondo negro
        renderer.SetDrawColor(0, 255, 0, 0);

        // cargar texturas
        TextureProvider::load_textures(renderer);
        animation_provider->load_animations();

}


void Render::update(Snapshot snapshot){
    // actualizar jugadores
    for (auto& jugador: snapshot.players) {
        // iterar cada uno y buscarlo por ID
        auto it = players_renderables.find(jugador.player_id);
        if (it != players_renderables.end()) {            
            // si existe, actualizarlo
            it->second->update(jugador);
        } else {
            std::cout << "LOG: Creando jugador con ID: " << (int)jugador.player_id << std::endl;
            // si no existe, crearlo
            auto renderable_player = std::make_unique<RenderablePlayer>(jugador.player_id, animation_provider);
            players_renderables[jugador.player_id] = std::move(renderable_player);
        }
    }

    // TODO: actualizar dropeables

    // TODO: actualizar mapa
}


void Render::render_all(){
    // limpiar la ventana
    renderer.Clear();

    // iterar todos los jugadores
    for (auto& [id, renderable_player]: players_renderables) {
        // renderizar cada jugador
        renderable_player->render(renderer);
    }

    // mostrar la ventana
    renderer.Present();
}


void Render::closeWindow() {
    this->window.~Window(); 
    this->renderer.~Renderer();
    this->sdl.~SDL();
}
