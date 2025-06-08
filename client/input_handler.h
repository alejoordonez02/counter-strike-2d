#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL2/SDL_events.h>
#include "../common/queue.h"
#include "../common/network/dto.h"
#include "../common/snapshot.h"

class InputHandler {
private:
    Queue<std::shared_ptr<DTO>>& commands_queue;

public:
    InputHandler(Queue<std::shared_ptr<DTO>>& commands_queue);

    void handle_key_down(const SDL_Event& event);
    void handle_key_up(const SDL_Event& event);

    void send_direction();

    double calculate_facing_angle(int16_t x, int16_t y);

    void process_movement();

    bool handle_events();
};

#endif
