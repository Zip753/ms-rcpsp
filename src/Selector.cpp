#include "../include/Selector.h"

#include "../include/Random.h"

Schedule *Selector::select(Population *p) {
  // select n random genotypes
  int p_size = p->size();
  int tourn_size = n;
  if (p_size < tourn_size)
    tourn_size = p_size;

  int best_fitness = 0;
  int best_id = 0;
  for (int i = 0; i < tourn_size; i++) {
    int idx = Random::randint() % p_size;
    if (i == 0 || best_fitness > p->genotype[idx]->fitness()) {
      best_id = idx;
      best_fitness = p->genotype[idx]->fitness();
    }
  }

  return p->genotype[best_id];
}
