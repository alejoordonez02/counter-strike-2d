#ifndef RANDOM_H
#define RANDOM_H

#include <random>

/*
 * Claramente estos los vamos a tener que generar más rápido, esto
 * es sólo un proto
 * */
class Random {
public:
    static float get(const float& n, const float& m) {
        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::uniform_real_distribution<float> dist(n, m);
        return dist(gen);
    }
};

#endif
