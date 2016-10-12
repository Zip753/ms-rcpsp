#ifndef MS_RCPSP_SELECTOR_H
#define MS_RCPSP_SELECTOR_H

#include "Population.h"
#include "Schedule.h"

/** @brief Base abstract class for selection operators.
 *
 * If you want to implement your own selection operator, create a subclass of
 * Selector and override Selector#select function.
 */
template <class T>
class Selector {
 public:
  /** Selects the candidate specimen from the population. */
  virtual T* select(const Population<T>& p) const = 0;

  virtual ~Selector() = 0;
};

template <class T>
Selector<T>::~Selector() {}

#endif  // MS_RCPSP_SELECTOR_H
