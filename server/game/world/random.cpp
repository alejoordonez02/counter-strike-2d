#include "random.h"

#include <functional>
#include <random>

void Random::initialize() {
    std::random_device rd;
    gen.seed(rd());
    dist = std::uniform_real_distribution<float>(0.0f, 1.0f);
    custom_generator = nullptr;  // Usar el generador por defecto
}

void Random::set_custom_generator(std::function<float()> generator) {
    custom_generator = generator;
}

void Random::reset_custom_generator() {
    custom_generator = nullptr;  // Volver al generador aleatorio real
}

float Random::get(const float& n, const float& m) {
    if (custom_generator) {
        return custom_generator();  // Usar el generador fijo
    }
    return std::uniform_real_distribution<float>(n, m)(gen);
}

std::mt19937_64 Random::gen;
std::uniform_real_distribution<float> Random::dist(0.0f, 1.0f);
std::function<float()> Random::custom_generator = nullptr;
