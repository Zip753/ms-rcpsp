#ifndef MS_RCPSP_POPULATION_H
#define MS_RCPSP_POPULATION_H

#include <cstdio>

#include "Schedule.h"

/**
 * Representation of population, i.e. set of specimen (schedules).
 * @param T Type of specimen class.
 */
class Population {
 public:
  /**
   * Creates the population from the list of scecimen.
   * @param size Size of population.
   * @param t List of specimen.
   */
  Population(int size, Schedule** t) : genotype(t), n(size) {}

  ~Population();

  /** Size of the population. */
  int size();

  /** Specimen with the smallest fitness function in the population. */
  Schedule* best();

  /** List of specimen. */
  Schedule** genotype;

  /**
   * Shows statistical information of the population: best, average and worst
   * specimen.
   * @param stream Destination file stream.
   */
  void showStat(FILE *stream);

 private:
  /** Size of the population. */
  int n;
};

#endif  // MS_RCPSP_POPULATION_H
