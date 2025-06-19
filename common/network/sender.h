#ifndef COMMON_NETWORK_SENDER_H
#define COMMON_NETWORK_SENDER_H

#include <memory>
#include <stdexcept>

#include "connection.h"
#include "dto/dto.h"
#include "liberror.h"
#include "queue.h"
#include "thread.h"

class Sender: public Thread {
private:
    Connection& con;
    Queue<std::unique_ptr<DTO>>& queue;

public:
    Sender(Connection& c, Queue<std::unique_ptr<DTO>>& q): con(c), queue(q) {}

    void run() override {
        try {
            while (true) {
                std::unique_ptr<DTO> dto_p = queue.pop();
                con.send_msg(dto_p->serialize());
            }
        } catch (const std::runtime_error& err) {
            // ClosedQueue or socket was closed
        } catch (const LibError& err) {
            // socket was closed during Socket::sendall()
        }
    }

    ~Sender() = default;
};

#endif
