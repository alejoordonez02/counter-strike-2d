#include "client_handler.h"

#include <iostream>

#include "common/network/connection.h"
#include "game/game_maker.h"
#include "game_maker_error.h"
#include "lobby_commands/lobby_cmd_constructor.h"

ClientHandler::ClientHandler(Connection&& con, GameMaker& game_maker):
    con(std::move(con)), game_maker(game_maker) {}

void ClientHandler::run() {
    while (should_keep_running()) {
        std::vector<uint8_t> msg = con.receive_msg();
        std::unique_ptr<DTO> dto_p = dto_ctr.construct(std::move(msg));
        std::unique_ptr<LobbyCommand> cmd = cmd_ctr.construct(std::move(dto_p));
        cmd->execute(*this);
    }
}

void ClientHandler::handle_create(const std::string& game_name, MapName map,
                                  TeamName team) {
    try {
        game_maker.create(std::move(con), game_name, map, team);
        this->stop();
    } catch (const GameAlreadyExists& e) {
        con.send_single(LobbyCommands::FAILURE);
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error in ClientHandler::handle_create: "
                  << e.what() << std::endl;
        con.send_single(LobbyCommands::FAILURE);
        stop();
    }
}

void ClientHandler::handle_join(const std::string& game_name, TeamName team) {
    try {
        game_maker.join(std::move(con), game_name, team);
        this->stop();
    } catch (const GameNotFound& e) {
        con.send_single(LobbyCommands::FAILURE);
    } catch (const TeamIsFull& e) {
        con.send_single(LobbyCommands::FAILURE);
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error in ClientHandler::handle_join: "
                  << e.what() << std::endl;
        con.send_single(LobbyCommands::FAILURE);
        stop();
    }
}

void ClientHandler::handle_list() {
    // game_maker.list();
}
