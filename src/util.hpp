// util.hpp - small shared helpers (timer, RNG, error exit)
#pragma once
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <random>
#include <string>
#include <vector>

typedef long long i64;

[[noreturn]] inline void die(const std::string& msg) {
    std::fprintf(stderr, "mqc: error: %s\n", msg.c_str());
    std::exit(2);
}

struct Timer {
    std::chrono::steady_clock::time_point t0;
    Timer() : t0(std::chrono::steady_clock::now()) {}
    double sec() const {
        return std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count();
    }
};

struct Rng {
    std::mt19937_64 g;
    explicit Rng(uint64_t seed = 1) : g(seed) {}
    int below(int n) { return (int)(g() % (uint64_t)n); }          // uniform in [0, n)
    double unif() { return (g() >> 11) * (1.0 / 9007199254740992.0); }
    template <class V> void shuffle(V& v) {
        for (size_t i = v.size(); i > 1; --i) std::swap(v[i - 1], v[(size_t)(g() % i)]);
    }
};
