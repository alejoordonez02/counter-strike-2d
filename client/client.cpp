#include "client/client.h"

#include <filesystem>
#include <string>

#include <bits/fs_fwd.h>

#include "client/gameloop.h"
#include "common/maploader.h"

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
    // TODO: El mapa se debe poner descargar del server supuestamente
    // std::cout << "LOG: Current working directory: " <<
    // std::filesystem::current_path() << std::endl;
    MapLoader map_loader;
    MapData map_to_use =
            map_loader.loadMapData("tests/client/prueba_mapa_mod.yaml");

    // TODO: Aqui inicia un juego, la logica de las fases inicial, durante y
    // final se encontrará en el GameLoop
    GameLoop gameloop(snapshots, commands, player_id, map_to_use);
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
