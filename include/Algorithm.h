#ifndef MS_RCPSP_ALGORITHM_H
#define MS_RCPSP_ALGORITHM_H

#include "Crossover.h"
#include "Mutator.h"
#include "Population.h"
#include "Schedule.h"
#include "Selector.h"

#include <cstdio>

/** @mainpage
 * This is the library that implements the backbone for genetic algorithms.
 * It is possible to add new mutation and crossover operators, as well as new
 * specimen (schedule) representations by extending respective base classes.
 */

/**
 * @brief Representation of genetic algorithm. Glues everything together.
 * @param T Type of specimen representation, subclass of Schedule.
 */
template <class T>
class Algorithm {
 public:
  /**
   * @param pop_size Size of the population.
   * @param tournament_size Size of the tournament for selection.
   * @param c Pointer to the crossover operator.
   * @param m Pointer to the mutation operator.
   */
  Algorithm(int pop_size, int tournament_size, Crossover<T>* c, Mutator<T>* m,
            int _steps = -1, bool _rem_clones = true);
  ~Algorithm();

  /**
   * Executes the genetic algorithm.
   * @param stream File stream for statistics output.
   * @return The most adapted specimen in all populations (best solution found).
   */
  Schedule* solve(FILE* stream);

 private:
  Population* population;
  Selector* selector;
  Crossover<T>* crossover;
  Mutator<T>* mutator;
  /** Number of generations. */
  int steps;
  /** If true, removes clones from the population. */
  bool remove_clones;
  /** Copy of the best solution for the current population. */
  Schedule* best = nullptr;
  /** Copy of the best solution for the whole run. */
  Schedule* global_best = nullptr;

  void addToPopulation(Schedule** pop, int* i, Schedule* sample);

  /** Updates best result for the current generation and the global best. */
  void update_best();
};

#endif  // MS_RCPSP_ALGORITHM_H
