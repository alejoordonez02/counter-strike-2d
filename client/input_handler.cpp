#include "input_handler.h"

InputHandler::InputHandler(Queue<Command>& comandos_queue): 
    comandos(comandos_queue) {
}


void InputHandler::handle_move_up(){
    Command* command = new MoveUpCommand();
    comandos.push(command);
    std::cout << "Move Up" << std::endl;
}


void InputHandler::handle_key_up(const SDL_Event& event){
    SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
    switch (keyEvent.keysym.sym) {
        case SDLK_LEFT:
            player.stopMoving();
            break;
        case SDLK_RIGHT:
            player.stopMoving();
            break;
        case SDLK_UP:
            player.stopMoving();
            break;
        case SDLK_DOWN:
            player.stopMoving();
            break;
        } 
}



void InputHandler::handle_key_down(const SDL_Event& event){
    SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
    switch (keyEvent.keysym.sym) {
        case SDLK_LEFT:
            player.moveLeft();
            break;
        case SDLK_RIGHT:
            player.moveRigth();
            break;
        case SDLK_UP:
            player.moveUp();
            break;
        case SDLK_DOWN:
            player.moveDown();
            break;
        }
} 


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
    
    return true;
}
