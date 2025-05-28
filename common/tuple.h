#ifndef TUPLE_H
#define TUPLE_H

#include <cmath>

template <typename Derived, typename T>
struct Tuple {
    T x;
    T y;

    Tuple(const T& x, const T& y): x(x), y(y) {}

    float get_length() const { return std::sqrt(x * x + y * y); }

    float dot(const Derived& other) const { return x * other.x + y * other.y; }

    Derived operator+(const Derived& other) const { return Derived(x + other.x, y + other.y); }

    Derived operator-(const Derived& other) const { return Derived(x - other.x, y - other.y); }

    Derived& operator+=(const Derived& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Derived operator*(const float& n) const { return Derived(x * n, y * n); }

    bool operator==(const Derived& other) const { return x == other.x and y == other.y; }

    bool operator<(const Derived& other) const { return get_length() < other.get_length(); }
};

#endif
