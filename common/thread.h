/*
 * Este archivo fue tomado de hands-on-thread
 * Repositorio original: https://github.com/eldipa/hands-on-threads
 * Licencia original: GPL v2
 *
 * De acuerdo con la GPL v2, este código se mantiene bajo la misma licencia.
 */
#ifndef THREAD_H_
#define THREAD_H_

#include <atomic>
#include <iostream>
#include <thread>

class Runnable {
public:
  virtual void start() = 0;
  virtual void join() = 0;
  virtual void stop() = 0;
  virtual bool is_alive() const = 0;

  virtual ~Runnable() {}
};

class Thread : public Runnable {
private:
  std::thread thread;

  std::atomic<bool> _keep_running;
  std::atomic<bool> _is_alive;

protected:
  bool should_keep_running() const { return _keep_running; }

public:
  Thread() : _keep_running(true), _is_alive(false) {}

  void start() override {
    _is_alive = true;
    _keep_running = true;
    thread = std::thread(&Thread::main, this);
  }

  void join() override { thread.join(); }

  void main() {
    try {
      this->run();
    } catch (const std::exception &err) {
      std::cerr << "Unexpected exception: " << err.what() << "\n";
    } catch (...) {
      std::cerr << "Unexpected exception: <unknown>\n";
    }

    _is_alive = false;
  }

  void stop() override { _keep_running = false; }

  bool is_alive() const override { return _is_alive; }

  virtual void run() = 0;
  virtual ~Thread() override {}

  Thread(const Thread &) = delete;
  Thread &operator=(const Thread &) = delete;

  Thread(Thread &&other) = delete;
  Thread &operator=(Thread &&other) = delete;
};

#endif
