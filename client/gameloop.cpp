#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "gameloop.h"
#include <unistd.h>
#include "../common/player_commands/command.h"
#include "../common/player_commands/move.h"
#include "texture_provider.h"

#include "mock_server.h"

const static int RATE = 1000/60;


GameLoop::GameLoop(Queue<Snapshot>& snapshots, Queue<PlayerDTO>& comandos): 
    sdl(SDL_INIT_VIDEO),
    window("Counter Strike 2D",
                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                          640, 480,
                          SDL_WINDOW_SHOWN),
    renderer(window, -1, SDL_RENDERER_ACCELERATED),
    // texture_provider(renderer),
    snapshots_queue(snapshots),
    comandos_queue(comandos),
    input_handler(comandos)
    {
        // poner color de fondo negro
        renderer.SetDrawColor(0, 0, 0, 0);

        // cargar texturas
        TextureProvider::load_textures(renderer);
}


void GameLoop::run(){

    
    while (is_running) {
        // uint32_t t1 = SDL_GetTicks();
        _debug_simulacion_servidor(ultima_snapshot);
        
        is_running = input_handler.handle_events();
        
        // TODO: asegurarse de obtener el último evento (vaciar la queue entera?)
        snapshots_queue.try_pop(ultima_snapshot);
        
        if(!ultima_snapshot.players.empty()){   
            // imprimir posicion jugador obtenido del vector de jugadores
            PlayerDTO jugador = ultima_snapshot.players.at(0);
            std::cout << jugador.x << std::endl;
        }

        update_renderables_from_snapshot();
        // update(player, pointer, RATE);
        
        render_all();

       

        // sleep_or_catch_up(t1);
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
            auto renderable_player = std::make_unique<RenderablePlayer>(jugador.player_id);
            players_renderables[jugador.player_id] = std::move(renderable_player);
        }
    }
}


void GameLoop::render_all(){
    // renderer.SetDrawColor(0x80, 0x80, 0x80);

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


/**
 * Solo con fines de debug
 */
void GameLoop::_debug_simulacion_servidor(Snapshot& snapshot){
    // mock_server(snapshots_queue);

    // toma aquello que esté en la queue de comandos (o sea Command) 
    // y lo convierte en un snapshot para que pusheado en la otra cola

    PlayerDTO player;
    if(!comandos_queue.try_pop(player)){
        return;
    }
    std::cout << "popeo elemento player.x: " << player.x << std::endl;
    
    snapshot.players.push_back(player);

    if(!snapshots_queue.try_push(snapshot)){
        return;
    }

}


void GameLoop::closeWindow() {
    this->window.~Window(); 
    this->renderer.~Renderer();
    this->sdl.~SDL();
}






// void GameLoop::sleep_or_catch_up(uint32_t& t1) {
//     uint32_t t2 = SDL_GetTicks();

//     int rest = RATE - (t2 - t1);
//     if (rest < 0) {
//         int behind = -rest;
//         int lost = behind - behind % RATE;

//         // recuperamos los frames perdidos
//         uint8_t frames_to_skip = int(lost / RATE);

//         // TODO: skipear frames


//         t1 += lost;
//     } else {
//         SDL_Delay(rest);
//     }

//     t1 = SDL_GetTicks();
// }
