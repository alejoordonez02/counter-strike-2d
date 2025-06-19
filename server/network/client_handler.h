#ifndef SERVER_CLIENT_HANDLER_H
#define SERVER_CLIENT_HANDLER_H

#include "common/network/connection.h"
#include "server/player_handler.h"

/*
 * Manejar la etapa previa a la partida, por ahora sólo tiene el método play
 * para arrancar a jugar con el PlayerHandler
 * */
class ClientHandler {
private:
    Connection con;

public:
    ClientHandler(Connection&& con): con(std::move(con)) {}

    std::unique_ptr<PlayerHandler> play(std::shared_ptr<Player> player) {
        return std::make_unique<PlayerHandler>(std::move(con), player);
    }
};

#endif
