#include "../include/Crossover.h"

#include "../include/PrioSchedule.h"
#include "../include/Random.h"
#include "../include/SimpleSchedule.h"

template <class T>
bool Crossover<T>::should_cross() {
  return Random::rand(p_cross);
}

template class Crossover<PrioSchedule>;
template class Crossover<SimpleSchedule>;
