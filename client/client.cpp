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
#include "common/team_name.h"
#include "lobbywindow.h"

Client::Client(const std::string& hostname, const std::string& servname):
    con(hostname, servname), commands(), snapshots(), sender(con, commands),
    receiver(con, snapshots), input_handler(commands) {}

void Client::lobby_phase() {
    using namespace DTOSerial::LobbyCommands;

    try {
        std::unique_ptr<LobbyWindow> lobbyWindow =
            std::make_unique<LobbyWindow>();
        lobbyWindow->setAttribute(Qt::WA_DeleteOnClose);

        QEventLoop lobbyLoop;

        QObject::connect(
            lobbyWindow.get(), &LobbyWindow::requestListGames,
            [this]() { commands.try_push(std::make_unique<ListGamesDTO>()); });

        // Conexión para crear partida
        QObject::connect(
            lobbyWindow.get(), &LobbyWindow::requestCreateGame,
            [&](const QString& name, int mapIdx, int teamIdx) {
                commands.try_push(std::make_unique<CreateGameDTO>(
                    name.toStdString(), static_cast<MapName>(mapIdx),
                    static_cast<TeamName>(teamIdx)));
                lobbyLoop.quit();
            });

        // Conexión para unirse a partida
        QObject::connect(
            lobbyWindow.get(), &LobbyWindow::requestJoinGame,
            [&](const QString& name, int teamIdx) {
                commands.try_push(std::make_unique<JoinGameDTO>(
                    name.toStdString(), static_cast<TeamName>(teamIdx)));
                lobbyLoop.quit();
            });

        lobbyWindow->show();
        lobbyLoop.exec();
        lobbyWindow->close();

    } catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "Error",
                              QString("Critical error: %1").arg(e.what()));
    }
}

void Client::run() {
    sender.start();
    receiver.start();

    // lobby: menu interactivo que envía dtos (create, join y list, más otros)
    // al servidor
    lobby_phase();

    // TODO: El mapa se debe poner descargar del server supuestamente
    // std::cout << "LOG: Current working directory: " <<
    // std::filesystem::current_path() << std::endl;
    MapLoader map_loader;
    MapData map_to_use =
        map_loader.loadMapData("tests/client/prueba_mapa_mod.yaml");

    // TODO: Aqui inicia un juego, la logica de las fases inicial, durante y
    // final se encontrará en el GameLoop
    GameLoop gameloop(snapshots, commands, map_to_use);
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
