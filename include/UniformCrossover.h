#ifndef MS_RCPSP_UNIFORMCROSSOVER_H
#define MS_RCPSP_UNIFORMCROSSOVER_H

#include "Crossover.h"

namespace EvolutionaryAlgorithm {

/** @brief Implementation of uniform crossover. */
template <class T>
class UniformCrossover : public Crossover<T> {
 public:
  UniformCrossover(double _p_cross) : Crossover<T>(_p_cross) {}
  std::unique_ptr<T> cross(const T& a, const T& b) const override;
};

};  // namespace EvolutionaryAlgorithm

#endif  // MS_RCPSP_UNIFORMCROSSOVER_H
