#include "../include/Crossover.h"
#include "../include/Random.h"

bool Crossover::should_cross() {
  return Random::rand(p_cross);
}