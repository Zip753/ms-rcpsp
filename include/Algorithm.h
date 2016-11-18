#ifndef MS_RCPSP_ALGORITHM_H
#define MS_RCPSP_ALGORITHM_H

#include <memory>
#include <utility>

namespace EvolutionaryAlgorithm {

/** @brief Base abstract class for all optimization algorithms.
 * @param T Class of optimized parameter.
 */
template <class T>
class Algorithm {
 public:
  virtual std::unique_ptr<T> optimize(std::ostream &stream) = 0;

  std::unique_ptr<T> optimize() {
    std::ostream vain(0);
    return std::move(optimize(vain));
  }
};

};  // namespace EvolutionaryAlgorithm

#endif  // MS_RCPSP_ALGORITHM_H
