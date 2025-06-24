#include "client/input_handler.h"

#include <chrono>
#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "client/camera.h"
#include "common/direction.h"
#include "common/network/dto.h"
#include "common/network/dtos/aim_dto.h"
#include "common/network/dtos/change_weapon_dto.h"
#include "common/network/dtos/start_attacking_dto.h"
#include "common/network/dtos/start_moving_dto.h"
#include "common/network/dtos/start_planting_dto.h"
#include "common/network/dtos/stop_action_dto.h"
#include "common/network/dtos/stop_moving_dto.h"
#include "start_reloading_dto.h"

InputHandler::InputHandler(Queue<std::shared_ptr<DTO>>& commands_queue):
    commands_queue(commands_queue) {}

/**
 * @brief Mapa para almacenar el estado de las teclas.
 * La clave es el código de la tecla (SDL_Keycode) y el valor es un booleano
 * que indica si la tecla está presionada (true) o no (false)
 */
std::map<SDL_Keycode, bool> key_states;
std::map<std::string, bool> mouse_states;

void InputHandler::handle_key_down(const SDL_Event& event) {
    SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;
    key_states[keyEvent.keysym.sym] = true;
}

void InputHandler::handle_key_up(const SDL_Event& event) {
    SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;
    key_states[keyEvent.keysym.sym] = false;
}

void InputHandler::handle_mouse_down(const SDL_Event& event) {
    if (event.button.button == SDL_BUTTON_LEFT) {
        mouse_states["mouse_left"] = true;
    } else if (event.button.button == SDL_BUTTON_RIGHT) {
        mouse_states["mouse_right"] = true;
    }
}

void InputHandler::handle_mouse_up(const SDL_Event& event) {
    if (event.button.button == SDL_BUTTON_LEFT) {
        mouse_states["mouse_left"] = false;
    } else if (event.button.button == SDL_BUTTON_RIGHT) {
        mouse_states["mouse_right"] = false;
    }
}

// void InputHandler::handle_mouse_wheel(const SDL_Event& event) {
//     // Sensibilidad mínima para el scroll de arma
//     const int kWeaponScrollThreshold = 1;
//     static int weapon_scroll_accum = 0;

//     // Acumula el desplazamiento de la rueda
//     weapon_scroll_accum += event.wheel.y;
//     if (std::abs(weapon_scroll_accum) >= kWeaponScrollThreshold) {
//         // determina el tipo de arma a cambiar (ejemplo: 1="next" o
//         -1="prev") int weapon_type = weapon_scroll_accum > 0 ? 1 : -1;
//         std::cout << "LOG: Cambiando arma a: " << weapon_type << std::endl;
//         commands_queue.try_push(std::make_shared<ChangeWeaponDTO>(weapon_type));
//         weapon_scroll_accum = 0;
//     }
// }

// en base a que teclas presiones envía un comando de movimiento
// permite tambien movimientos en diagonal y el de quedarse quieto
void InputHandler::send_direction() {
    static bool was_moving = false;
    Direction dir(0, 0);

    if (key_states[SDLK_w]) {
        dir.y -= 1;
    }
    if (key_states[SDLK_s]) {
        dir.y += 1;
    }
    if (key_states[SDLK_a]) {
        dir.x -= 1;
    }
    if (key_states[SDLK_d]) {
        dir.x += 1;
    }

    if (dir.x != 0 || dir.y != 0) {
        commands_queue.try_push(std::make_shared<StartMovingDTO>(dir));
        was_moving = true;
    } else if (was_moving) {
        commands_queue.try_push(std::make_shared<StopMovingDTO>());
        was_moving = false;
    }
}

void InputHandler::send_attack() {
    // con static hacemos que se mantenga su valor entre llamadas
    // tambien se podria poner como miembro de la clase
    static bool prev_left = false;
    bool is_attacking = mouse_states["mouse_left"];

    // detecta el inicio del ataque (sostener click)
    if (is_attacking && !prev_left) {
        std::cout << "LOG: Enviando comando de ataque." << std::endl;
        // enviarlo solo una vez, no todo el tiempo
        commands_queue.try_push(std::make_shared<StartAttackingDTO>());
    }
    // Detecta el fin del ataque (soltar click)
    if (!is_attacking && prev_left) {
        std::cout << "LOG: Enviando comando de fin de ataque." << std::endl;
        commands_queue.try_push(std::make_shared<StopActionDTO>());
    }

    if (mouse_states["mouse_left"]) {
        // Sonido de disparo ?
    } else if (mouse_states["mouse_right"]) {
        std::cout << "LOG: Click izquierdo sostenido" << std::endl;
    }
    // actualiza el estado del click izquierdo
    prev_left = is_attacking;
}

void InputHandler::send_change_weapon() {
    // verifica si se apretó la tecla para cambiar entre arma primaria
    // secundaria, cuchillo o bomba
    if (key_states[SDLK_b]) {
        std::cout << "LOG: Enviando comando de cambio a arma bomba."
                  << std::endl;
        commands_queue.try_push(
            std::make_shared<ChangeWeaponDTO>(EquipmentType::Bomb));
    } else if (key_states[SDLK_k]) {
        std::cout << "LOG: Enviando comando de cambio a arma cuchillo."
                  << std::endl;
        commands_queue.try_push(
            std::make_shared<ChangeWeaponDTO>(EquipmentType::Knife));
    } else if (key_states[SDLK_1]) {
        std::cout << "LOG: Enviando comando de cambio a arma primaria."
                  << std::endl;
        commands_queue.try_push(
            std::make_shared<ChangeWeaponDTO>(EquipmentType::Primary));
    } else if (key_states[SDLK_2]) {
        std::cout << "LOG: Enviando comando de cambio a arma secundaria."
                  << std::endl;
        commands_queue.try_push(
            std::make_shared<ChangeWeaponDTO>(EquipmentType::Secondary));
    }
}

void InputHandler::send_aim() {
    // sensibilidad mínima para el aim
    const int kAimThreshold = 90;
    static int aim_accum_x = 0, aim_accum_y = 0;

    static int last_dx = INT32_MAX, last_dy = INT32_MAX;
    SDL2pp::Point mouse_pos;
    SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
    Camera::revert_center_point(mouse_pos);

    int dx = mouse_pos.x;
    int dy = mouse_pos.y;

    aim_accum_x += std::abs(dx - last_dx);
    aim_accum_y += std::abs(dy - last_dy);

    if (aim_accum_x >= kAimThreshold || aim_accum_y >= kAimThreshold) {
        // std::cout << "LOG: Enviando comando de apuntar a: (" << dx << ", " <<
        // dy << ")" << std::endl;
        commands_queue.try_push(std::make_shared<AimDTO>(Direction(dx, dy)));
        last_dx = dx;
        last_dy = dy;
        aim_accum_x = 0;
        aim_accum_y = 0;
    }
}

void InputHandler::send_plant_bomb() {
    static bool prev = false;
    bool is_planting = key_states[SDLK_e];

    if (is_planting && !prev)
        commands_queue.try_push(std::make_shared<StartPlantingDTO>());

    if (!is_planting && prev)
        commands_queue.try_push(std::make_shared<StopActionDTO>());

    prev = is_planting;
}

void InputHandler::send_reload() {
    static bool prev = false;
    bool is_reloading = key_states[SDLK_r];

    if (is_reloading && !prev)
        commands_queue.try_push(std::make_shared<StartReloadingDTO>());

    if (!is_reloading && prev)
        commands_queue.try_push(std::make_shared<StopActionDTO>());

    prev = is_reloading;
}

// Nueva función para procesar el movimiento:
void InputHandler::process_movement() {
    send_direction();
    send_attack();
    send_change_weapon();
    send_aim();
    send_plant_bomb();
    send_reload();
    // send_states();
}

bool InputHandler::handle_events() {
    SDL_Event event;
    /*
     * bloquear hasta q haya un evento
     * */
    SDL_WaitEvent(&event);

    /*
     * se desbloquea y hace lo mismo de antes
     * */
    do {
        switch (event.type) {
            case SDL_KEYDOWN:
                handle_key_down(event);
                break;
            case SDL_KEYUP:
                handle_key_up(event);
                break;
            case SDL_MOUSEBUTTONDOWN:
                handle_mouse_down(event);
                break;
            case SDL_MOUSEBUTTONUP:
                handle_mouse_up(event);
                break;
            case SDL_MOUSEWHEEL:
                // handle_mouse_wheel(event);
                break;
            case SDL_QUIT:
                std::cout << "LOG: Saliendo del input handler..." << std::endl;
                return false;
            default:
                break;
        }
    } while (SDL_PollEvent(&event));

    process_movement();
    return true;
}

void InputHandler::run() {
    // se utiliza un timer para evitar que el input sea demasiado sensible
    using clock = std::chrono::steady_clock;
    auto last_sent = clock::now();
    const int cooldown_ms = 20;  // ajustar sensibilidad

    while (is_alive) {
        auto now = clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now -
                                                                  last_sent)
                .count() > cooldown_ms) {
            is_alive = handle_events();
            last_sent = now;
        }
    }
    std::cout << "LOG: InputHandler ha terminado." << std::endl;
}

bool InputHandler::alive_status() { return is_alive; }
