#ifndef CLIENT_INPUT_HANDLER_H
#define CLIENT_INPUT_HANDLER_H

#include <SDL2/SDL_events.h>

#include <memory>

#include "client/camera.h"
#include "common/direction.h"
#include "common/network/dto.h"
#include "common/network/dtos/aim_dto.h"
#include "common/network/dtos/buy_ammo_dto.h"
#include "common/network/dtos/buy_weapon_dto.h"
#include "common/network/dtos/start_attacking_dto.h"
#include "common/network/dtos/start_moving_dto.h"
#include "common/network/dtos/start_planting_dto.h"
#include "common/network/dtos/start_reloading_dto.h"
#include "common/network/dtos/stop_action_dto.h"
#include "common/network/dtos/stop_moving_dto.h"
#include "common/network/dtos/use_weapon_dto.h"
#include "common/queue.h"
#include "common/thread.h"
#include "common/weapons.h"

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
    void send_plant_bomb();
    void send_defuse_bomb();
    void send_reload();
    void send_aim();
    void send_buy_weapon();
    void send_buy_ammo();
    void send_drops();

public:
    explicit InputHandler(Queue<std::shared_ptr<DTO>>& commands_queue);

    bool alive_status();

    void run() override;

    ~InputHandler() = default;
};

#endif
