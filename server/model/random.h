#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class Random {
private:
    static std::mt19937_64 gen;
    static std::uniform_real_distribution<float> dist;

public:
    static void initialize() {
        std::random_device rd;
        gen.seed(rd());
        dist = std::uniform_real_distribution<float>(0.0f, 1.0f);
    }

    static float get(const float& n = 0.0f, const float& m = 1.0f) {
        return std::uniform_real_distribution<float>(n, m)(gen);
    }
};

std::mt19937_64 Random::gen;
std::uniform_real_distribution<float> Random::dist(0.0f, 1.0f);

#endif
