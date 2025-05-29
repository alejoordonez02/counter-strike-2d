#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL2/SDL.h>
#include "../common/queue.h"
#include "../common/player_commands/command.h"

class InputHandler {
private:
    Queue<Command>& comandos;


public:
    InputHandler(Queue<Command>& comandos_queue);

    void handle_key_down(const SDL_Event& event);
    void handle_key_up(const SDL_Event& event);

    void send_direction();

    void process_movement();

    bool handle_events();
};

#endif
