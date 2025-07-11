/* * Este archivo fue tomado de hands-on-socket-in-cpp
 * Repositorio original: https://github.com/eldipa/hands-on-sockets-in-cpp
 * Licencia original: GPL v2
 *
 * De acuerdo con la GPL v2, este código se mantiene bajo la misma licencia.
 */
#ifndef COMMON_NETWORK_SOCKET_RESOLVER_ERROR_H
#define COMMON_NETWORK_SOCKET_RESOLVER_ERROR_H

#include <exception>

class ResolverError: public std::exception {
    private:
    int gai_errno;

    public:
    explicit ResolverError(int gai_errno);

    const char* what() const noexcept override;

    virtual ~ResolverError();
};
#endif
