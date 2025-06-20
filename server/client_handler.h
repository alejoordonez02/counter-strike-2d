#ifndef SERVER_CLIENT_HANDLER_H
#define SERVER_CLIENT_HANDLER_H

#include "common/network/connection.h"
#include "common/thread.h"
#include "server/game_maker.h"
#include "server/lobby_command_constructor.h"

class ClientHandler: public Thread {
private:
    Connection con;
    GameMaker& game_maker;
    DTOConstructor dto_ctr;
    LobbyCmdConstructor cmd_ctr;

public:
    ClientHandler(Connection&& con, GameMaker& game_maker);

    void run() override;

    void handle_create(const std::string& game_name /*, TeamName team */);

    void handle_join(const std::string& game_name);

    void handle_list();
};

#endif
