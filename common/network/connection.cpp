#include "connection.h"

#include <arpa/inet.h>

#include <cstdint>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "protocol.h"
#include "socket/socket.h"

/*
 * Server connection
 * */
Connection::Connection(Socket&& s): skt(std::move(s)) {}

/*
 * Client connection
 * */
Connection::Connection(const std::string& hostname,
                       const std::string& servname):
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
    uint16_t sz_be = htons(msg.size());

    if (not skt.sendall(&sz_be, sizeof(sz_be)))
        throw std::runtime_error("Socket send error: disconnected");
}

void Connection::send_single(const uint8_t b) {
    if (not skt.sendall(&b, 1))
        throw std::runtime_error("Socket send error: disconnected");
}

uint8_t Connection::receive_single() {
    uint8_t b;
    if (not skt.recvall(&b, 1))
        throw std::runtime_error("Socket receive error: disconnected");

    return b;
}

void Connection::destroy_socket() {
    skt.shutdown(2);
    skt.close();
}

Socket Connection::release_socket() { return std::move(skt); }

void Connection::acquire_socket(Socket&& s) { skt = std::move(s); }
