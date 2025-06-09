#include <iostream>

#include "client/client.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Bad call. Usage: " << argv[0] << ". No args expected"
                  << std::endl;
        return EXIT_FAILURE;
    }

    try {
        // TODO: Ejecutar el lobby de QT
        // TODO: Logica de lobby, de aca obtiene socker (puerto, ip), nombre
        // jugador, partida, etc. Socket socket = lobby->getSocket() int
        // player_id = lobby->getPlayerID()
        // ...
        std::string hostname = argv[1];
        std::string servname = argv[2];

        std::cout << "LOG: Connecting to server at " << hostname << ":"
                  << servname << std::endl;

        Client cliente(hostname, servname);
        cliente.run();

    } catch (const std::exception& e) {
        std::cerr << "Something went wrong: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Something went wrong" << std::endl;
        return EXIT_FAILURE;
    }
    return 0;
}
