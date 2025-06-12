#ifndef MOCK_SERVER_H
#define MOCK_SERVER_H

#include <iostream>
#include <memory>
#include <thread>
#include <utility>

#include "common/network/connection.h"
#include "common/network/dtos/snapshot_dto.h"
#include "common/network/receiver.h"
#include "common/network/sender.h"
#include "common/queue.h"
#include "common/snapshot.h"

void mock_server() {
    // 1. Crear socket de escucha en localhost:7878
    Socket listen_socket("7878");
    Socket client_socket = listen_socket.accept();

    std::cout << "Se acepto una conexion entrante" << std::endl;

    // 2. Crear la conexión
    Connection server_con(std::move(client_socket));

    // 3. Crear las colas
    Queue<std::unique_ptr<DTO>> commands_queue;
    Queue<std::shared_ptr<DTO>> snapshots_queue;

    // 4. Crear Receiver y Sender
    Receiver receiver(server_con, commands_queue);
    Sender sender(server_con, snapshots_queue);

    receiver.start();
    sender.start();

    // ======== inicializacion ========
    PlayerData player1{};
    player1.player_id = 1;
    player1.team_id = 0;
    player1.is_walking = false;


    PlayerData player2{};
    player2.player_id = 2;
    player2.team_id = 1;
    player2.is_walking = false;
    player2.x = 200;
    player2.y = 200;

    PlayerData player3{};
    player3.player_id = 3;
    player3.team_id = 1;
    player3.is_walking = false;
    player3.x = 400;
    player3.y = 300;

    Snapshot initial_snap{};
    initial_snap.round_number = 0;
    initial_snap.players.push_back(player1);
    initial_snap.players.push_back(player2);
    initial_snap.players.push_back(player3);
    std::unique_ptr<DTO> initial_snapshot = std::make_unique<SnapshotDTO>(initial_snap);
    snapshots_queue.try_push(std::move(initial_snapshot));
    // TODO: habria que hacer esto: pero no me funca, son las 2am y estoy
    // cansado jefe -alepaff Map map; Player player(Position(0, 0),
    //               Equipment(std::make_unique<Fist>(),
    //               std::make_unique<Fist>(),
    //                         std::make_unique<Fist>(), 0),
    //               map);
    // CmdConstructor constructor;
    // std::unique_ptr<Command> cmd = constructor.construct(std::move(dto_ptr));
    // cmd->execute(player);
    // ================================

    // Loop del server
    while (true) {
        // Obtener el último comando recibido (si hay)
        std::unique_ptr<DTO> dto_ptr;
        if (commands_queue.try_pop(dto_ptr)) {
            std::cout << "MockServer: Recibido comando tipo: "
                      << int(dto_ptr->get_type()) << std::endl;
            StartMovingDTO* start_moving_dto =
                    dynamic_cast<StartMovingDTO*>(dto_ptr.get());
            if (!start_moving_dto) {
                continue;
            }

            // Procesar el comando de movimiento
            Direction new_pos = start_moving_dto->get_direction();
            player1.x += new_pos.x * 5;
            player1.y += new_pos.y * 5;
            player1.is_walking = true;
            std::cout << "MockServer: Jugador movido a (" << player1.x << ", "
                      << player1.y << ")" << std::endl;

            // debe crear siempre un nuevo snapshot
            Snapshot snap{};
            snap.round_number = 1;
            snap.players.push_back(player1);
            snap.players.push_back(player2);
            snap.players.push_back(player3);

            // Empaquetar el snapshot en un DTO y enviarlo al cliente
            std::shared_ptr<DTO> snapshot_dto =
                    std::make_shared<SnapshotDTO>(snap);
            snapshots_queue.try_push(std::move(snapshot_dto));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

#endif
