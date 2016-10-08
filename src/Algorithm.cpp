#include "../include/Algorithm.h"
#include "../include/PrioSchedule.h"
#include "../include/SimpleSchedule.h"

template <class T>
Schedule* Algorithm<T>::solve(FILE *stat) {
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
      Schedule* a = selector->select(population);
      Schedule* b;
      do { b = selector->select(population); } while (b == a);
      if (i == n - 1 || crossover->should_cross()) {
        T *a_cross = crossover->cross(dynamic_cast<T*>(a), dynamic_cast<T*>(b));
        Schedule *a_mut = mutator->mutate(a_cross);
        addToPopulation(next_pop, &i, a_mut);
        delete a_cross;
      } else {
        addToPopulation(next_pop, &i, mutator->mutate(dynamic_cast<T*>(a)));
        addToPopulation(next_pop, &i, mutator->mutate(dynamic_cast<T*>(b)));
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
  if (best != nullptr) delete best;
  best = new T(dynamic_cast<T*>(population->best()));
  if (global_best == nullptr) {
    global_best = new T(dynamic_cast<T*>(best));
  } else if (global_best->fitness() > best->fitness()) {
    delete global_best;
    global_best = new T(dynamic_cast<T*>(best));
  }
}

template <class T>
void Algorithm<T>::addToPopulation(Schedule** pop, int* idx, Schedule* sample) {
  if (remove_clones) {
    for (int k = 0; k < 3; k++) {
      bool contains = false;
      for (int i = 0; i < *idx; i++)
        if (pop[i]->eq(sample)) {
          contains = true;
          break;
        }
      if (contains) {
        mutator->force_mutate(sample);
      } else {
        pop[(*idx)++] = sample;
        return;
      }
    }
    delete sample;
    pop[(*idx)++] = new T();
  } else {
    pop[(*idx)++] = sample;
  }
}

template <class T>
Algorithm<T>::~Algorithm() {
  delete population;
  delete selector;
  delete mutator;
  delete crossover;
  delete best;
  delete global_best;
}

template <class T>
Algorithm<T>::Algorithm(int pop_size, int tournament_size, Crossover<T>* c,
                        Mutator<T>* m, int _steps, bool _rem_clones) :
    crossover(c), mutator(m), steps(_steps), remove_clones(_rem_clones) {
  Schedule** specimen = new Schedule*[pop_size];
  for (int i = 0; i < pop_size; ++i) {
    specimen[i] = new T();
  }
  population = new Population(pop_size, specimen);
  selector = new Selector(tournament_size);
}

template class Algorithm<PrioSchedule>;
template class Algorithm<SimpleSchedule>;
