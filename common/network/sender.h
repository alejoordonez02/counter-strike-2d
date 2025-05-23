#ifndef SENDER_H
#define SENDER_H

#include "connection.h"
#include "../queue.h"
#include "../thread.h"
#include "serializer.h"

class Sender: public Thread {
private:
    Queue<std::unique_ptr<Serializable>> q; // hace falta up-cast
    Connection& con;
    Serializer szr;

public:
    Sender(Connection& c): con(c) {}

    void run() override {}

    bool try_push(std::unique_ptr<Serializable>&& u_p) { // ***
        return q.try_push(u_p); // puede que haga falta std::move(u_p) aca
    }

    ~Sender() = default;
};

#endif


// *** en EventHandler:
// std::unique_ptr<Serializable> cmd_p = std::make_unique<Attack>(args de Attack); // up-cast con move constructor de unique_ptr
// sender.try_push(cmd_p); // puede que haga falta std::move(cmd_p) aca

