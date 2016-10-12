#ifndef MS_RCPSP_CROSSOVER_H
#define MS_RCPSP_CROSSOVER_H

#include "Random.h"
/**
 * @brief Abstract base class for crossover implementations.
 *
 * If you want to create a new crossover operator, you should create a new
 * subclass of Crossover and implement Crossover#cross function for all
 * specimen representations that you're using. For implementation example see
 * src/UniformCrossover.cpp.
 *
 * @param T Type of specimen representation, subclass of Schedule.
 */
template <class T>
class Crossover {
 private:
  /** Crossover probability. */
  double p_cross;

 protected:
  /**
   * Creates crossover operator with supplied probability.
   * @param _p_cross Probability of crossover.
   */
  Crossover(double _p_cross) : p_cross(_p_cross) {}

 public:
  virtual ~Crossover() = 0;

  /**
   * Takes two specimen and performs crossover on them. Results in a new object.
   */
  virtual T* cross(T* a, T* b) const = 0;

  /** Checks whether the crossover should take place. */
  inline bool should_cross() const { return Random::rand(p_cross); }
};

template <class T>
Crossover<T>::~Crossover() {}

#endif  // MS_RCPSP_CROSSOVER_H
