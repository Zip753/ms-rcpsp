#ifndef MS_RCPSP_POPULATION_H
#define MS_RCPSP_POPULATION_H

#include <cstdio>
#include <vector>

#include "Schedule.h"

namespace EvolutionaryAlgorithm {

/** @brief Representation of population, i.e. set of specimen (schedules). */
template <class T>
class Population {
 public:
  /**
   * Creates the population from the list of scecimen. Transfers ownership of
   * all specimen to the new population.
   * @param spec List of specimen.
   */
  Population(std::vector<std::unique_ptr<T>>* spec);

  /** Returns size of the population. */
  size_t size() const { return n; }

  /** Returns specimen with the smallest fitness function in the population. */
  T* best();

  /** List of specimen. */
  std::vector<std::unique_ptr<T>> genotype;

  /**
   * Shows statistical information of the population: best, average and worst
   * specimen.
   * @param stream Destination file stream.
   */
  void showStat(FILE* stream);

 private:
  /** Size of the population. */
  size_t n;
};

};  // namespace EvolutionaryAlgorithm

#include "../src/Population.tpp"

#endif  // MS_RCPSP_POPULATION_H
