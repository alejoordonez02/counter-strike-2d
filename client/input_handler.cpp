#include "input_handler.h"
#include "../common/direction.h"
#include "../common/network/dto.h"

#include <map>
#include <iostream>

InputHandler::InputHandler(Queue<std::unique_ptr<DTO>>& commands_queue): 
    commands(commands_queue) {
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

void InputHandler::update_player_values(Snapshot& snapshot) {
    // obtiene el id del jugador actual y reemplaza el puntero para actualizar los valores
    auto it = std::find_if(snapshot.players.begin(), snapshot.players.end(),
                           [this](const PlayerDTO& found_player) { return found_player.player_id == player.player_id; });
    if (it == snapshot.players.end())
        return;

    player = *it;
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

    if(dir.x != 0 || dir.y != 0){
        commands.try_push(std::make_unique<MoveDTO>(dir));
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


