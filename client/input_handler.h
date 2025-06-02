#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL2/SDL.h>
#include "../common/queue.h"
#include "../common/player_commands/command.h"
#include "../common/snapshot.h"

class InputHandler {
private:
    Queue<PlayerDTO>& comandos;
    PlayerDTO player;


public:
    InputHandler(Queue<PlayerDTO>& comandos_queue);

    void handle_key_down(const SDL_Event& event);
    void handle_key_up(const SDL_Event& event);

    void update_player_values(Snapshot& snapshot);

    void send_direction();

    double calculate_facing_angle(int16_t x, int16_t y);

    void process_movement();

    bool handle_events();
};

#endif
