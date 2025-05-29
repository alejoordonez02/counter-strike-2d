#include "gameloop.h"
#include "client.h"


// Client::Client(){}

void Client::run(){

    // receiver.start();
    // sender.start();    

    GameLoop gameloop(snapshots, comandos);
    gameloop.run();

}
