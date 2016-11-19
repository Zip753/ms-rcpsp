#ifndef MS_RCPSP_CROSSOVER_H
#define MS_RCPSP_CROSSOVER_H

#include <bits/unique_ptr.h>
#include "Random.h"

using Util::Random;

namespace Solutions {
namespace EvolutionaryAlgorithm {

/**
 * @brief Abstract base class for crossover implementations.
 *
 * If you want to create a new crossover operator, you should create a new
 * subclass of Crossover and implement Crossover#Cross function for all
 * specimen representations that you're using. For implementation example see
 * src/UniformCrossover.cpp.
 *
 * @param T Type of specimen representation, subclass of Schedule.
 */
template <class T>
class Crossover {
 protected:
  /**
   * Creates crossover operator with supplied probability.
   * @param _p_cross Probability of crossover.
   */
  Crossover(double p_cross_) : p_cross_(p_cross_) {}

 public:
  /**
   * Takes two specimen and performs crossover on them. Results in a new object.
   * @param a first parent specimen.
   * @param b second parent specimen.
   * @return owning pointer to new specimen.
   */
  virtual std::unique_ptr<T> Cross(const T &a, const T &b) const = 0;

  /**
   * Checks whether the crossover should take place.
   * @return true if crossover should take place.
   */
  inline bool should_cross() const { return Random::rand(p_cross_); }

  virtual ~Crossover() = 0;

 private:
  /** Crossover probability. */
  double p_cross_;
};

template <class T>
Crossover<T>::~Crossover() {}

};  //  namespace EvolutionaryAlgorithm
};  // namespace Solutions

#endif  // MS_RCPSP_CROSSOVER_H
