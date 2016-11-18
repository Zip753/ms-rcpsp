#ifndef MS_RCPSP_LAXCROSSOVER_H
#define MS_RCPSP_LAXCROSSOVER_H

#include "Crossover.h"

namespace EvolutionaryAlgorithm {

/**
 * @brief Implementation of Least Assignments Crossover.
 *
 * For detailed desciption please refer to:
 * http://imopse.ii.pwr.edu.pl/files/Pages_57_62_Mendel2013_PRESS.pdf
 */
template <class T>
class LAXCrossover : public Crossover<T> {
 public:
  LAXCrossover(double p_cross_) : Crossover<T>(p_cross_) {}
  std::unique_ptr<T> Cross(const T& a, const T& b) const override;
};

};  // namespace EvolutionaryAlgorithm

#endif // MS_RCPSP_LAXCROSSOVER_H
