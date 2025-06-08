#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "gameloop.h"
#include <unistd.h>
#include "texture_provider.h"
#include "animation_provider.h"
#include "../server/player_commands/command.h"


#define FRAME_RATE 1000000.0f/25.0f


GameLoop::GameLoop(Queue<DTO>& snapshots, Queue<DTO>& comands): 
    sdl(SDL_INIT_VIDEO),
    window("Counter Strike 2D",
                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                          640, 480,
                          SDL_WINDOW_SHOWN),
    renderer(window, -1, SDL_RENDERER_ACCELERATED),
    // texture_provider(renderer),
    snapshots_queue(snapshots),
    comands_queue(comands),
    input_handler(comands),
    animation_provider(std::make_shared<AnimationProvider>())
    {
        // poner color de fondo negro
        renderer.SetDrawColor(0, 255, 0, 0);

        // cargar texturas
        TextureProvider::load_textures(renderer);
        animation_provider->load_animations();

}


void GameLoop::run(){
    while (is_running) {
        // se asegura que la cola tenga el ultimo estado
        while(snapshots_queue.try_pop(ultima_snapshot)){}
        
        input_handler.update_player_values(ultima_snapshot);
        is_running = input_handler.handle_events();

        update_renderables_from_snapshot();
        
        render_all();

        usleep(FRAME_RATE);
        
    }
}

void GameLoop::update_renderables_from_snapshot(){
    // actualizar colisionables, jugadores, etc.

    // iterar jugadores y graficarlos
    for (auto& jugador: ultima_snapshot.players) {
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
}


void GameLoop::render_all(){
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


void GameLoop::closeWindow() {
    this->window.~Window(); 
    this->renderer.~Renderer();
    this->sdl.~SDL();
}
