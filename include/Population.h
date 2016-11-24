#ifndef MS_RCPSP_POPULATION_H
#define MS_RCPSP_POPULATION_H

#include <cstdio>
#include <vector>

#include "Schedule.h"

namespace Solutions {
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
  Population(std::vector<std::unique_ptr<T>> spec)
      : specimen_(std::move(spec)) {}

  /** @return size of the population. */
  size_t size() const { return specimen_.size(); }

  /** @return specimen with the smallest fitness function in the population. */
  T* Best();

  /** Returns specimen at given index.
   * @param i index od specimen.
   * @return pointer to the specimen. */
  T* specimen(size_t i) const { return specimen_[i].get(); }

  /**
   * Shows statistical information of the population: best, average and worst
   * specimen.
   * @param stream Destination file stream.
   */
  void ShowStat(std::ostream &stream);

 private:
  /** List of specimen. */
  std::vector<std::unique_ptr<T>> specimen_;
};

};  // namespace EvolutionaryAlgorithm
};  // namespace Solutions

#include "../src/Population.tpp"

#endif  // MS_RCPSP_POPULATION_H
