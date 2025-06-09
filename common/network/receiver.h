#ifndef COMMON_NETWORK_RECEIVER_H
#define COMMON_NETWORK_RECEIVER_H

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include "common/network/connection.h"
#include "common/network/dto.h"
#include "common/network/dto_constructor.h"
#include "common/network/socket/liberror.h"
#include "common/queue.h"
#include "common/thread.h"

class Receiver: public Thread {
    private:
    Connection& con;
    Queue<std::unique_ptr<DTO>>& queue;
    DTOConstructor dto_ctr;

    public:
    Receiver(Connection& c, Queue<std::unique_ptr<DTO>>& q): con(c), queue(q) {}

    void run() override {
        try {
            while (true) {
                std::vector<uint8_t> msg = con.receive_msg();
                std::unique_ptr<DTO> dto_p = dto_ctr.construct(std::move(msg));
                queue.push(std::move(dto_p));
            }
        } catch (const std::runtime_error&
                         err) {  // ClosedQueue or socket was closed
        } catch (const LibError&
                         err) {  // socket was closed during Socket::recvall()
        }
    }

    ~Receiver() = default;
};

#endif
