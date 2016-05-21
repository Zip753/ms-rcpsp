#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Population.h"
#include "Schedule.h"
#include "LAXCrossover.h"
#include "Mutator.h"
#include "Selector.h"
#include <cstdio>

class Algorithm {
public:
    Algorithm(Population *p, Selector *s, Crossover *c, Mutator *m, int _steps = -1, bool _rem_clones = true)
        : population(p), selector(s), crossover(c), mutator(m), steps(_steps), remove_clones(_rem_clones) {};
    Schedule* solve();
    Schedule* solve(FILE *stream);
private:
    Population *population;
    Selector *selector;
    Crossover *crossover;
    Mutator *mutator;
    int steps;
    bool remove_clones;
    Schedule *best = 0;
    Schedule* global_best = nullptr;

    void addToPopulation(Schedule **pop, int &i, Schedule *sample);

    void update_best();
};

#endif // ALGORITHM_H
