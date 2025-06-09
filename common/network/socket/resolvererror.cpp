/* * Este archivo fue tomado de hands-on-socket-in-cpp
 * Repositorio original: https://github.com/eldipa/hands-on-sockets-in-cpp
 * Licencia original: GPL v2
 *
 * De acuerdo con la GPL v2, este código se mantiene bajo la misma licencia.
 */
#include "common/network/socket/resolvererror.h"

#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>

ResolverError::ResolverError(int gai_errno): gai_errno(gai_errno) {}

const char* ResolverError::what() const noexcept {
    return gai_strerror(gai_errno);
}

ResolverError::~ResolverError() {}
