#ifndef SERVER_CLIENT_SESSION_H
#define SERVER_CLIENT_SESSION_H

#include <memory>
#include <utility>

#include "common/network/connection.h"
#include "common/network/dto.h"
#include "common/network/receiver.h"
#include "common/network/sender.h"
#include "common/queue.h"
#include "server/cmd_constructor.h"
#include "server/game_monitor.h"

class ClientSession {
    private:
    Connection con;
    Queue<std::shared_ptr<DTO>> send_q;
    Queue<std::unique_ptr<DTO>> recv_q;
    Sender sndr;
    Receiver rcvr;

    GameMonitor& game_monitor;
    CmdConstructor cmd_ctr;
    // Player& player; // default constructor PROBLEMA
    bool _is_finished;

    public:
    ClientSession(Socket&& s, GameMonitor& gm):
            con(std::move(s)),
            sndr(con, send_q),
            rcvr(con, recv_q),
            game_monitor(gm),
            _is_finished(false) {
        // ClientSetup setup(con, game_monitor, player);
        // setup.start();
        // setup.join();
        sndr.start();
        rcvr.start();
    }

    bool is_finished() { return _is_finished; }

    bool try_play() {
        std::unique_ptr<DTO> dto_p;
        if (recv_q.try_pop(dto_p)) {
            std::unique_ptr<Command> cmd_p =
                    cmd_ctr.construct(std::move(dto_p));
            // cmd_p->execute(player);
            return true;
        }
        return false;
    }

    bool try_push_game_update(/* std::shared_ptr<GameSnapshot> */) {
        // send_q.try_push(lo que sea que definamos en game loop)
        // agregar info especifica del player?
    }

    void end(
      /* std::shared_ptr<GameSnapshot> o std::shared_ptr<GameFinishedDTO> */) {
        // send_q.push(); // asegura push de update final
        send_q.close();
        sndr.join();
        // con.destroy_socket();
        recv_q.pop();  // desbloquear receiver por si estaba en push con queue
                       // llena
        rcvr.join();
        _is_finished = true;
    }

    void force_terminate() {  // falta definir
                              // con.destroy_socket();
        send_q.close();
        recv_q.close();
        sndr.join();
        rcvr.join();
        _is_finished = true;
    }

    ClientSession(const ClientSession&) = delete;
    ClientSession& operator=(const ClientSession&) = delete;

    ClientSession(ClientSession&&) =
            delete;  // Thread subclasses (sndr, rcvr) can't be moved
    ClientSession& operator=(ClientSession&&) = delete;

    ~ClientSession() = default;
};

#endif
