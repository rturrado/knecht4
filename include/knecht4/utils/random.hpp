#pragma once

#include <random>

namespace k4::utils {

// Random int generator
// Generates a random int in the range [low, high]
class RandomInt {
public:
    RandomInt(int low, int high) : low_{ low }, high_{ high } {}
    int operator()() {
        return std::uniform_int_distribution<int>{ low_, high_ }(engine_);
    }

private:
    int low_{ 0 };
    int high_{ 1 };
    std::default_random_engine engine_{ std::random_device{}() };
};

}  // namespace k4::utils
