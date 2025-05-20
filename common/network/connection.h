#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>

#include "socket/socket.h"
#include "serializer.h"

class Connection {
private:
    Socket skt;

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

    void send_msg(const std::string& msg);
    std::string receive_msg();

private:
    std::string prepend_length(const std::string& msg);

    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;

    Connection(Connection&&) = default;
    Connection& operator=(Connection&&) = default;

    ~Connection() = default;
};

#endif
