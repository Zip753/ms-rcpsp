#ifndef MS_RCPSP_PRIOSCHEDULE_H
#define MS_RCPSP_PRIOSCHEDULE_H

#include <cstdio>
#include <set>
#include <utility>

#include "Task.h"
#include "Schedule.h"

class PrioSchedule : public Schedule {
 public:
  PrioSchedule();
  PrioSchedule(int *_ires, int *_prio);
  PrioSchedule(PrioSchedule *s);
  ~PrioSchedule();

  void compute_fitness();

  int *prio;     // own, priorities of tasks
  int *business; // own

 private:
  bool *visited;

  void init(bool initialize); // constructor hook
  void fix_all();
};

#endif  // MS_RCPSP_PRIOSCHEDULE_H
