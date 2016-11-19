#ifndef MS_RCPSP_TOURNAMENTSELECTOR_H
#define MS_RCPSP_TOURNAMENTSELECTOR_H

#include "Population.h"
#include "Selector.h"

namespace Solutions {
namespace EvolutionaryAlgorithm {

/** @brief Implementation of tournament selection operator. */
template <class T>
class TournamentSelector : public Selector<T> {
 public:
  /** @param tourn_size_ tournament size. */
  TournamentSelector(size_t tourn_size_) : tournament_size_(tourn_size_) {}

  T* Select(const Population<T> &p) const override;

 private:
  /** Size of the tournament. */
  const size_t tournament_size_;
};

};  // namespace EvolutionaryAlgorithm
};  // namespace Solutions

#include "../src/TournamentSelector.tpp"

#endif  // MS_RCPSP_TOURNAMENTSELECTOR_H
