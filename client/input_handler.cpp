#include "input_handler.h"
#include "../common/direction.h"
#include "../common/network/dto.h"
#include "../common/network/dtos/start_moving_dto.h"

#include <map>
#include <iostream>

InputHandler::InputHandler(Queue<std::shared_ptr<DTO>>& commands_queue): 
    commands_queue(commands_queue){
    }

/**
 * @brief Mapa para almacenar el estado de las teclas.
 * La clave es el código de la tecla (SDL_Keycode) y el valor es un booleano
 * que indica si la tecla está presionada (true) o no (false)
 */
std::map<SDL_Keycode, bool> key_states;

void InputHandler::handle_key_down(const SDL_Event& event) {
    SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
    key_states[keyEvent.keysym.sym] = true;
}

void InputHandler::handle_key_up(const SDL_Event& event) {
    SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
    key_states[keyEvent.keysym.sym] = false;
}

// en base a que teclas presiones envía un comando de movimiento
// permite tambien movimientos en diagonal y el de quedarse quieto
void InputHandler::send_direction(){
    Direction dir(0, 0);

    if (key_states[SDLK_UP]) {
        dir.y -= 1;
    }
    if (key_states[SDLK_DOWN]) {
        dir.y += 1;
    }
    if (key_states[SDLK_LEFT]) {
        dir.x -= 1;
    }
    if (key_states[SDLK_RIGHT]) {
        dir.x += 1;
    }

    // envía solo si hay un movimiento
    if(dir.x != 0 || dir.y != 0){
        std::cout << "LOG: Enviando dirección: (" << dir.x << ", " << dir.y << ")" << std::endl;
        commands_queue.try_push(std::make_shared<StartMovingDTO>(dir));
    }
}


// Nueva función para procesar el movimiento:
void InputHandler::process_movement() {
    send_direction();
    // send_attack();
    // send_states();       
}

bool InputHandler::handle_events() {
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type) {
            case SDL_KEYDOWN:
                handle_key_down(event);
                break;
            case SDL_KEYUP:
                handle_key_up(event);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    std::cout << "LOG: Botón izquierdo del ratón presionado." << std::endl;
                } else if (event.button.button == SDL_BUTTON_RIGHT) {
                    std::cout << "LOG: Botón derecho del ratón presionado." << std::endl;
                }
                break;
            case SDL_QUIT:
                std::cout << "LOG: Cerrando ventana..." << std::endl;
                return false;
        }
    }
    process_movement();
    return true;
}


void InputHandler::run(){
    while (is_alive) {
        is_alive = handle_events();
    }
    std::cout << "LOG: InputHandler ha terminado." << std::endl;
}

bool InputHandler::alive_status(){
    return is_alive;
}

