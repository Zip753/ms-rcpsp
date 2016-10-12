#ifndef MS_RCPSP_POPULATION_H
#define MS_RCPSP_POPULATION_H

#include <cstdio>

#include "Schedule.h"

/** @brief Representation of population, i.e. set of specimen (schedules). */
template <class T>
class Population {
 public:
  /**
   * Creates the population from the list of scecimen.
   * @param size Size of population.
   * @param t List of specimen.
   */
  Population(int size, T** t) : genotype(t), n(size) {}

  ~Population();

  /** Returns size of the population. */
  int size() const { return n; }

  /** Returns specimen with the smallest fitness function in the population. */
  T* best();

  /** List of specimen. */
  T** genotype;

  /**
   * Shows statistical information of the population: best, average and worst
   * specimen.
   * @param stream Destination file stream.
   */
  void showStat(FILE* stream);

 private:
  /** Size of the population. */
  int n;
};

#include "../src/Population.tpp"

#endif  // MS_RCPSP_POPULATION_H
