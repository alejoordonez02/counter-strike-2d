/*
 * Este archivo fue tomado de hands-on-socket-in-cpp
 * Repositorio original: https://github.com/eldipa/hands-on-sockets-in-cpp
 * Licencia original: GPL v2
 *
 * De acuerdo con la GPL v2, este código se mantiene bajo la misma licencia.
 */
#undef _GNU_SOURCE
#undef GNU_SOURCE

#include "liberror.h"

#include <cstdarg>
#include <cstdio>
#include <cstring>

#include <errno.h>

LibError::LibError(int error_code, const char *fmt, ...) noexcept {
  va_list args;
  va_start(args, fmt);

  int s = vsnprintf(msg_error, sizeof(msg_error), fmt, args);

  va_end(args);

  if (s < 0) {
    msg_error[0] = msg_error[1] = msg_error[2] = '?';
    msg_error[3] = ' ';
    msg_error[4] = '\0';

    s = 4;
  } else if (s == sizeof(msg_error)) {
  }

  strerror_r(error_code, msg_error + s, sizeof(msg_error) - s);

  msg_error[sizeof(msg_error) - 1] = 0;
}

const char *LibError::what() const noexcept { return msg_error; }

LibError::~LibError() {}
