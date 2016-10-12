#ifndef MS_RCPSP_MUTATOR_H
#define MS_RCPSP_MUTATOR_H

#include "Project.h"
#include "Random.h"
#include "Schedule.h"

using SchedulingProblem::Project;
using Util::Random;

namespace EvolutionaryAlgorithm {

/** @brief Base class for mutation operators.
 *
 * If you want to implement your own mutation operator, create a subclass of
 * Mutator and implement Mutator#mutate and Mutator#mutate_gene functions.
 */
template <class T>
class Mutator {
 public:
  /** @param _p_mut Mutation probability. */
  Mutator(double _p_mut) : p_mut(_p_mut) {};

  /** Performs mutation on the given sample. Returns new sample instance. */
  virtual T* mutate(T* sample) const = 0;

  /**
   * Mutates given sample without creating a new one.
   * Used to force mutation in the specimen for clone removal.
   */
  void force_mutate(T* sample) const {
    int idx = Random::randint() % Project::get()->size();
    mutate_gene(sample, idx);
  }

  virtual ~Mutator() = 0;

 protected:
  /** Mutation probability. */
  double p_mut;

  /**
   * Mutates single gene in the specimen.
   * @param sample Specimen to operate on.
   * @param idx Index of the gene to be mutated.
   */
  virtual void mutate_gene(T* sample, int idx) const = 0;
};

template <class T>
Mutator<T>::~Mutator() {}

};  // namespace EvolutionaryAlgorithm

#endif  // MS_RCPSP_MUTATOR_H
