#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Population.h"
#include "Schedule.h"
#include "LAXCrossover.h"
#include "Mutator.h"
#include "Selector.h"
#include <cstdio>

/**
 * Class that is responsible for the algorithm structure and runtime.
 */
class Algorithm {
public:
    /**
     * Algorithm constructor.
     * Accepts dependency injections and simply stores them in private fields.
     */
    Algorithm(Population *p, Selector *s, Crossover *c, Mutator *m, int _steps = -1, bool _rem_clones = true)
        : population(p), selector(s), crossover(c), mutator(m), steps(_steps), remove_clones(_rem_clones) {};
    ~Algorithm();

    /**
     * Execute the genetic algorithm.
     * @param stream file stream for statistical output.
     * @return the most adapted specimen in all populations.
     */
    Schedule* solve(FILE *stream);
private:
    Population *population;
    Selector *selector;
    Crossover *crossover;
    Mutator *mutator;

    /**
     * Number of generations.
     */
    int steps;

    /**
     * Flag that specifies whether clone removal should be used.
     */
    bool remove_clones;

    /**
     * Copy of the best solution for the current population.
     */
    Schedule *best = nullptr;

    /**
     * Copy of the best solution for the whole run.
     */
    Schedule *global_best = nullptr;

    void addToPopulation(Schedule **pop, int &i, Schedule *sample);

    /**
     * Update best result for the current generation and for the algorithm itself.
     */
    void update_best();
};

#endif // ALGORITHM_H
