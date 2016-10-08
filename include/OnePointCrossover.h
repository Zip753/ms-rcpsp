#ifndef MS_RCPSP_ONEPOINTCROSSOVER_H
#define MS_RCPSP_ONEPOINTCROSSOVER_H

#include "Crossover.h"

/** @brief Implementation of one-point crossover. */
template <class T>
class OnePointCrossover : public Crossover<T> {
 public:
  OnePointCrossover(double _p_cross) : Crossover<T>(_p_cross) {}
  T* cross(T* a, T* b) const override;
};

#endif  // MS_RCPSP_ONEPOINTCROSSOVER_H
