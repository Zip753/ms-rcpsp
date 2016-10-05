#ifndef MS_RCPSP_LAXCROSSOVER_H
#define MS_RCPSP_LAXCROSSOVER_H

#include "Crossover.h"
#include "Schedule.h"

#include <utility>

class LAXCrossover : public Crossover {
 public:
  LAXCrossover(double _p_cross) : Crossover(_p_cross) {}
  Schedule *cross(Schedule *a, Schedule *b);
};

#endif // MS_RCPSP_LAXCROSSOVER_H
