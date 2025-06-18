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
    static bool was_moving = false;
    Direction dir(0, 0);

    /*
     * wasd pls jsajjasjaj
     * */
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
        commands_queue.try_push(std::make_unique<StartMovingDTO>(dir));
        was_moving = true;
    } else if (was_moving) {
        commands_queue.try_push(std::make_unique<StopMovingDTO>());
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

void InputHandler::send_aim() {
    static int last_dx = INT32_MAX, last_dy = INT32_MAX;
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    SDL_Window* win = SDL_GetMouseFocus();
    int w = 0, h = 0;
    if (win) SDL_GetWindowSize(win, &w, &h);

    int dx = mx - w / 2;
    int dy = my - h / 2;
    /*
     * checkear q no se vaya a volver a mandar la misma dir, quizás innecesario
     * siendo que hay cooldown...
     * */
    if (dx != last_dx || dy != last_dy) {
        commands_queue.try_push(std::make_unique<AimDTO>(Direction(dx, dy)));
        last_dx = dx;
        last_dy = dy;
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
