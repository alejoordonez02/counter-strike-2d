#ifndef RECEIVER_H
#define RECEIVER_H

#include "connection.h"
#include "../queue.h"
#include "../thread.h"
#include "deserializer.h"
#include "../player_commands.h"

template <typename ReturnT>
class Receiver;


template <>
class Receiver<std::unique_ptr<Command>>: public Thread {
private:
    Queue<std::unique_ptr<Command>> q;
    Connection& con;
    Deserializer<std::unique_ptr<Command>> deszr;

public:
    Receiver(Connection& c): con(c) {}

    void run() override {}

    bool try_pop(std::unique_ptr<Command>& u_p) { // en GameLoop: std::unique_ptr<Command> p; receiver.try_pop(p);
        return q.try_pop(u_p); // habria que ver si la linea 74 de queue.h hace un move assignment por ser un unique_ptr
    }

    ~Receiver() = default;
};


// template <>
// class Receiver<GameState>: public Thread {
// private:
//     Queue<GameState> q;
//     Connection& con;
//     Deserializer<GameState> deszr;

// public:
//     Receiver(Connection& c): con(c) {}

//     void run() override {}

//     bool try_pop(GameState& gs) { // en cliente: pasar el GameState a actualizar
//         return q.try_pop(gs);
//     }

//     ~Receiver() = default;
// };

#endif
