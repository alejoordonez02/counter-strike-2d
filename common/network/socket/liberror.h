/*
 * Este archivo fue tomado de hands-on-socket-in-cpp
 * Repositorio original: https://github.com/eldipa/hands-on-sockets-in-cpp
 * Licencia original: GPL v2
 *
 * De acuerdo con la GPL v2, este código se mantiene bajo la misma licencia.
 */
#ifndef LIB_ERROR_H
#define LIB_ERROR_H

#include <exception>

class LibError : public std::exception {
  char msg_error[256];

public:
  LibError(int error_code, const char *fmt, ...) noexcept;

  virtual const char *what() const noexcept;

  virtual ~LibError();
};

#endif
