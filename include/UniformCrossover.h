#ifndef MS_RCPSP_UNIFORMCROSSOVER_H
#define MS_RCPSP_UNIFORMCROSSOVER_H

#include "Crossover.h"

namespace Solutions {
namespace EvolutionaryAlgorithm {

/** @brief Implementation of uniform crossover. */
template <class T>
class UniformCrossover : public Crossover<T> {
 public:
  UniformCrossover(double p_cross_) : Crossover<T>(p_cross_) {}
  std::unique_ptr<T> Cross(const T& a, const T& b) const override;
};

};  // namespace EvolutionaryAlgorithm
};  // namespace Solutions

#endif  // MS_RCPSP_UNIFORMCROSSOVER_H
