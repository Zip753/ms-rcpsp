#include <algorithm>
#include <iomanip>
#include <iostream>

#include "../include/Population.h"

namespace EvolutionaryAlgorithm {

template <class T>
T* Population<T>::best() {
  size_t best_idx = 0;
  for (size_t i = 1; i < size(); i++) {
    if (specimen(i)->fitness() < specimen(best_idx)->fitness())
      best_idx = i;
  }
  return specimen(best_idx);
}

template <class T>
void Population<T>::ShowStat(std::ostream &stream) {
  int best_val = best()->fitness(),
      worst_val = 0;
  double mean = 0;
  for (size_t i = 0; i < size(); i++) {
    mean += specimen(i)->fitness();
    if (worst_val < specimen(i)->fitness())
      worst_val = specimen(i)->fitness();
  }
  mean /= size();

  stream << best_val << " " << mean << " " << worst_val;
}

template <class T>
Population<T>::Population(std::vector<std::unique_ptr<T>>* spec) {
  specimen_.reserve(spec->size());
  std::transform(std::make_move_iterator(spec->begin()),
                 std::make_move_iterator(spec->end()),
                 std::back_inserter(specimen_),
                 [](std::unique_ptr<T> p){ return std::move(p); });
}

};  // namespace EvolutionaryAlgorithm
