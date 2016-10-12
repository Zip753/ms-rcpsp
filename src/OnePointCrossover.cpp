#include "../include/OnePointCrossover.h"

#include "../include/PrioSchedule.h"
#include "../include/Random.h"
#include "../include/SimpleSchedule.h"

namespace EvolutionaryAlgorithm {

using SchedulingProblem::SimpleSchedule;

template<>
SimpleSchedule* OnePointCrossover<SimpleSchedule>::cross(
    SimpleSchedule* a, SimpleSchedule* b) const {
  SimpleSchedule* s = new SimpleSchedule(a);

  int n = s->size();
  int idx = Random::randint() % n;
  for (int i = idx; i < n; i++)
    s->ires[i] = b->ires[i];

  return s;
}

using SchedulingProblem::PrioSchedule;

template<>
PrioSchedule* OnePointCrossover<PrioSchedule>::cross(PrioSchedule* a,
                                                     PrioSchedule* b) const {
  PrioSchedule* s = new PrioSchedule(a);

  int n = s->size();
  int idx = Random::randint() % n;
  for (int i = idx; i < n; i++)
    s->ires[i] = b->ires[i];

  return s;
}

};  // namespace EvolutionaryAlgorithm
