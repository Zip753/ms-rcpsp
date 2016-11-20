#include <algorithm>
#include <iomanip>
#include <iostream>

#include "../include/Population.h"

namespace Solutions {
namespace EvolutionaryAlgorithm {

template <class T>
T* Population<T>::best() {
  size_t best_idx = 0;
  for (size_t i = 1; i < size(); i++) {
    if (specimen(i)->Fitness() < specimen(best_idx)->Fitness())
      best_idx = i;
  }
  return specimen(best_idx);
}

template <class T>
void Population<T>::ShowStat(std::ostream &stream) {
  int best_val = best()->Fitness();
  size_t worst_idx = 0;
  double mean = 0;
  for (size_t i = 0; i < size(); i++) {
    mean += specimen(i)->Fitness();
    if (specimen(worst_idx)->Fitness() < specimen(i)->Fitness())
      worst_idx = i;
  }
  mean /= size();

  stream << best_val << " " << mean << " " << specimen(worst_idx)->Fitness();
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
};  // namespace Solutions
