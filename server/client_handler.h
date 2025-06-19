#ifndef SERVER_CLIENT_HANDLER_H
#define SERVER_CLIENT_HANDLER_H

#include "common/network/connection.h"
#include "common/thread.h"
#include "server/game_maker.h"
#include "server/lobby_command_constructor.h"
#include "server/player_handler.h"

/*
 * Manejar la etapa previa a la partida, por ahora sólo tiene el método play
 * para arrancar a jugar con el PlayerHandler
 * */
class ClientHandler: public Thread {
private:
    Connection con;
    GameMaker& game_maker;
    DTOConstructor dto_ctr;
    LobbyCmdConstructor cmd_ctr;

public:
    ClientHandler(Connection&& con, GameMaker& game_maker):
        con(std::move(con)), game_maker(game_maker) {}

    void run() override {
        while (should_keep_running()) {
            std::vector<uint8_t> msg = con.receive_msg();
            std::unique_ptr<DTO> dto_p = dto_ctr.construct(std::move(msg));
            std::unique_ptr<LobbyCommand> cmd =
                cmd_ctr.construct(std::move(dto_p));
            cmd->execute(*this);
        }
    }

    void handle_create(const std::string& game_name /*, TeamName team */) {
        /*
         * Acá un try catch para evitar perder la conexión en caso de que la
         * partida no exista, esté llena, o no tenga lugar en el team elegido
         * */
        game_maker.create(std::move(con), game_name /*, team */);
    }

    void handle_join(const std::string& game_name) {
        /*
         * Try catch, misma idea que arriba
         * */
        game_maker.join(std::move(con), game_name /*, team */);
    }

    void handle_list() {
        // game_maker.list();
    }

    std::unique_ptr<PlayerHandler> play(std::shared_ptr<Player> player) {
        return std::make_unique<PlayerHandler>(std::move(con), player);
    }
};

#endif
