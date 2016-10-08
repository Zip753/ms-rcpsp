#ifndef MS_RCPSP_SIMPLEMUTATOR_H
#define MS_RCPSP_SIMPLEMUTATOR_H

#include "Mutator.h"

template <class T>
class SimpleMutator : public Mutator<T> {
 public:
  SimpleMutator(double _p_mut) : Mutator<T>(_p_mut) {}

  T* mutate(T* sample) const override;

 private:
  virtual void mutate_gene(T* sample, int idx) const override;
};

#endif  // MS_RCPSP_SIMPLEMUTATOR_H
