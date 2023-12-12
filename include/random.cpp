#include "random.h"

uint64 Random::generateSeed(uint64 seed) {
    long long hash = 0x811c9dc5;
    uint64 prime = 0x1000193;

    for (int i = 0; i < 8; i++) {
        uint64 value = seed & 0xff;
        hash = hash ^ value;
        hash *= prime;
        seed = seed >> 8;
    }

    return hash;
}

Random::Random() {
    uint64 seed = std::chrono::system_clock::now().time_since_epoch().count();
    seed = generateSeed(seed);
    rng.seed(seed);
}

Random::Random(uint64 seed) {
    seed = generateSeed(seed);
    rng.seed(seed);
}

Random::Random(uint64 seed1, uint64 seed2) {
    uint64 combined_seed = seed1 ^ seed2;
    combined_seed = generateSeed(combined_seed);
    rng.seed(combined_seed);
}

int Random::nextInt() {
    std::uniform_int_distribution<int> dist;
    return dist(rng);
}

long long Random::nextLong() {
    std::uniform_int_distribution<long long> dist;
    return dist(rng);
}

float Random::nextFloat() {
    std::uniform_real_distribution<float> dist;
    return dist(rng);
}

double Random::nextDouble() {
    std::uniform_real_distribution<double> dist;
    return dist(rng);
}

int Random::nextInt(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

long long Random::nextLong(long long min, long long max) {
    std::uniform_int_distribution<long long> dist(min, max);
    return dist(rng);
}

float Random::nextFloat(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(rng);
}

double Random::nextDouble(double min, double max) {
    std::uniform_real_distribution<double> dist(min, max);
    return dist(rng);
}
