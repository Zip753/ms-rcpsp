#ifndef MS_RCPSP_ALGORITHM_H
#define MS_RCPSP_ALGORITHM_H

#include "Crossover.h"
#include "Mutator.h"
#include "Population.h"
#include "Schedule.h"
#include "Selector.h"

#include <cstdio>

class Algorithm {
 public:
  Algorithm(int pop_size, int tournament_size, Crossover<Schedule> *c,
            Mutator<Schedule> *m, int _steps = -1, bool _rem_clones = true);
  ~Algorithm();

  Schedule *solve(FILE *stream);

 private:
  Population *population;
  Selector *selector;
  Crossover<Schedule> *crossover;
  Mutator<Schedule> *mutator;
  int steps;
  bool remove_clones;
  Schedule *best = nullptr, *global_best = nullptr;

  void addToPopulation(Schedule **pop, int &i, Schedule *sample);

  void update_best();
};

#endif // MS_RCPSP_ALGORITHM_H
