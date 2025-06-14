#include "client/input_handler.h"

#include <chrono>
#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "common/direction.h"
#include "common/network/dto.h"
#include "common/network/dtos/aim_dto.h"
#include "common/network/dtos/start_attacking_dto.h"
#include "common/network/dtos/start_moving_dto.h"
#include "common/network/dtos/stop_attacking_dto.h"
#include "common/network/dtos/stop_moving_dto.h"

#include "input_handler.h"

InputHandler::InputHandler(Queue<std::unique_ptr<DTO>>& commands_queue):
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

// en base a que teclas presiones envía un comando de movimiento
// permite tambien movimientos en diagonal y el de quedarse quieto
void InputHandler::send_direction() {
    // recuerda si antes se estaba moviendo
    static bool was_moving = false;

    Direction dir(0, 0);

    if (key_states[SDLK_UP] || key_states[SDLK_w]) {
        dir.y -= 1;
    }
    if (key_states[SDLK_DOWN] || key_states[SDLK_s]) {
        dir.y += 1;
    }
    if (key_states[SDLK_LEFT] || key_states[SDLK_a]) {
        dir.x -= 1;
    }
    if (key_states[SDLK_RIGHT] || key_states[SDLK_d]) {
        dir.x += 1;
    }

    // envía solo si hay un movimiento
    if (dir.x != 0 || dir.y != 0) {
        // std::cout << "LOG: Enviando comando de movimiento." << std::endl;
        commands_queue.try_push(std::make_unique<StartMovingDTO>(dir));
        was_moving = true;
    } else {
        if (was_moving) {
            // std::cout << "LOG: Enviando comando de fin de movimiento."
            //           << std::endl;
            commands_queue.try_push(std::make_unique<StopMovingDTO>(dir));
            was_moving = false;
        }
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
        commands_queue.try_push(std::make_unique<StartAttackingDTO>());
    }
    // Detecta el fin del ataque (soltar click)
    if (!is_attacking && prev_left) {
        std::cout << "LOG: Enviando comando de fin de ataque." << std::endl;
        commands_queue.try_push(std::make_unique<StopAttackingDTO>());
    }

    if (mouse_states["mouse_left"]) {
        // Sonido de disparo ?
    } else if (mouse_states["mouse_right"]) {
        std::cout << "LOG: Click izquierdo sostenido" << std::endl;
    }
    // actualiza el estado del click izquierdo
    prev_left = is_attacking;
}

// envia las coordenadas del mouse como comando de aim
void InputHandler::send_aim() {
    // NOTE: Se le puede poner un cooldown para no enviar demasiados comandos
    static int last_mouse_x = -1;
    static int last_mouse_y = -1;

    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    if (mouse_x != last_mouse_x || mouse_y != last_mouse_y) {
        // std::cout << "LOG: Enviando comando de aim a (" << mouse_x << ", " <<
        // mouse_y << ")" << std::endl;
        // commands_queue.try_push(std::make_shared<AimDTO>(Direction(mouse_x,
        // mouse_y, false)));
        last_mouse_x = mouse_x;
        last_mouse_y = mouse_y;
    }
}

// Nueva función para procesar el movimiento:
void InputHandler::process_movement() {
    send_direction();
    send_attack();
    send_aim();
    // send_states();
}

bool InputHandler::handle_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            // mantener presionada una tecla
            case SDL_KEYDOWN:
                handle_key_down(event);
                break;
            // soltar una tecla
            case SDL_KEYUP:
                handle_key_up(event);
                break;
            // click del mouse
            case SDL_MOUSEBUTTONDOWN:
                handle_mouse_down(event);
                break;
            // soltar click del mouse
            case SDL_MOUSEBUTTONUP:
                handle_mouse_up(event);
                break;
            case SDL_QUIT:
                std::cout << "LOG: Saliendo del input handler..." << std::endl;
                return false;
        }
    }
    process_movement();
    return true;
}

void InputHandler::run() {
    // se utiliza un timer para evitar que el input sea demasiado sensible
    using clock = std::chrono::steady_clock;
    auto last_sent = clock::now();
    const int cooldown_ms = 50;  // ajustar sensibilidad

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
