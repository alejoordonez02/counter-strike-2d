#ifndef MOCK_SERVER_H
#define MOCK_SERVER_H

#include "../common/queue.h"
#include "../common/snapshot.h"
#include "../common/network/connection.h"
#include "../common/network/receiver.h"
#include "../common/network/sender.h"
#include "../common/network/dtos/snapshot_dto.h"
#include <memory>
#include <thread>
#include <iostream>


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

    // Poner un dato inicial de prueba del mock server en la cola de snapshots con un PlayerData
    PlayerData player1{};
    player1.player_id = 1;
    player1.team_id = 0;
    player1.x = 50;
    player1.y = 100;

    // Crear el snapshot inicial y agregar el jugador
    Snapshot snap{};
    snap.round_number = 0;
    snap.players.push_back(player1);

    // Empaquetar el snapshot en un DTO
    std::unique_ptr<DTO> initial_snapshot = std::make_unique<SnapshotDTO>(snap);

    // Si quieres ponerlo en la cola:
    snapshots_queue.try_push(std::move(initial_snapshot));

    // 5. Loop principal del mock server
    while (true) {
        // Obtener el último comando recibido (si hay)
        std::unique_ptr<DTO> dto_ptr;
        if (commands_queue.try_pop(dto_ptr)) {
            std::cout << "MockServer: Recibido comando tipo: " << int(dto_ptr->get_type()) << std::endl;

            // Crear un Snapshot de ejemplo (puedes personalizarlo)
            Snapshot snap;
            snap.round_number = 1;

            // Empaquetar el snapshot en un DTO y enviarlo al cliente
            std::shared_ptr<DTO> snapshot_dto = std::make_shared<SnapshotDTO>(snap);
            snapshots_queue.try_push(std::move(snapshot_dto));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}



#endif