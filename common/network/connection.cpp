#include "connection.h"

#include <cstdint>
#include <sstream>
#include <utility>

#include <arpa/inet.h>

#include "protocol.h"

/*
 * For accepting
 * */
Connection::Connection(const std::string& servname): skt(servname.c_str()) {}

/*
 * Server connection
 * */
Connection::Connection(Socket&& s): skt(std::move(s)) {}

/*
 * Client connection
 * */
Connection::Connection(const std::string& hostname, const std::string& servname):
        skt(hostname.c_str(), servname.c_str()) {}


void Connection::send_msg(const std::string& msg) {
    std::string buf = prepend_length(msg);

    if (not skt.sendall(buf.data(), buf.size()))
        throw std::runtime_error("Socket send error: disconnected");
}

std::string Connection::receive_msg() {
    uint8_t size_buf[Message::LenBytes];
    if (not skt.recvall(size_buf, Message::LenBytes))
        throw std::runtime_error("Socket receive error: disconnected");

    uint16_t size = ntohs(*(uint16_t*)size_buf);

    char data_buf[Message::MaxLen] = {0};
    if (not skt.recvall(data_buf, size))  // asegurar size <= MaxMsgLen - 1
        throw std::runtime_error("Socket receive error: disconnected");

    return std::string(data_buf);
}

std::string Connection::prepend_length(const std::string& msg) {
    std::ostringstream oss;

    uint16_t size = htons(msg.size());
    oss.write((const char*)&size, sizeof(size));
    oss << msg;

    return oss.str();
}
