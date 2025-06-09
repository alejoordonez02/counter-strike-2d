#include "client/client.h"

#include <string>

#include "client/gameloop.h"

Client::Client(const std::string& hostname, const std::string& servname):
        con(hostname, servname),
        commands(),
        snapshots(),
        sender(con, commands),
        receiver(con, snapshots),
        input_handler(commands) {}

void Client::run() {
    sender.start();
    receiver.start();

    // TODO: Aqui inicia un juego, la logica de las fases inicial, durante y
    // final se encontrará en el GameLoop
    GameLoop gameloop(snapshots, commands);
    gameloop.run();
}
