#ifndef MS_RCPSP_UNIFORMCROSSOVER_H
#define MS_RCPSP_UNIFORMCROSSOVER_H

#include "Crossover.h"

/** @brief Implementation of uniform crossover. */
template <class T>
class UniformCrossover : public Crossover<T> {
 public:
  UniformCrossover(double _p_cross) : Crossover<T>(_p_cross) {}
  T* cross(T* a, T* b) const override;
};

#endif  // MS_RCPSP_UNIFORMCROSSOVER_H
