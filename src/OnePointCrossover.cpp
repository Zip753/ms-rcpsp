#include "../include/OnePointCrossover.h"

#include "../include/Random.h"
#include "../include/SimpleSchedule.h"
#include "../include/PrioSchedule.h"

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
