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
#include "common/team_name.h"
#include <QEventLoop>
#include <QMessageBox>
#include "mainwindow.h"

Client::Client(const std::string& hostname, const std::string& servname):
    con(hostname, servname), commands(), snapshots(), sender(con, commands),
    receiver(con, snapshots), input_handler(commands) {}

void Client::lobby_phase() {
    using namespace DTOSerial::LobbyCommands;

    try {
        // Variables para controlar el estado del lobby
        struct LobbyResult {
            bool completed = false;
            std::string matchName;
            TeamName team;
        } result;

        MainWindow mainWindow;
        mainWindow.show();

        // Event loop principal que esperará hasta que se complete el lobby
        QEventLoop mainLoop;

        QObject::connect(&mainWindow, &MainWindow::connectToLobby, [&]() {
            mainWindow.close();
            std::unique_ptr<LobbyWindow> lobbyWindow = std::make_unique<LobbyWindow>();
            lobbyWindow->setAttribute(Qt::WA_DeleteOnClose);

            QEventLoop lobbyLoop;

            QObject::connect(lobbyWindow.get(), &LobbyWindow::requestListGames, [this]() {
                commands.try_push(std::make_unique<ListGamesDTO>());
            });

            // Conexión para crear partida
            QObject::connect(lobbyWindow.get(), &LobbyWindow::requestCreateGame, 
                [&](const QString& name, int mapIdx, int teamIdx) {
                    commands.try_push(std::make_unique<CreateGameDTO>(
                        name.toStdString(),
                        static_cast<MapName>(mapIdx),
                        static_cast<TeamName>(teamIdx)
                    ));
                    result = {true, name.toStdString(), static_cast<TeamName>(teamIdx)};
                    lobbyLoop.quit();
                });

            // Conexión para unirse a partida
            QObject::connect(lobbyWindow.get(), &LobbyWindow::requestJoinGame,
                [&](const QString& name, int teamIdx) {
                    commands.try_push(std::make_unique<JoinGameDTO>(
                        name.toStdString(),
                        static_cast<TeamName>(teamIdx)
                    ));
                    result = {true, name.toStdString(), static_cast<TeamName>(teamIdx)};
                    lobbyLoop.quit();
                });

            // Si se cierra la ventana sin acción
            QObject::connect(lobbyWindow.get(), &LobbyWindow::destroyed, [&]() {
                if (!result.completed) {
                    QMessageBox::information(&mainWindow, "Información", "Saliendo del lobby");
                }
                lobbyLoop.quit();
            });

            lobbyWindow->show();
            lobbyLoop.exec(); // Bloquea aquí hasta quit() del lobbyLoop
            lobbyWindow->close();
            // Si se completó una acción, salir del loop principal
            if (result.completed) {
                mainLoop.quit();
            }
        });

        // Bloquea aquí hasta que se complete una acción o se cierre la aplicación
        mainLoop.exec();

        if (!result.completed) {
            throw std::runtime_error("User disconnected");
        }

        // Aquí puedes usar result.matchName y result.team para continuar
        // con la lógica del juego


    } catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "Error", QString("Error crítico: %1").arg(e.what()));
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
