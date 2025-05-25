#ifndef TUPLE_H
#define TUPLE_H

#include <cmath>

template <typename T>
struct Tuple {
    T x;
    T y;

    Tuple(const T& x, const T& y): x(x), y(y) {}

    float get_length() const { return std::sqrt(x * x + y * y); }

    Tuple<T> operator+(const Tuple<T>& other) const { return Tuple<T>(x + other.x, y + other.y); }

    Tuple<T>& operator+=(const Tuple<T>& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    bool operator==(const Tuple<T>& other) const { return x == other.x and y == other.y; }

    bool operator<(const Tuple<T>& other) const { return get_length() < other.get_length(); }
};

#endif
