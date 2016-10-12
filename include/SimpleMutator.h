#ifndef MS_RCPSP_SIMPLEMUTATOR_H
#define MS_RCPSP_SIMPLEMUTATOR_H

#include "Mutator.h"

namespace EvolutionaryAlgorithm {

/** @brief Implementation of simple mutation operator. */
template <class T>
class SimpleMutator : public Mutator<T> {
 public:
  SimpleMutator(double _p_mut) : Mutator<T>(_p_mut) {}

  T* mutate(T* sample) const override;

 private:
  virtual void mutate_gene(T* sample, int idx) const override;
};

};  // namespace EvolutionaryAlgorithm

#endif  // MS_RCPSP_SIMPLEMUTATOR_H
