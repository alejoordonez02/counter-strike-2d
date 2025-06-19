#ifndef COMMON_NETWORK_CONNECTION_H
#define COMMON_NETWORK_CONNECTION_H

#include <cstdint>
#include <string>
#include <vector>

#include "socket/socket.h"

class Connection {
private:
    Socket skt;

    void send_length(const std::vector<uint8_t>& msg);

public:
    /*
     * Server connection
     * */
    explicit Connection(Socket&& s);

    /*
     * Client connection
     * */
    Connection(const std::string& hostname, const std::string& servname);

    void send_msg(const std::vector<uint8_t>& msg);
    std::vector<uint8_t> receive_msg();
    void send_single(const uint8_t b);
    uint8_t receive_single();

    void destroy_socket();
    Socket release_socket();
    void acquire_socket(Socket&& s);

    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;

    Connection(Connection&&) = default;
    Connection& operator=(Connection&&) = default;

    ~Connection() = default;
};

#endif
