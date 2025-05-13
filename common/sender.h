#ifndef SENDER_H
#define SENDER_H

#include "connection.h"
#include "queue.h"
#include "serializable.h"
#include "thread.h"

class Sender: public Thread {
private:
    Queue<std::unique_ptr<Serializable>> msgs;
    Connection con;

public:
    void run() override;
};

#endif
