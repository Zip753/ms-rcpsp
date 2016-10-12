#ifndef MS_RCPSP_ALGORITHM_H
#define MS_RCPSP_ALGORITHM_H

#include <memory>

/** @brief Base abstract class for all optimization algorithms.
 * @param T Class of optimized parameter.
 */
template <class T>
class Algorithm {
 public:
  virtual std::shared_ptr<T> optimize() = 0;
};

#endif  // MS_RCPSP_ALGORITHM_H
