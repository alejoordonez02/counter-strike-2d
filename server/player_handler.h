#ifndef SERVER_PLAYER_HANDERL_H
#define SERVER_PLAYER_HANDERL_H

#include "common/network/connection.h"
#include "common/network/receiver.h"
#include "common/network/sender.h"
#include "common/queue.h"
#include "server/cmd_constructor.h"
#include "server/model/player.h"
#include "server/player_commands/command.h"

/*
 * Manejar la etapa del cliente jugando la partida
 * */
class PlayerHandler {
private:
    Connection con;
    Queue<std::unique_ptr<DTO>> snapshots;
    Queue<std::unique_ptr<DTO>> commands;
    Receiver receiver;
    Sender sender;
    std::shared_ptr<Player> player;
    CmdConstructor constructor;

public:
    PlayerHandler(Connection&& con, std::shared_ptr<Player> player):
            con(std::move(con)),
            receiver(this->con, commands),
            sender(this->con, snapshots),
            player(player) {}

    void start() {
        receiver.start();
        sender.start();
    }

    void play() {
        std::unique_ptr<DTO> dto;
        if (commands.try_pop(dto)) {
            std::unique_ptr<Command> cmd =
                    constructor.construct(std::move(dto));
            cmd->execute(*player);
        }
    }

    void send_snapshot(const Snapshot& snapshot) {
        auto dto = std::make_unique<SnapshotDTO>(snapshot);
        snapshots.push(std::move(dto));
    }
};

#endif
