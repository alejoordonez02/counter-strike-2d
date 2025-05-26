#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include "common/network/socket/socket.h"
#include "common/thread.h"

class Acceptor: public Thread {
private:
    Socket listener;

public:
    Acceptor(const std::string& servname);
    void run() override;
    void stop() override;
    ~Acceptor() = default;
};

#endif
