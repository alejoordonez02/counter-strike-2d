/*
 * Este archivo fue tomado de hands-on-socket-in-cpp
 * Repositorio original: https://github.com/eldipa/hands-on-sockets-in-cpp
 * Licencia original: GPL v2
 *
 * De acuerdo con la GPL v2, este código se mantiene bajo la misma licencia.
 */
#ifndef COMMON_NETWORK_SOCKET_LIB_ERROR_H
#define COMMON_NETWORK_SOCKET_LIB_ERROR_H

#include <exception>

class LibError: public std::exception {
    char msg_error[256];

    public:
    LibError(int error_code, const char* fmt, ...) noexcept;

    const char* what() const noexcept override;

    virtual ~LibError();
};

#endif
