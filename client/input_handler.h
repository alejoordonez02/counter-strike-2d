#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL2/SDL.h>
#include "../common/queue.h"
#include "../server/player_commands/command.h"
#include "../common/snapshot.h"

class InputHandler {
private:
    Queue<PlayerDTO>& comandos;


public:
    InputHandler(Queue<PlayerDTO>& comandos_queue);

    void handle_key_down(const SDL_Event& event);
    void handle_key_up(const SDL_Event& event);

    void send_direction();

    void process_movement();

    bool handle_events();
};

#endif
