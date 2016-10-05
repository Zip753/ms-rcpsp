#ifndef MS_RCPSP_UNIFORMCROSSOVER_H
#define MS_RCPSP_UNIFORMCROSSOVER_H

#include "Crossover.h"

class UniformCrossover : public Crossover {
 public:
  UniformCrossover(double _p_cross) : Crossover(_p_cross) {}
  Schedule *cross(Schedule *a, Schedule *b);
};

#endif // MS_RCPSP_UNIFORMCROSSOVER_H
