#ifndef MS_RCPSP_ALGORITHM_H
#define MS_RCPSP_ALGORITHM_H

#include "LAXCrossover.h"
#include "Mutator.h"
#include "Population.h"
#include "Schedule.h"
#include "Selector.h"

#include <cstdio>

class Algorithm {
 public:
  Algorithm(Population *p, Selector *s, Crossover *c, Mutator *m,
            int _steps = -1, bool _rem_clones = true)
      : population(p), selector(s), crossover(c), mutator(m), steps(_steps),
        remove_clones(_rem_clones) {};
  ~Algorithm();

  Schedule *solve(FILE *stream);

 private:
  Population *population;
  Selector *selector;
  Crossover *crossover;
  Mutator *mutator;
  int steps;
  bool remove_clones;
  Schedule *best = nullptr, *global_best = nullptr;

  void addToPopulation(Schedule **pop, int &i, Schedule *sample);

  void update_best();
};

#endif // MS_RCPSP_ALGORITHM_H
