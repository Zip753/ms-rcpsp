#include "../include/GeneticAlgorithm.h"

#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#include "../include/Mutator.h"
#include "../include/PrioSchedule.h"
#include "../include/Selector.h"
#include "../include/SimpleSchedule.h"

namespace Solutions {
namespace EvolutionaryAlgorithm {

template <class T>
std::unique_ptr<T> GeneticAlgorithm<T>::Optimize(std::ostream &stat) {
  for (size_t step = 0; step < steps_; step++) {
    // Evaluate population.
    UpdateBest();
    // Output intermediate results.
    std::cout << "step == " << step << "\n";
    std::cout << "best: ";
    best_->PrintState(true);
    population_->ShowStat(stat);
    // Move on to next generation.
    size_t n = population_->size();
    std::vector<std::unique_ptr<T>> next_pop;
    next_pop.reserve(n);
    for (size_t iter = 0; iter < n;) {
      T* a = selector_->Select(*population_);
      T* b;
      do { b = selector_->Select(*population_); } while (b == a);
      if (iter == n - 1 || crossover_->should_cross()) {
        std::unique_ptr<T> a_cross(crossover_->Cross(*a, *b));
        MutateAndAddToPopulation(&next_pop, &iter, *a_cross);
      } else {
        MutateAndAddToPopulation(&next_pop, &iter, *a);
        MutateAndAddToPopulation(&next_pop, &iter, *b);
      }
    }
    population_ = std::make_unique<Population<T>>(&next_pop);
  }
  UpdateBest();

  return std::move(global_best_);
}

template <class T>
void GeneticAlgorithm<T>::MutateAndAddToPopulation(
    std::vector<std::unique_ptr<T>>* next_pop, size_t* iter, const T &a) {
  std::unique_ptr<T> a_mut = mutator_->Mutate(a);
  TryRemoveClones(*next_pop, (*iter)++, a_mut.get());
  next_pop->push_back(std::move(a_mut));
}

template <class T>
void GeneticAlgorithm<T>::UpdateBest() {
  best_ = std::make_unique<T>(*population_->Best());
  if (global_best_ == nullptr || global_best_->Fitness() > best_->Fitness()) {
    global_best_ = std::make_unique<T>(*best_);
  }
}

template <class T>
void GeneticAlgorithm<T>::TryRemoveClones(
    const std::vector<std::unique_ptr<T>> &pop, size_t idx, T* sample) {
  if (remove_clones_) {
    for (int k = 0; k < 3; k++) {
      bool contains = false;
      for (size_t i = 0; i < idx; i++)
        if (*pop[i] == *sample) {
          contains = true;
          break;
        }
      if (contains) {
        mutator_->force_mutate(sample);
      } else {
        return;
      }
    }
    sample->Reset();
  }
}

};  // namespace EvolutionaryAlgorithm
};  // namespace Solutions
