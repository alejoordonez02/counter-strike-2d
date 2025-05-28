#ifndef RECEIVER_H
#define RECEIVER_H

#include <stdexcept>

#include <vector>
#include <cstdint>

#include "connection.h"
#include "../queue.h"
#include "../thread.h"
#include "dto.h"
#include "socket/liberror.h"

class Receiver: public Thread {
private:
    Connection& con;
    Queue<DTO>& queue;

public:
    Receiver(Connection& c, Queue<DTO>& q): con(c), queue(q) {}

    void run() override {
        try {
            while (true) {
                std::vector<uint8_t> msg = con.receive_msg();
                DTO dto(std::move(msg));
                queue.push(std::move(dto));
            }
        } catch (const std::runtime_error& err) { // ClosedQueue or socket was closed
        } catch (const LibError& err) { // socket was closed during Socket::recvall()
        }
    }

    ~Receiver() = default;
};

#endif
