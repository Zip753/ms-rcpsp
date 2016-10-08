#ifndef MS_RCPSP_MUTATOR_H
#define MS_RCPSP_MUTATOR_H

#include "Schedule.h"
/**
 * Implementation of mutation operator.
 */
template <class T>
class Mutator {
 public:
  /**
   * @param _p_mut mutation probability.
   */
  Mutator(double _p_mut) : p_mut(_p_mut) {};

  /** Performs mutation on the given sample. Returns new sample instance. */
  T *mutate(T *sample);

  /**
   * Mutates given sample without creating a new one.
   * Used to force mutation in the specimen for clone removal.
   */
  void force_mutate(Schedule* sample);

 private:
  /** Mutation probability. */
  double p_mut;

  /**
   * Mutates single gene in the specimen.
   * @param sample Specimen to operate on.
   * @param idx Index of the gene to be mutated.
   */
  void mutate_gene(T *sample, int idx);
};

#endif  // MS_RCPSP_MUTATOR_H
