#ifndef MS_RCPSP_SCHEDULE_H
#define MS_RCPSP_SCHEDULE_H

#include "Task.h"

#include <cstdio>
#include <set>
#include <utility>

class Schedule {
 public:
  Schedule();
  Schedule(int *_ires, int *_prio);
  Schedule(Schedule *s);
  ~Schedule();

  int fitness();
  void show(bool sh = false);
  void show(FILE *stream);
  int size();

  int *ires;     // own
  int *prio;     // own, priorities of tasks
  int *start;    // own
  int *business; // own
  int max_res_count(int i);
  int resource(int i);
  bool eq(Schedule *s);

 private:
  int n;
  Task **tasks; // reference
  int _fitness = -1;

  bool *visited;

  void init(bool initialize); // constructor hook
  void fix_all();
  int finish_time(int i);
};

#endif // SCHEDULE_H
