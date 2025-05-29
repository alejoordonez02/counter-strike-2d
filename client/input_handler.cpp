#include "input_handler.h"
#include <map>

InputHandler::InputHandler(Queue<Command>& comandos_queue): 
    comandos(comandos_queue) {
}


// Agrega esto en la clase InputHandler (en el header y aquí):
std::map<SDL_Keycode, bool> key_states;

// Modifica handle_key_down y handle_key_up:
void InputHandler::handle_key_down(const SDL_Event& event) {
    SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
    key_states[keyEvent.keysym.sym] = true;
}

void InputHandler::handle_key_up(const SDL_Event& event) {
    SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
    key_states[keyEvent.keysym.sym] = false;
}

// Nueva función para procesar el movimiento:
void InputHandler::process_movement(Jugador& player) {
    bool up = key_states[SDLK_UP];
    bool down = key_states[SDLK_DOWN];
    bool left = key_states[SDLK_LEFT];
    bool right = key_states[SDLK_RIGHT];

    if (up && right) player.moveUpRight();
    else if (up && left) player.moveUpLeft();
    else if (down && right) player.moveDownRight();
    else if (down && left) player.moveDownLeft();
    else if (up) player.moveUp();
    else if (down) player.moveDown();
    else if (left) player.moveLeft();
    else if (right) player.moveRigth();
    else player.stopMoving();
}

// Llama a process_movement en handle_events:
bool InputHandler::handle_events(Jugador &player) {
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
    process_movement(player);
    return true;
}


// bool InputHandler::handle_events(Jugador &player) {
//     SDL_Event event;
//     while(SDL_PollEvent(&event)){
//         switch(event.type) {
//             case SDL_KEYDOWN:
//                 handle_key_down(event);
//                 break;
//             case SDL_KEYUP:
//                 handle_key_up(event);
//                 break;
//             
//         }
//     }
    
//     return true;
// }

// void InputHandler::handle_move_up(){
//     Command* command = new MoveUpCommand();
//     comandos.push(command);
//     std::cout << "Move Up" << std::endl;
// }


// void InputHandler::handle_key_up(const SDL_Event& event){
//     SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
//     switch (keyEvent.keysym.sym) {
//         case SDLK_LEFT:
//             player.stopMoving();
//             break;
//         case SDLK_RIGHT:
//             player.stopMoving();
//             break;
//         case SDLK_UP:
//             player.stopMoving();
//             break;
//         case SDLK_DOWN:
//             player.stopMoving();
//             break;
//         } 
// }



// void InputHandler::handle_key_down(const SDL_Event& event){
//     SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
//     switch (keyEvent.keysym.sym) {
//         case SDLK_LEFT:
//             player.moveLeft();
//             break;
//         case SDLK_RIGHT:
//             player.moveRigth();
//             break;
//         case SDLK_UP:
//             player.moveUp();
//             break;
//         case SDLK_DOWN:
//             player.moveDown();
//             break;
//         }
// } 


