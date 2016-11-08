#ifndef MS_RCPSP_ONEPOINTCROSSOVER_H
#define MS_RCPSP_ONEPOINTCROSSOVER_H

#include "Crossover.h"

namespace EvolutionaryAlgorithm {

/** @brief Implementation of one-point crossover. */
template <class T>
class OnePointCrossover : public Crossover<T> {
 public:
  OnePointCrossover(double _p_cross) : Crossover<T>(_p_cross) {}
  std::unique_ptr<T> cross(const T& a, const T& b) const override;
};

};  // namespace EvolutionaryAlgorithm

#endif  // MS_RCPSP_ONEPOINTCROSSOVER_H
