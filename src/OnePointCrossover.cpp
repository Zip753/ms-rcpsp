#include "../include/OnePointCrossover.h"
#include "../include/Random.h"

Schedule *OnePointCrossover::cross(Schedule *a, Schedule *b) {
  Schedule *s = new Schedule(a);

  int n = s->size();
  int idx = Random::randint() % n;
  for (int i = idx; i < n; i++)
    s->ires[i] = b->ires[i];

  return s;
}
