#include "../include/UniformCrossover.h"

#include "../include/PrioSchedule.h"
#include "../include/Random.h"
#include "../include/SimpleSchedule.h"

namespace EvolutionaryAlgorithm {

using SchedulingProblem::PrioSchedule;

template<>
PrioSchedule* UniformCrossover<PrioSchedule>::cross(PrioSchedule* a,
                                                    PrioSchedule* b) const {
  PrioSchedule* s = new PrioSchedule(a);

  int n = s->size();
  for (int i = 0; i < n; i++) {
    if (Random::randint() % 2 == 1) {
      s->ires[i] = b->ires[i];
    }

    if (Random::randint() % 2 == 1) {
      s->prio[i] = b->prio[i];
    }
  }

  return s;
}

using SchedulingProblem::SimpleSchedule;

template<>
SimpleSchedule* UniformCrossover<SimpleSchedule>::cross(
    SimpleSchedule* a, SimpleSchedule* b) const {
  SimpleSchedule* s = new SimpleSchedule(a);

  int n = s->size();
  for (int i = 0; i < n; i++) {
    if (Random::randint() % 2 == 1) {
      s->ires[i] = b->ires[i];
    }
  }

  return s;
}

};  // namespace EvolutionaryAlgorithm
