#include "client/client.h"

#include <bits/fs_fwd.h>

#include <filesystem>
#include <iostream>
#include <string>

#include "client/gameloop.h"
#include "common/map_name.h"
#include "common/maploader.h"
#include "common/network/dtos/create_game_dto.h"
#include "common/network/dtos/join_game_dto.h"
#include "common/network/dtos/list_games_dto.h"

Client::Client(const std::string& hostname, const std::string& servname):
    con(hostname, servname), commands(), snapshots(), sender(con, commands),
    receiver(con, snapshots), input_handler(commands) {}

void Client::lobby_phase() {
    using namespace DTOSerial::LobbyCommands;
    while (true) {
        std::cout << "\n=== LOBBY MENU ===\n"
                  << "1) Listar partidas\n"
                  << "2) Crear partida\n"
                  << "3) Unirse a partida\n"
                  << "Elija una opción: ";
        int opt;
        if (!(std::cin >> opt)) std::exit(1);

        switch (opt) {
            case 1: {
                commands.try_push(std::make_unique<ListGamesDTO>());
                break;
            }
            case 2: {
                std::string name;
                int map_idx;
                std::cout << "Nombre de la partida: ";
                std::cin >> name;
                std::cout << "Mapa (0..N): ";
                std::cin >> map_idx;
                commands.try_push(std::make_unique<CreateGameDTO>(
                    name, static_cast<MapName>(map_idx)));
                return;  // salimos del lobby para entrar al game loop
            }
            case 3: {
                std::string name;
                std::cout << "Nombre de la partida: ";
                std::cin >> name;
                commands.try_push(std::make_unique<JoinGameDTO>(name));
                return;
            }
            default:
                std::cout << "Opción inválida\n";
        }
    }
}

void Client::run(int use_id) {
    sender.start();
    receiver.start();

    // lobby: menu interactivo que envía dtos (create, join y list, más otros)
    // al servidor
    lobby_phase();

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
    sender.stop();
    receiver.stop();
    sender.join();
    receiver.join();
}
