#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <chrono>

typedef unsigned long long uint64;

class Random {
private:
    std::mt19937 rng;
    uint64 generateSeed(uint64 seed);

public:
    Random();
    Random(uint64 seed);
    Random(uint64 seed1, uint64 seed2);

    int nextInt();
    long long nextLong();
    float nextFloat();
    double nextDouble();

    int nextInt(int min, int max);
    long long nextLong(long long min, long long max);
    float nextFloat(float min, float max);
    double nextDouble(double min, double max);

    template<typename T>
    T nextType() {
        std::uniform_real_distribution<T> dist;
        return dist(rng);
    }

    template<typename T>
    T nextType(T min, T max) {
        std::uniform_real_distribution<T> dist(min, max);
        return dist(rng);
    }
};

#endif // RANDOM_H