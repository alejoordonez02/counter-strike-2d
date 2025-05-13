#ifndef CONNECTION_H
#define CONNECTION_H

#include <cstdint>
#include <string>
#include <vector>

#include "socket/socket.h"

class Connection {
private:
    Socket skt;

public:
    /*
     * For accepting
     * */
    Connection(Socket&& skt);

    /*
     * Server connection
     * */
    Connection(const std::string& servname);

    /*
     * Client connection
     * */
    Connection(const std::string& hostname, const std::string& servname);

    void send(std::vector<uint8_t> msg);
    std::vector<uint8_t> recv();
};

#endif
