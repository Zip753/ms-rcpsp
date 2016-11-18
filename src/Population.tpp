#include <algorithm>
#include "../include/Population.h"

namespace EvolutionaryAlgorithm {

template <class T>
T* Population<T>::best() {
  size_t best_idx = 0;
  for (size_t i = 1; i < n; i++) {
    if (genotype[i]->fitness() < genotype[best_idx]->fitness())
      best_idx = i;
  }
  return genotype[best_idx].get();
}

template <class T>
void Population<T>::showStat(FILE* stream) {
  int best_val = best()->fitness(),
      worst_val = 0;
  double mean = 0;
  for (size_t i = 0; i < n; i++) {
    mean += genotype[i]->fitness();
    if (worst_val < genotype[i]->fitness())
      worst_val = genotype[i]->fitness();
  }
  mean /= n;

  fprintf(stream, "%d %.4lf %d\n", best_val, mean, worst_val);
}

template <class T>
Population<T>::Population(std::vector<std::unique_ptr<T>>* spec) :
    n(spec->size()) {
  genotype.reserve(spec->size());
  std::transform(std::make_move_iterator(spec->begin()),
                 std::make_move_iterator(spec->end()),
                 std::back_inserter(genotype),
                 [](std::unique_ptr<T> p){ return std::move(p); });
}

};  // namespace EvolutionaryAlgorithm
