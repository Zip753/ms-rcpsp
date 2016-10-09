#ifndef MS_RCPSP_TOURNAMENTSELECTOR_H
#define MS_RCPSP_TOURNAMENTSELECTOR_H

#include "Population.h"
#include "Selector.h"

/** @brief Implementation of tournament selection operator. */
class TournamentSelector : public Selector {
 public:
  /** @param _n Tournament size. */
  TournamentSelector(int _n) : n(_n) {}

  Schedule* select(Population* p) const override;

 private:
  /** Size of the tournament. */
  const int n;
};

#endif  // MS_RCPSP_TOURNAMENTSELECTOR_H
