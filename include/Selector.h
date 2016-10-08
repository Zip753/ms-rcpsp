#ifndef MS_RCPSP_SELECTOR_H
#define MS_RCPSP_SELECTOR_H

#include "Population.h"
#include "Schedule.h"

/** @brief Base abstract class for selection operators.
 *
 * If you want to implement your own selection operator, create a subclass of
 * Selector and override Selector#select function.
 */
class Selector {
 public:
  /** @param _n Tournament size. */
  Selector(int _n = 5) : n(_n) {}

  /** Selects the candidate specimen from the population. */
  virtual Schedule* select(Population* p) const = 0;

 protected:
  /** Size of the tournament. */
  const int n;
};

#endif  // MS_RCPSP_SELECTOR_H
