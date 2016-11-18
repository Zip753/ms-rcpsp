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

namespace EvolutionaryAlgorithm {

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
class GeneticAlgorithm : public Algorithm<T> {
 public:
  /**
   * @param pop_size Size of the population.
   * @param s Selection operator.
   * @param c Crossover operator.
   * @param m Mutation operator.
   */
  GeneticAlgorithm(size_t pop_size,
                   std::unique_ptr<Selector<T>> s,
                   std::unique_ptr<Crossover<T>> c,
                   std::unique_ptr<Mutator<T>> m,
                   size_t _steps,
                   bool _rem_clones = true);
  ~GeneticAlgorithm() {}

  /**
   * Executes the genetic algorithm.
   * @param stream File stream for statistics output.
   * @return The most adapted specimen in all populations (best solution found).
   */
  std::unique_ptr<T> optimize(std::ostream &stream) override;

 private:
  std::unique_ptr<Population<T>> population;
  std::unique_ptr<Selector<T>> selector;
  std::unique_ptr<Crossover<T>> crossover;
  std::unique_ptr<Mutator<T>> mutator;
  /** Number of generations. */
  size_t steps;
  /** If true, removes clones from the population. */
  bool remove_clones;
  /** Copy of the best solution for the current population. */
  std::unique_ptr<T> best = nullptr;
  /** Copy of the best solution for the whole run. */
  std::unique_ptr<T> global_best = nullptr;

  void TryRemoveClones(const std::vector<std::unique_ptr<T>> &pop, size_t idx,
                       T* sample);

  /** Updates best result for the current generation and the global best. */
  void update_best();
};

};  // namespace EvolutionaryAlgorithm

#include "../src/GeneticAlgorithm.tpp"

#endif  // MS_RCPSP_GENETICALGORITHM_H
