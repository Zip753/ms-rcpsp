#ifndef MS_RCPSP_ALGORITHM_H
#define MS_RCPSP_ALGORITHM_H

#include <cstdio>
#include <memory>

#include "Crossover.h"
#include "Mutator.h"
#include "Population.h"
#include "Schedule.h"
#include "Selector.h"

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
   * @param s Selection operator.
   * @param c Crossover operator.
   * @param m Mutation operator.
   */
  Algorithm(int pop_size,
            const Selector &s,
            const Crossover<T> &c,
            const Mutator<T> &m,
            int _steps = -1,
            bool _rem_clones = true);
  ~Algorithm();

  /**
   * Executes the genetic algorithm.
   * @param stream File stream for statistics output.
   * @return The most adapted specimen in all populations (best solution found).
   */
  std::shared_ptr<Schedule> solve(FILE* stream);

 private:
  Population* population;
  const Selector& selector;
  const Crossover<T>& crossover;
  const Mutator<T>& mutator;
  /** Number of generations. */
  int steps;
  /** If true, removes clones from the population. */
  bool remove_clones;
  /** Copy of the best solution for the current population. */
  std::shared_ptr<Schedule> best = nullptr;
  /** Copy of the best solution for the whole run. */
  std::shared_ptr<Schedule> global_best = nullptr;

  void addToPopulation(Schedule** pop, int* i, T* sample);

  /** Updates best result for the current generation and the global best. */
  void update_best();
};

#endif  // MS_RCPSP_ALGORITHM_H
