/*
 * Este archivo fue tomado de hands-on-thread
 * Repositorio original: https://github.com/eldipa/hands-on-threads
 * Licencia original: GPL v2
 *
 * De acuerdo con la GPL v2, este código se mantiene bajo la misma licencia.
 */
#ifndef COMMON_QUEUE_H_
#define COMMON_QUEUE_H_

#include <climits>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <utility>

struct ClosedQueue: public std::runtime_error {
    ClosedQueue(): std::runtime_error("The queue is closed") {}
};

template <typename T, class C = std::deque<T>>
class Queue {
    private:
    std::queue<T, C> q;
    const unsigned int max_size;

    bool closed;

    std::mutex mtx;
    std::condition_variable is_not_full;
    std::condition_variable is_not_empty;

    public:
    Queue(): max_size(UINT_MAX - 1), closed(false) {}
    explicit Queue(const unsigned int max_size):
            max_size(max_size), closed(false) {}

    template <typename U>
    bool try_push(U&& val) {
        std::unique_lock<std::mutex> lck(mtx);

        if (closed) {
            throw ClosedQueue();
        }

        if (q.size() == this->max_size) {
            return false;
        }

        if (q.empty()) {
            is_not_empty.notify_all();
        }

        q.push(std::forward<U>(val));
        return true;
    }

    bool try_pop(T& val) {
        std::unique_lock<std::mutex> lck(mtx);

        if (q.empty()) {
            if (closed) {
                throw ClosedQueue();
            }
            return false;
        }

        if (q.size() == this->max_size) {
            is_not_full.notify_all();
        }

        val = std::move(q.front());
        q.pop();
        return true;
    }

    template <typename U>
    void push(U&& val) {
        std::unique_lock<std::mutex> lck(mtx);

        if (closed) {
            throw ClosedQueue();
        }

        while (q.size() == this->max_size) {
            is_not_full.wait(lck);
        }

        if (q.empty()) {
            is_not_empty.notify_all();
        }

        q.push(std::forward<U>(val));
    }

    T pop() {
        std::unique_lock<std::mutex> lck(mtx);

        while (q.empty()) {
            if (closed) {
                throw ClosedQueue();
            }
            is_not_empty.wait(lck);
        }

        if (q.size() == this->max_size) {
            is_not_full.notify_all();
        }

        T val = std::move(q.front());
        q.pop();

        return val;
    }

    void close() {
        std::unique_lock<std::mutex> lck(mtx);

        if (closed) {
            throw std::runtime_error("The queue is already closed.");
        }

        closed = true;
        is_not_empty.notify_all();
    }

    private:
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
};

template <>
class Queue<void*> {
    private:
    std::queue<void*> q;
    const unsigned int max_size;

    bool closed;

    std::mutex mtx;
    std::condition_variable is_not_full;
    std::condition_variable is_not_empty;

    public:
    explicit Queue(const unsigned int max_size):
            max_size(max_size), closed(false) {}

    bool try_push(void* const& val) {
        std::unique_lock<std::mutex> lck(mtx);

        if (closed) {
            throw ClosedQueue();
        }

        if (q.size() == this->max_size) {
            return false;
        }

        if (q.empty()) {
            is_not_empty.notify_all();
        }

        q.push(val);
        return true;
    }

    bool try_pop(void*& val) {
        std::unique_lock<std::mutex> lck(mtx);

        if (q.empty()) {
            if (closed) {
                throw ClosedQueue();
            }
            return false;
        }

        if (q.size() == this->max_size) {
            is_not_full.notify_all();
        }

        val = q.front();
        q.pop();
        return true;
    }

    void push(void* const& val) {
        std::unique_lock<std::mutex> lck(mtx);

        if (closed) {
            throw ClosedQueue();
        }

        while (q.size() == this->max_size) {
            is_not_full.wait(lck);
        }

        if (q.empty()) {
            is_not_empty.notify_all();
        }

        q.push(val);
    }

    void* pop() {
        std::unique_lock<std::mutex> lck(mtx);

        while (q.empty()) {
            if (closed) {
                throw ClosedQueue();
            }
            is_not_empty.wait(lck);
        }

        if (q.size() == this->max_size) {
            is_not_full.notify_all();
        }

        void* const val = q.front();
        q.pop();

        return val;
    }

    void close() {
        std::unique_lock<std::mutex> lck(mtx);

        if (closed) {
            throw std::runtime_error("The queue is already closed.");
        }

        closed = true;
        is_not_empty.notify_all();
    }

    private:
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
};

template <typename T>
class Queue<T*>: private Queue<void*> {
    public:
    explicit Queue(const unsigned int max_size): Queue<void*>(max_size) {}

    using Queue<void*>::try_push;
    using Queue<void*>::try_pop;
    using Queue<void*>::push;
    using Queue<void*>::pop;
    using Queue<void*>::close;

    bool try_push(T* const& val) override {
        return Queue<void*>::try_push(val);
    }

    bool try_pop(T*& val) override {
        return Queue<void*>::try_pop((void*&)val);
    }  // cppcheck-suppress cstyleCast

    void push(T* const& val) override { return Queue<void*>::push(val); }

    T* pop() override { return static_cast<T*>(Queue<void*>::pop()); }

    private:
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
};

#endif
