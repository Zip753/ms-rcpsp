#ifndef MS_RCPSP_ONEPOINTCROSSOVER_H
#define MS_RCPSP_ONEPOINTCROSSOVER_H

#include "Crossover.h"

namespace Solutions {
namespace EvolutionaryAlgorithm {

/** @brief Implementation of one-point crossover. */
template <class T>
class OnePointCrossover : public Crossover<T> {
 public:
  OnePointCrossover(double p_cross_) : Crossover<T>(p_cross_) {}
  std::unique_ptr<T> Cross(const T& a, const T& b) const override;
};

};  // namespace EvolutionaryAlgorithm
};  // namespace Solutions

#endif  // MS_RCPSP_ONEPOINTCROSSOVER_H
