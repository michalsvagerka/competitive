#ifndef MAJK_RANDOM_H
#define MAJK_RANDOM_H

#include <random>
#include <chrono>
seed_seq seed{(ll)std::random_device{}(), std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()};
// seed_seq seed{12};
std::mt19937 rng{seed};
using random_int = std::uniform_int_distribution<int>;
using random_ll = std::uniform_int_distribution<ll>;

#endif //MAJK_RANDOM_H
