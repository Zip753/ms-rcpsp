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
  LAXCrossover(double _p_cross) : Crossover<T>(_p_cross) {}
  T* cross(T* a, T* b) const override;
};

};  // namespace EvolutionaryAlgorithm

#endif // MS_RCPSP_LAXCROSSOVER_H
