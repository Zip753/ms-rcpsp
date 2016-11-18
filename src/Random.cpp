#include "../include/Random.h"

#include <random>

namespace Util {

std::random_device Random::rd;
std::mt19937 Random::gen = std::mt19937(Random::rd());
std::uniform_int_distribution<> Random::rand_int;
std::uniform_real_distribution<> Random::rand_real;

};  // namespace Util
