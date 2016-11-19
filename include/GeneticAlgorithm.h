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
   * @param population_ initial population.
   * @param selector_ selection operator.
   * @param crossover_ crossover operator.
   * @param mutator_ mutation operator.
   */
  GeneticAlgorithm(std::unique_ptr<Population<T>> population_,
                   std::unique_ptr<Selector<T>> selector_,
                   std::unique_ptr<Crossover<T>> crossover_,
                   std::unique_ptr<Mutator<T>> mutator_,
                   size_t steps_,
                   bool remove_clones_ = true) :
      population_(std::move(population_)), selector_(std::move(selector_)),
      crossover_(std::move(crossover_)), mutator_(std::move(mutator_)),
      steps_(steps_), remove_clones_(remove_clones_) {}
  ~GeneticAlgorithm() {}

  /**
   * Executes the genetic algorithm.
   * @param stream stream for statistics output.
   * @return the most adapted specimen in all populations (best found solution).
   */
  std::unique_ptr<T> optimize(std::ostream &stream) override;

 private:
  std::unique_ptr<Population<T>> population_;
  std::unique_ptr<Selector<T>> selector_;
  std::unique_ptr<Crossover<T>> crossover_;
  std::unique_ptr<Mutator<T>> mutator_;
  /** Number of generations. */
  size_t steps_;
  /** If true, removes clones from the population. */
  bool remove_clones_;
  /** Copy of the best solution for the current population. */
  std::unique_ptr<T> best_ = nullptr;
  /** Copy of the best solution for the whole run. */
  std::unique_ptr<T> global_best_ = nullptr;

  void TryRemoveClones(const std::vector<std::unique_ptr<T>> &pop, size_t idx,
                       T* sample);

  /** Updates best result for the current generation and the global best. */
  void UpdateBest();

  void MutateAndAddToPopulation(std::vector<std::unique_ptr<T>>* next_pop,
                                size_t* iter, const T &a);
};

};  // namespace EvolutionaryAlgorithm

#include "../src/GeneticAlgorithm.tpp"

#endif  // MS_RCPSP_GENETICALGORITHM_H
