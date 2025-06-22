#include "player_handler.h"

#include "common/network/connection.h"
#include "common/network/receiver.h"
#include "common/network/sender.h"
#include "common/queue.h"
#include "player_commands/player_cmd_constructor.h"
#include "player_commands/player_command.h"
#include "world/player.h"

PlayerHandler::PlayerHandler(Connection&& con, std::shared_ptr<Player> player):
    con(std::move(con)), receiver(this->con, commands),
    sender(this->con, snapshots), player(player) {}

void PlayerHandler::start() {
    receiver.start();
    sender.start();
}

void PlayerHandler::play() {
    std::unique_ptr<DTO> dto;
    if (commands.try_pop(dto)) {
        std::unique_ptr<Command> cmd = constructor.construct(std::move(dto));
        cmd->execute(*player);
    }
}

void PlayerHandler::send_snapshot(SnapshotDTO& snapshot) {
    snapshot.user_data = player->get_special_data();
    auto dto = std::make_unique<SnapshotDTOB>(snapshot);
    snapshots.push(std::move(dto));
}
