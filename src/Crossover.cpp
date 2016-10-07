#include "../include/Crossover.h"

#include "../include/Random.h"
#include "../include/Schedule.h"

template <class T>
bool Crossover<T>::should_cross() {
  return Random::rand(p_cross);
}

template class Crossover<Schedule>;
