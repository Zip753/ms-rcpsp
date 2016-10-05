#ifndef MS_RCPSP_SELECTOR_H
#define MS_RCPSP_SELECTOR_H

#include "Population.h"
#include "Schedule.h"

class Population;
class Selector {
 public:
  Selector(int _n = 5) : n(_n) {};
  Schedule *select(Population *p);

 private:
  int n;
};

#endif // MS_RCPSP_SELECTOR_H
