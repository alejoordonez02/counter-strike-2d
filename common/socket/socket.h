/*
 * Este archivo fue tomado de hands-on-socket-in-cpp
 * Repositorio original: https://github.com/eldipa/hands-on-sockets-in-cpp
 * Licencia original: GPL v2
 *
 * De acuerdo con la GPL v2, este código se mantiene bajo la misma licencia.
 */
#ifndef SOCKET_H
#define SOCKET_H

class Socket {
private:
  int skt;
  bool closed;
  int stream_status;

  explicit Socket(int skt);

  void chk_skt_or_fail() const;

public:
  Socket(const char *hostname, const char *servname);

  explicit Socket(const char *servname);

  Socket(const Socket &) = delete;
  Socket &operator=(const Socket &) = delete;

  Socket(Socket &&);
  Socket &operator=(Socket &&);

  int sendsome(const void *data, unsigned int sz);
  int recvsome(void *data, unsigned int sz);

  int sendall(const void *data, unsigned int sz);
  int recvall(void *data, unsigned int sz);

  Socket accept();

  void shutdown(int how);

  bool is_stream_send_closed() const;
  bool is_stream_recv_closed() const;

  int close();

  ~Socket();
};
#endif
