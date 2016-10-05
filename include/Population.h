#ifndef MS_RCPSP_POPULATION_H
#define MS_RCPSP_POPULATION_H

#include "Schedule.h"

class Selector;
class Population {
 public:
  Population(int size, Schedule **sln) : genotype(sln), n(size) {};
  Population(int size);
  ~Population();
  int size();
  Schedule *best();
  Schedule **genotype; // array of *Solution

  void showStat(FILE *stream);

 private:
  int n;
};

#endif // MS_RCPSP_POPULATION_H
