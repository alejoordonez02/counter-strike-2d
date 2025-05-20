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

//     ~Receiver() = default;
// };

#endif
