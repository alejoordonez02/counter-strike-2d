#include "connection.h"

#include <string>
#include <vector>
#include <cstdint>
#include <stdexcept>

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


void Connection::send_msg(const std::vector<uint8_t>& msg) {
    if (msg.size() > Message::MaxLen)
        throw std::runtime_error("Connection send error: message is too large");

    send_length(msg);

    if (not skt.sendall(msg.data(), msg.size()))
        throw std::runtime_error("Socket send error: disconnected");
}

std::vector<uint8_t> Connection::receive_msg() {
    uint8_t size_buf[Message::LenBytes];
    if (not skt.recvall(size_buf, Message::LenBytes))
        throw std::runtime_error("Socket receive error: disconnected");

    uint16_t size = ntohs(*(uint16_t*)size_buf);

    std::vector<uint8_t> data_buf(size);
    if (not skt.recvall(data_buf.data(), size))
        throw std::runtime_error("Socket receive error: disconnected");

    return data_buf;
}

void Connection::send_length(const std::vector<uint8_t>& msg) {
    uint16_t size = htons(msg.size());
    std::vector<uint8_t> buf;
    
    buf.push_back(static_cast<uint8_t>(size >> 8));
    buf.push_back(static_cast<uint8_t>(size & 0xFF));

    if (not skt.sendall(buf.data(), buf.size()))
        throw std::runtime_error("Socket send error: disconnected");
}
