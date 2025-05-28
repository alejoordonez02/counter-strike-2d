#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>
#include <vector>
#include <cstdint>

#include "socket/socket.h"

class Connection {
private:
    Socket skt;

    void send_length(const std::vector<uint8_t>& msg);

public:
    /*
     * For accepting
     * */
    Connection(const std::string& servname);

    /*
     * Server connection
     * */
    Connection(Socket&& s);

    /*
     * Client connection
     * */
    Connection(const std::string& hostname, const std::string& servname);

    
    void send_msg(const std::vector<uint8_t>& msg);
    std::vector<uint8_t> receive_msg();


    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;

    Connection(Connection&&) = default;
    Connection& operator=(Connection&&) = default;

    ~Connection() = default;
};

#endif
