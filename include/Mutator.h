#ifndef MS_RCPSP_MUTATOR_H
#define MS_RCPSP_MUTATOR_H

#include "Schedule.h"

class Mutator {
 public:
  Mutator(double _p_mut) : p_mut(_p_mut) {};
  // create new sample that is a probable mutation of given one
  Schedule *mutate(Schedule *sample);
  // mutate given sample without creating a new one
  void force_mutate(Schedule *sample);

 private:
  double p_mut;
  void mutate_gene(Schedule *sample, int idx);
};

#endif // MS_RCPSP_MUTATOR_H
