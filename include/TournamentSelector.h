#ifndef MS_RCPSP_TOURNAMENTSELECTOR_H
#define MS_RCPSP_TOURNAMENTSELECTOR_H

#include "Population.h"
#include "Selector.h"

/** @brief Implementation of tournament selection operator. */
class TournamentSelector : public Selector {
 public:
  TournamentSelector(int _n) : Selector(_n) {}

  Schedule* select(Population* p) const override;
};

#endif  // MS_RCPSP_TOURNAMENTSELECTOR_H
