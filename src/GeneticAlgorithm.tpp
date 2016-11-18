#include "../include/GeneticAlgorithm.h"

#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#include "../include/Mutator.h"
#include "../include/PrioSchedule.h"
#include "../include/Selector.h"
#include "../include/SimpleSchedule.h"

namespace EvolutionaryAlgorithm {

template <class T>
std::unique_ptr<T> GeneticAlgorithm<T>::optimize(std::ostream &stat) {
  for (size_t step = 0; step < steps; step++) {
    // Evaluate population.
    update_best();
    // Output intermediate results.
    std::cout << "step == " << step << "\n";
    std::cout << "best: ";
    best->PrintState(true);
    population->ShowStat(stat);
    // Move on to next generation.
    size_t n = population->size();
    std::vector<std::unique_ptr<T>> next_pop;
    next_pop.reserve(n);
    for (size_t iter = 0; iter < n;) {
      T* a = selector->select(*population);
      T* b;
      do { b = selector->select(*population); } while (b == a);
      if (iter == n - 1 || crossover->should_cross()) {
        std::unique_ptr<T> a_cross(crossover->Cross(*a, *b));
        std::unique_ptr<T> a_mut = mutator->Mutate(*a_cross);
        TryRemoveClones(next_pop, iter++, a_mut.get());
        next_pop.push_back(std::move(a_mut));
      } else {
        std::unique_ptr<T> a_mut = mutator->Mutate(*a);
        TryRemoveClones(next_pop, iter++, a_mut.get());
        next_pop.push_back(std::move(a_mut));
        std::unique_ptr<T> b_mut = mutator->Mutate(*b);
        TryRemoveClones(next_pop, iter++, b_mut.get());
        next_pop.push_back(std::move(b_mut));
      }
    }
    population = std::make_unique<Population<T>>(&next_pop);
  }
  update_best();

  return std::move(global_best);
}

template <class T>
void GeneticAlgorithm<T>::update_best() {
  best = std::make_unique<T>(*population->best());
  if (global_best == nullptr || global_best->fitness() > best->fitness()) {
    global_best = std::make_unique<T>(*best);
  }
}

template <class T>
void GeneticAlgorithm<T>::TryRemoveClones(
    const std::vector<std::unique_ptr<T>> &pop, size_t idx, T* sample) {
  if (remove_clones) {
    for (int k = 0; k < 3; k++) {
      bool contains = false;
      for (size_t i = 0; i < idx; i++)
        if (*pop[i] == *sample) {
          contains = true;
          break;
        }
      if (contains) {
        mutator->force_mutate(sample);
      } else {
        return;
      }
    }
    sample->reset();
  }
}

template <class T>
GeneticAlgorithm<T>::GeneticAlgorithm(size_t pop_size,
                                      std::unique_ptr<Selector<T>> s,
                                      std::unique_ptr<Crossover<T>> c,
                                      std::unique_ptr<Mutator<T>> m,
                                      size_t _steps,
                                      bool _rem_clones) :
    selector(std::move(s)), crossover(std::move(c)), mutator(std::move(m)),
    steps(_steps), remove_clones(_rem_clones) {
  std::vector<std::unique_ptr<T>> specimen;
  specimen.reserve(pop_size);
  for (size_t i = 0; i < pop_size; ++i) {
    specimen.push_back(std::move(std::make_unique<T>()));
  }
  population = std::make_unique<Population<T>>(&specimen);
}

};  // namespace EvolutionaryAlgorithm
