#include "gameloop.h"
#include "client.h"


Client::Client(const std::string& hostname, const std::string& servname):
    con(hostname, servname),
    snapshots(),
    commands(),
    sender(con, commands),
    receiver(con, snapshots)
{}

void Client::run(){

    sender.start();
    receiver.start(); 

    GameLoop gameloop(snapshots, commands);
    gameloop.run();

}
