#include "../include/Algorithm.h"

#include <memory>
#include <utility>

#include "../include/PrioSchedule.h"
#include "../include/SimpleSchedule.h"

template <class T>
std::shared_ptr<Schedule> Algorithm<T>::solve(FILE* stat) {
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
    if (stat != 0) {
      population->showStat(stat);
    }
    // Move on to next generation.
    int n = population->size();
    Schedule **next_pop = new Schedule *[n];
    for (int i = 0; i < n;) {
      Schedule* a = selector.select(population);
      Schedule* b;
      do { b = selector.select(population); } while (b == a);
      if (i == n - 1 || crossover.should_cross()) {
        T* a_cross = crossover.cross(dynamic_cast<T*>(a), dynamic_cast<T*>(b));
        T* a_mut = mutator.mutate(a_cross);
        addToPopulation(next_pop, i++, a_mut);
        delete a_cross;
      } else {
        addToPopulation(next_pop, i++, mutator.mutate(dynamic_cast<T*>(a)));
        addToPopulation(next_pop, i++, mutator.mutate(dynamic_cast<T*>(b)));
      }
    }
    delete population;
    population = new Population(n, next_pop);
  }
  update_best();

  return global_best;
}

template <class T>
void Algorithm<T>::update_best() {
  best = std::make_shared<T>(dynamic_cast<T*>(population->best()));
  if (global_best == nullptr || global_best->fitness() > best->fitness()) {
    global_best = best;
  }
}

template <class T>
void Algorithm<T>::addToPopulation(Schedule** pop, int idx, T* sample) {
  if (remove_clones) {
    for (int k = 0; k < 3; k++) {
      bool contains = false;
      for (int i = 0; i < idx; i++)
        if (*dynamic_cast<T*>(pop[i]) == *sample) {
          contains = true;
          break;
        }
      if (contains) {
        mutator.force_mutate(sample);
      } else {
        pop[idx] = sample;
        return;
      }
    }
    dynamic_cast<Schedule*>(sample)->reset();
  }
  pop[idx] = sample;
}

template <class T>
Algorithm<T>::~Algorithm() {
  delete population;
}

template <class T>
Algorithm<T>::Algorithm(int pop_size,
                        const Selector& s,
                        const Crossover<T> &c,
                        const Mutator<T> &m,
                        int _steps,
                        bool _rem_clones) :
    selector(s), crossover(c), mutator(m), steps(_steps),
    remove_clones(_rem_clones)
     {
  Schedule** specimen = new Schedule*[pop_size];
  for (int i = 0; i < pop_size; ++i) {
    specimen[i] = new T();
  }
  population = new Population(pop_size, specimen);
}

template class Algorithm<PrioSchedule>;
template class Algorithm<SimpleSchedule>;
