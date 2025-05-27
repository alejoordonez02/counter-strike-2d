#ifndef CLIENT_SETUP_H
#define CLIENT_SETUP_H

#include "../common/thread.h"

class ClientSetup: public Thread {
    // pequeño thread sincronico con cliente para manejar lobby (create y join), nace y muere antes que los senders y receivers
private:

public:
    ClientSetup() {}

    void run() override {}

    ~ClientSetup() = default;
};

#endif
