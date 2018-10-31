#ifndef MAJK_RANDOM_H
#define MAJK_RANDOM_H

#include <random>
#include <chrono>
auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
std::mt19937 rng(12);
using random_int = std::uniform_int_distribution<int>;
using random_ll = std::uniform_int_distribution<ll>;
struct TimeLimit {
    TimeLimit(double seconds) : s(seconds-0.2), last(clock()), mx(0) {}
    operator bool() const { clock_t cur = clock(); mx = max(mx, cur-last); last = cur; return clock() < s * CLOCKS_PER_SEC - 1.5 * mx; }
    double s; mutable clock_t last, mx;
};

#endif //MAJK_RANDOM_H
