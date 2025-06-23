#ifndef CLIENT_INPUT_HANDLER_H
#define CLIENT_INPUT_HANDLER_H

#include <memory>

#include <SDL2/SDL_events.h>

#include "common/network/dto.h"
#include "common/queue.h"
#include "common/thread.h"

class InputHandler: public Thread {
private:
    Queue<std::shared_ptr<DTO>>& commands_queue;
    std::atomic<bool> is_alive = true;

    void handle_key_down(const SDL_Event& event);
    void handle_key_up(const SDL_Event& event);

    void handle_mouse_down(const SDL_Event& event);
    void handle_mouse_up(const SDL_Event& event);

    bool handle_events();

    void process_movement();
    void send_direction();
    void send_change_weapon();
    void send_attack();

    void send_aim();

public:
    explicit InputHandler(Queue<std::shared_ptr<DTO>>& commands_queue);

    bool alive_status();

    void run() override;

    ~InputHandler() = default;
};

#endif
