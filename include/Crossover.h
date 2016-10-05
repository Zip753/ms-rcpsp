#ifndef MS_RCPSP_CROSSOVER_H
#define MS_RCPSP_CROSSOVER_H

#include "Schedule.h"

class Crossover {
 private:
  double p_cross;

 public:
  Crossover(double _p_cross) : p_cross(_p_cross) {}
  virtual ~Crossover() {}
  virtual Schedule *cross(Schedule *a, Schedule *b) = 0;
  bool should_cross();
};

#endif // MS_RCPSP_CROSSOVER_H
