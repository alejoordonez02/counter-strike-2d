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

    // 3. Crear las colas compartidas
    Queue<std::shared_ptr<DTO>> commands_queue;
    Queue<std::unique_ptr<DTO>> snapshots_queue;

    // 4. Crear Receiver y Sender
    Receiver receiver(server_con, snapshots_queue); // Recibe comandos del cliente y los pone en snapshots_queue
    Sender sender(server_con, commands_queue);      // Envía snapshots al cliente desde commands_queue

    receiver.start();
    sender.start();

    // 5. Loop principal del mock server
    while (true) {
        // Obtener el último comando recibido (si hay)
        std::unique_ptr<DTO> dto_ptr;
        if (snapshots_queue.try_pop(dto_ptr)) {
            // Aquí podrías procesar el comando si quieres
            // Por ejemplo, imprimir el tipo de comando recibido
            std::cout << "MockServer: Recibido comando tipo: " << int(dto_ptr->get_type()) << std::endl;

            // Crear un Snapshot de ejemplo (puedes personalizarlo)
            Snapshot snap;
            snap.round_number = 1;
            snap.terrorists_score = 2;
            snap.counter_terrorists_score = 3;

            // Empaquetar el snapshot en un DTO y enviarlo al cliente
            auto snapshot_dto = std::make_shared<SnapshotDTO>(snap);
            commands_queue.try_push(snapshot_dto);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}



#endif