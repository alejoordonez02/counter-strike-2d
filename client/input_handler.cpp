#include "input_handler.h"
#include "../common/direction.h"
#include "../common/player_commands/move.h"
#include "../common/player_commands/command.h"

#include <map>
#include <iostream>

InputHandler::InputHandler(Queue<Command>& comandos_queue): 
    comandos(comandos_queue) {
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

    comandos.push(Move(dir));
}


// Nueva función para procesar el movimiento:
void InputHandler::process_movement() {
    send_direction();
    // send_attack();
    // send_states();       
}

// Llama a process_movement en handle_events:
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
                    std::cout << "Botón izquierdo del ratón presionado." << std::endl;
                } else if (event.button.button == SDL_BUTTON_RIGHT) {
                    std::cout << "Botón derecho del ratón presionado." << std::endl;
                }
                break;
            case SDL_QUIT:
                std::cout << "Cerrando ventana..." << std::endl;
                return false;
        }
    }
    process_movement();
    return true;
}


