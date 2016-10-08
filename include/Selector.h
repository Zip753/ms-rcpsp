#ifndef MS_RCPSP_SELECTOR_H
#define MS_RCPSP_SELECTOR_H

#include "Population.h"
#include "Schedule.h"

/** @brief Implementation of tournament selection operator. */
class Selector {
 public:
  /** @param _n Tournament size. */
  Selector(int _n = 5) : n(_n) {}

  /** Selects the candidate specimen from the population. */
  Schedule* select(Population* p) const;

 private:
  /** Size of the tournament. */
  const int n;
};

#endif  // MS_RCPSP_SELECTOR_H
