#ifndef SENDER_H
#define SENDER_H

#include <stdexcept>

#include "connection.h"
#include "../queue.h"
#include "../thread.h"
#include "dto.h"
#include "socket/liberror.h"

class Sender: public Thread {
private:
    Connection& con;
    Queue<DTO>& queue;

public:
    Sender(Connection& c, Queue<DTO>& q): con(c), queue(q) {}

    void run() override {
        try {
            while (true) {
                DTO dto = queue.pop();
                con.send_msg(dto.serialize());
            }
        } catch (const std::runtime_error& err) { // ClosedQueue or socket was closed
        } catch (const LibError& err) { // socket was closed during Socket::sendall()
        }

    }

    ~Sender() = default;
};

#endif
