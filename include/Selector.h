#ifndef MS_RCPSP_SELECTOR_H
#define MS_RCPSP_SELECTOR_H

#include "Population.h"
#include "Schedule.h"

/**
 * Implementation of tournament selection operator.
 */
class Selector {
 public:
  /** @param _n tournament size, defaults to 5. */
  Selector(int _n = 5) : n(_n) {}

  /** Selects the candidate specimen from the population. */
  Schedule* select(Population *p);

 private:
  /** Size of the tournament. */
  int n;
};

#endif  // MS_RCPSP_SELECTOR_H
