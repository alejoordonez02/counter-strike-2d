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
#include "common/network/dtos/snapshot_dto.h"

void mock_server() {
    // 1. Crear socket de escucha en localhost:7878
    Socket listen_socket("7878");
    Socket client_socket = listen_socket.accept();

    std::cout << "Se acepto una conexion entrante" << std::endl;

    // 2. Crear la conexión
    Connection server_con(std::move(client_socket));

    // 3. Crear las colas
    Queue<std::unique_ptr<DTO>> commands_queue;
    Queue<std::unique_ptr<DTO>> snapshots_queue;

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
    player1.current_weapon = WeaponType::AK47;


    PlayerData player2{};
    player2.player_id = 2;
    player2.team_id = 1;
    player2.is_walking = false;
    player2.is_shooting = true;
    player2.current_weapon = WeaponType::Glock;
    player2.x = 200;
    player2.y = 200;
    player2.aim_x = 400;
    player2.aim_y = 400;

    PlayerData player3{};
    player3.player_id = 3;
    player3.team_id = 1;
    player3.is_walking = false;
    player3.is_dead = true;
    player3.current_weapon = WeaponType::M3;
    player3.x = 400;
    player3.y = 300;

    auto initial_snap = std::make_unique<SnapshotDTO>();
    initial_snap->round_number = 0;
    initial_snap->players.push_back(player1);
    initial_snap->players.push_back(player2);
    initial_snap->players.push_back(player3);
    snapshots_queue.try_push(std::move(initial_snap));

    int counter = 0;

    // Loop del server
    while (true) {
        // Obtener el último comando recibido (si hay)
        std::unique_ptr<DTO> dto_ptr;
        if (commands_queue.try_pop(dto_ptr)) {
            std::cout << "MockServer: Recibido comando tipo: "
                      << int(dto_ptr->get_type()) << std::endl;
            if(dto_ptr->get_type() == DTOSerial::PlayerCommands::START_MOVING){
                StartMovingDTO* start_moving_dto = dynamic_cast<StartMovingDTO*>(dto_ptr.get());
                Direction new_pos = start_moving_dto->get_direction();
                // Procesar el comando de movimiento
                player1.x += new_pos.x * 20;
                player1.y += new_pos.y * 20;
                player1.is_walking = true;
            } else if (dto_ptr->get_type() == DTOSerial::PlayerCommands::STOP_MOVING) {
                // Procesar el comando de detener movimiento
                player1.is_walking = false;
            } else if (dto_ptr->get_type() == DTOSerial::PlayerCommands::START_ATTACKING) {
                // Procesar el comando de empezar a atacar
                StartAttackingDTO* start_attacking_dto = dynamic_cast<StartAttackingDTO*>(dto_ptr.get());
                if (start_attacking_dto) {
                    player1.is_shooting = true;
                    player1.current_weapon = WeaponType::M3;
                    std::cout << "start attacking " << player1.is_shooting << std::endl;
                }
            } else if (dto_ptr->get_type() == DTOSerial::PlayerCommands::STOP_ATTACKING) {
                // Procesar el comando de detener ataque
                StopAttackingDTO* stop_attacking_dto = dynamic_cast<StopAttackingDTO*>(dto_ptr.get());
                if (stop_attacking_dto) {
                    player1.is_shooting = false;
                    player1.current_weapon = WeaponType::Knife;
                    std::cout << "stop attacking " << player1.is_shooting << std::endl;
                }
            // } else if(dto_ptr->get_type() == DTOSerial::PlayerCommands::AIM){
            //     AimDTO* aim_dto = dynamic_cast<AimDTO*>(dto_ptr.get());
            //     if (aim_dto) {
                    
            //     }
            } else {
                std::cout << "Comando no reconocido: " << int(dto_ptr->get_type()) << std::endl;
                continue;
            }
            
            // debe crear siempre un nuevo snapshot
            auto snap = std::make_unique<SnapshotDTO>();

            counter++;
            if (counter == 10) {
                // Simular que los terroristas ganan cada 100 comandos
                snap->round_finished = true;
                snap->game_finished = true;
            }
            std::cout << "counter" << counter << std::endl;
            snap->round_number = counter;
            snap->players.push_back(player1);
            snap->players.push_back(player2);
            snap->players.push_back(player3);

            // Enviarlo al cliente
            snapshots_queue.try_push(std::move(snap));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

#endif
