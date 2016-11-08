#include "../include/TournamentSelector.h"

#include "../include/Random.h"

namespace EvolutionaryAlgorithm {

template <class T>
T* TournamentSelector<T>::select(const Population<T>& p) const {
  int p_size = p.size();
  int tourn_size = n;
  if (p_size < tourn_size)
    tourn_size = p_size;

  int best_fitness = 0;
  int best_id = 0;
  for (int i = 0; i < tourn_size; i++) {
    int idx = Util::Random::randint() % p_size;
    if (i == 0 || best_fitness > p.genotype[idx]->fitness()) {
      best_id = idx;
      best_fitness = p.genotype[idx]->fitness();
    }
  }

  return p.genotype[best_id].get();
}

};  // namespace EvolutionaryAlgorithm
