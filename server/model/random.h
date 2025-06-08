#ifndef RANDOM_H
#define RANDOM_H

#include <functional>
#include <random>

class Random {
private:
    static std::mt19937_64 gen;
    static std::uniform_real_distribution<float> dist;
    static std::function<float()> custom_generator;

public:
    static void initialize();

    static void set_custom_generator(std::function<float()> generator);

    static void reset_custom_generator();

    static float get(const float& n = 0.0f, const float& m = 1.0f);
};

#endif
