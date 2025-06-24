#include "client/client.h"

#include <bits/fs_fwd.h>

#include <QEventLoop>
#include <QMessageBox>
#include <filesystem>
#include <iostream>
#include <string>

#include "client/gameloop.h"
#include "common/map_name.h"
#include "common/maploader.h"
#include "common/network/dtos/create_game_dto.h"
#include "common/network/dtos/join_game_dto.h"
#include "common/network/dtos/list_games_dto.h"
#include "common/network/dtos/game_details_dto.h"
#include "common/team_name.h"
#include "lobbywindow.h"
#include "client/game_config.h"
#include "common/network/protocol.h"

Client::Client(const std::string& hostname, const std::string& servname):
    con(hostname, servname), commands(), snapshots(), sender(con, commands),
    receiver(con, snapshots), input_handler(commands) {}

MapName Client::lobby_phase(int i) {
    using namespace DTOSerial::LobbyCommands;
    MapName map_name = MapName::PRUEBA_MAPA_MOD; // HARDCODEADO

    if (i) {
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
                    commands.try_push(std::make_shared<ListGamesDTO>());
                    break;
                }
                case 2: {
                    std::string name;
                    int map_idx;
                    int team_idx;
                    std::cout << "Nombre de la partida: ";
                    std::cin >> name;
                    std::cout << "Mapa (0..N): ";
                    std::cin >> map_idx;
                    std::cout
                        << "Equipo (0: Terrorist, 1: Counter-Terrorist): ";
                    std::cin >> team_idx;
                    commands.try_push(std::make_shared<CreateGameDTO>(
                        name, static_cast<MapName>(map_idx),
                        static_cast<TeamName>(team_idx)));
                    map_name = static_cast<MapName>(map_idx);
                    return map_name;  // salimos del lobby para entrar al game loop
                }
                case 3: {
                    std::string name;
                    int team_idx;
                    std::cout << "Nombre de la partida: ";
                    std::cin >> name;
                    std::cout
                        << "Equipo (0: Terrorist, 1: Counter-Terrorist): ";
                    std::cin >> team_idx;
                    commands.try_push(std::make_shared<JoinGameDTO>(
                        name, static_cast<TeamName>(team_idx)));
                    // map_name = ???
                    return map_name;
                }
                default:
                    std::cout << "Opción inválida\n";
            }
        }
    } else {
        std::unique_ptr<LobbyWindow> lobbyWindow =
            std::make_unique<LobbyWindow>();
        lobbyWindow->setAttribute(Qt::WA_DeleteOnClose);

        QEventLoop lobbyLoop;

        QObject::connect(
            lobbyWindow.get(), &LobbyWindow::requestListGames, 
            [&]() {
                ListGamesDTO dto;
                con.send_msg(dto.serialize());
                auto n_games = con.receive_single();
                QList<GameDetailsDTO> list;
                for (int i = 0; i < n_games; i++) {
                    GameDetailsDTO dto(con.receive_msg());
                    list.append(dto);
                }
                lobbyWindow->setMatchesList(list);
                lobbyWindow->refreshMatchesListUI();
            }
        );

        // Conexión para crear partida
        QObject::connect(lobbyWindow.get(), &LobbyWindow::requestCreateGame, 
            [&](const QString& name, MapName m_name, TeamName t_name) {
                CreateGameDTO dto(name.toStdString(), m_name, t_name);
                con.send_msg(dto.serialize());
                auto res = con.receive_single();
                if (res == LobbyCommands::SUCCESS) {
                    lobbyWindow->close();
                    lobbyLoop.quit();
                    map_name = m_name;
                } else if (res == LobbyCommands::FAILURE) {
                    QMessageBox::critical(nullptr, "Failure!",
                        "Could not create game");
                }
                
            }
        );
        
        // Conexión para unirse a partida
        QObject::connect(lobbyWindow.get(), &LobbyWindow::requestJoinGame,
            [&](const QString& name, TeamName t_name, MapName m_name) {
                JoinGameDTO dto(name.toStdString(), t_name);
                con.send_msg(dto.serialize());
                auto res = con.receive_single();
                if (res == LobbyCommands::SUCCESS) {
                lobbyWindow->close();
                lobbyLoop.quit();
                map_name = m_name;
                } else if (res == LobbyCommands::FAILURE) {
                    QMessageBox::critical(nullptr, "Failure!",
                        "Could not join game");
                }
            }
        );

        lobbyWindow->show();
        lobbyWindow->on_refreshButton_clicked();
        lobbyLoop.exec(); 
    }
    return map_name; // ACOPLAR A CREATE Y JOIN (este enum se usa para cargar MapData para construir GameLoop)
}

void Client::run(int i) {
    // lobby: menu interactivo que envía operaciones (create, join y list, más otros)
    // al servidor
    MapName map_name = lobby_phase(i);
    
    sender.start();
    receiver.start();

    // TODO: El mapa se debe poner descargar del server supuestamente
    // std::cout << "LOG: Current working directory: " <<
    // std::filesystem::current_path() << std::endl;
    MapLoader map_loader;
    MapData map_to_use =
        map_loader.loadMapData(map_name);

    GameConfig game_config("config/client-config.yaml");

    // TODO: Aqui inicia un juego, la logica de las fases inicial, durante y
    // final se encontrará en el GameLoop
    GameLoop gameloop(snapshots, commands, map_to_use, game_config);
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
