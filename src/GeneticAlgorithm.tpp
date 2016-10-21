#include "../include/GeneticAlgorithm.h"

#include <memory>
#include <utility>
#include <vector>

#include "../include/Mutator.h"
#include "../include/PrioSchedule.h"
#include "../include/Selector.h"
#include "../include/SimpleSchedule.h"

namespace EvolutionaryAlgorithm {

template <class T>
std::shared_ptr<T> GeneticAlgorithm<T>::optimize(FILE* stat) {
  if (steps == -1) {
    return 0;
  }
  for (int step = 0; step < steps; step++) {
    // Evaluate population.
    update_best();
    // Output intermediate results.
    printf("step == %d\n", step);
    printf("best: ");
    best->printState(true);
    if (stat != nullptr) {
      population->showStat(stat);
    }
    // Move on to next generation.
    int n = population->size();
    std::vector<T*> next_pop = std::vector<T*>(n);
    for (int i = 0; i < n;) {
      T* a = selector->select(*population);
      T* b;
      do { b = selector->select(*population); } while (b == a);
      if (i == n - 1 || crossover->should_cross()) {
        T* a_cross = crossover->cross(a, b);
        T* a_mut = mutator->mutate(a_cross);
        TryRemoveClones(next_pop, i, a_mut);
        next_pop[i++] = a_mut;
        delete a_cross;
      } else {
        T* a_mut = mutator->mutate(a);
        TryRemoveClones(next_pop, i, a_mut);
        next_pop[i++] = a_mut;
        T* b_mut = mutator->mutate(b);
        TryRemoveClones(next_pop, i, b_mut);
        next_pop[i++] = b_mut;
      }
    }
    population = std::make_unique<Population<T>>(n, next_pop);
  }
  update_best();

  return global_best;
}

template <class T>
void GeneticAlgorithm<T>::update_best() {
  best = std::make_shared<T>(population->best());
  if (global_best == nullptr || global_best->fitness() > best->fitness()) {
    global_best = best;
  }
}

template <class T>
void GeneticAlgorithm<T>::TryRemoveClones(const std::vector<T*> &pop, int idx,
                                          T* sample) {
  if (remove_clones) {
    for (int k = 0; k < 3; k++) {
      bool contains = false;
      for (int i = 0; i < idx; i++)
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
GeneticAlgorithm<T>::GeneticAlgorithm(int pop_size,
                                      const std::shared_ptr<Selector<T>> &s,
                                      const std::shared_ptr<Crossover<T>> c,
                                      const std::shared_ptr<Mutator<T>> &m,
                                      int _steps,
                                      bool _rem_clones) :
    selector(s), crossover(c), mutator(m), steps(_steps),
    remove_clones(_rem_clones) {
  std::vector<T*> specimen = std::vector<T*>(pop_size);
  for (int i = 0; i < pop_size; ++i) {
    specimen[i] = new T();
  }
  population = std::make_unique<Population<T>>(pop_size, specimen);
}

};  // namespace EvolutionaryAlgorithm