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

void Client::run(int use_id) {
    sender.start();
    receiver.start();

    // TODO: En algun instante se debe obtener el ID del jugador
    // este es asignado por el servidor al iniciar la conexión
    int player_id = use_id;

    // TODO: Aqui inicia un juego, la logica de las fases inicial, durante y
    // final se encontrará en el GameLoop
    GameLoop gameloop(snapshots, commands, player_id);
    gameloop.run();

    commands.close();
    snapshots.close();

    con.destroy_socket();

    input_handler.stop();

    // Detener el sender y receiver
    sender.stop();
    receiver.stop();

    // Esperar a que terminen
    sender.join();
    receiver.join();
}
