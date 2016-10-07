#ifndef MS_RCPSP_LAXCROSSOVER_H
#define MS_RCPSP_LAXCROSSOVER_H

#include "Crossover.h"

#include <utility>

template <class T>
class LAXCrossover : public Crossover<T> {
 public:
  LAXCrossover(double _p_cross) : Crossover<T>(_p_cross) {}
  T *cross(T *a, T *b);
};

#endif // MS_RCPSP_LAXCROSSOVER_H
