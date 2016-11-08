#ifndef MS_RCPSP_SIMPLEMUTATOR_H
#define MS_RCPSP_SIMPLEMUTATOR_H

#include "Mutator.h"

namespace EvolutionaryAlgorithm {

/** @brief Implementation of simple mutation operator. */
template <class T>
class SimpleMutator : public Mutator<T> {
 public:
  SimpleMutator(double _p_mut) : Mutator<T>(_p_mut) {}

  std::unique_ptr<T> mutate(const T& sample) const override;

 private:
  void mutate_gene(T* sample, size_t idx) const override;
};

};  // namespace EvolutionaryAlgorithm

#endif  // MS_RCPSP_SIMPLEMUTATOR_H
