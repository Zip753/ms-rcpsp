#ifndef MS_RCPSP_GENETICALGORITHM_H
#define MS_RCPSP_GENETICALGORITHM_H

#include <cstdio>
#include <memory>

#include "Algorithm.h"
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
class GeneticAlgorithm : Algorithm<T> {
 public:
  /**
   * @param pop_size Size of the population.
   * @param s Selection operator.
   * @param c Crossover operator.
   * @param m Mutation operator.
   */
  GeneticAlgorithm(int pop_size,
                   const std::shared_ptr<Selector<T>> &s,
                   const std::shared_ptr<Crossover<T>> c,
                   const std::shared_ptr<Mutator<T>> &m,
                   int _steps = -1,
                   bool _rem_clones = true);
  ~GeneticAlgorithm();

  /**
   * Executes the genetic algorithm.
   * @param stream File stream for statistics output.
   * @return The most adapted specimen in all populations (best solution found).
   */
  std::shared_ptr<T> optimize(FILE* stream);

  std::shared_ptr<T> optimize() override { return optimize(nullptr); }

 private:
  Population<T>* population;
  std::shared_ptr<Selector<T>> selector;
  std::shared_ptr<Crossover<T>> crossover;
  std::shared_ptr<Mutator<T>> mutator;
  /** Number of generations. */
  int steps;
  /** If true, removes clones from the population. */
  bool remove_clones;
  /** Copy of the best solution for the current population. */
  std::shared_ptr<T> best = nullptr;
  /** Copy of the best solution for the whole run. */
  std::shared_ptr<T> global_best = nullptr;

  void addToPopulation(T** pop, int i, T* sample);

  /** Updates best result for the current generation and the global best. */
  void update_best();
};

#include "../src/GeneticAlgorithm.tpp"

#endif  // MS_RCPSP_GENETICALGORITHM_H
