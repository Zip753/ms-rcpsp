#include "../include/Random.h"

#include <cstdlib>
#include <random>
#include <zconf.h>

namespace Util {

bool Random::_seed = false;

bool Random::rand(double prob) {
  double ans = (static_cast<double>(::rand()) / RAND_MAX);
  return ans < prob;
}

uint32_t mix(clock_t a, time_t b, __pid_t c) {
  a = a - b; a = a - c; a = a ^ (c >> 13);
  b = b - c; b = b - a; b = b ^ (a << 8);
  c = c - a; c = c - b; c = c ^ (b >> 13);
  a = a - b; a = a - c; a = a ^ (c >> 12);
  b = b - c; b = b - a; b = b ^ (a << 16);
  c = c - a; c = c - b; c = c ^ (b >> 5);
  a = a - b; a = a - c; a = a ^ (c >> 3);
  b = b - c; b = b - a; b = b ^ (a << 10);
  c = c - a; c = c - b; c = c ^ (b >> 15);
  return c;
}

void Random::seed() {
  if (!_seed) {
    _seed = true;
    uint32_t seed = mix(clock(), time(NULL), getpid());
    srand(seed);
  }
}

int Random::randint() {
  seed();
  return ::rand();
}

};  // namespace Util
