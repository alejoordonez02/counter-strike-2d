#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL2/SDL_events.h>
#include "../common/queue.h"
#include "../common/network/dto.h"
#include "../common/snapshot.h"
#include "../common/thread.h"

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

    void send_attack();


public:
    InputHandler(Queue<std::shared_ptr<DTO>>& commands_queue);
    
    bool alive_status();

    void run() override;

    ~InputHandler() = default;
};

#endif
