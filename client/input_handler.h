#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL2/SDL.h>
#include "../common/queue.h"
#include "../server/player_commands/command.h"
#include "../common/snapshot.h"

class InputHandler:  {
private:
    Queue<std::shared_ptr<DTO>>& commands_queue;
    std::unique_ptr<DTO> player;

public:
    InputHandler(Queue<std::shared_ptr<DTO>>& commands_queue);

    void handle_key_down(const SDL_Event& event);
    void handle_key_up(const SDL_Event& event);

    void update_player_values(Snapshot& snapshot);

    void send_direction();

    double calculate_facing_angle(int16_t x, int16_t y);

    void process_movement();

    bool handle_events();
};

#endif
