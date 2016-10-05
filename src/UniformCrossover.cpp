#include "../include/Random.h"
#include "../include/UniformCrossover.h"

Schedule *UniformCrossover::cross(Schedule *a, Schedule *b) {
  Schedule *s = new Schedule(a);

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
