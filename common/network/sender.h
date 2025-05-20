#ifndef SENDER_H
#define SENDER_H

#include "connection.h"
#include "../queue.h"
#include "../thread.h"
#include "serializer.h"

class Sender: public Thread {
private:
    Queue<std::unique_ptr<Serializable>> q; // up-cast
    Connection& con;
    Serializer szr;

public:
    Sender(Connection& c): con(c) {}

    void run() override {}

    ~Sender() = default;
};

#endif
