#ifndef MS_RCPSP_TOURNAMENTSELECTOR_H
#define MS_RCPSP_TOURNAMENTSELECTOR_H

#include "Population.h"
#include "Selector.h"

namespace EvolutionaryAlgorithm {

/** @brief Implementation of tournament selection operator. */
template <class T>
class TournamentSelector : public Selector<T> {
 public:
  /** @param _n Tournament size. */
  TournamentSelector(size_t _n) : n(_n) {}

  T* select(const Population<T>& p) const override;

 private:
  /** Size of the tournament. */
  const size_t n;
};

};  // namespace EvolutionaryAlgorithm

#include "../src/TournamentSelector.tpp"

#endif  // MS_RCPSP_TOURNAMENTSELECTOR_H
