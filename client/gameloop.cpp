#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "gameloop.h"
#include <unistd.h>
#include "../server/player_commands/command.h"

#define FRAME_RATE 1000000.0f/25.0f

GameLoop::GameLoop(Queue<DTO>& snapshots, Queue<DTO>& comands): 
    snapshots_queue(snapshots),
    comands_queue(comands),
    input_handler(comands),
    render()
{}


void GameLoop::run(){
    while (is_running) {
        // se asegura que la cola tenga el ultimo estado
        while(snapshots_queue.try_pop(ultima_snapshot)){}
        
        input_handler.update_player_values(ultima_snapshot);
        is_running = input_handler.handle_events();

        render.update(ultima_snapshot);
        
        render.render_all();

        usleep(FRAME_RATE);
        
    }
}

