#ifndef MS_RCPSP_SCHEDULE_H
#define MS_RCPSP_SCHEDULE_H

#include <cstdio>
#include "Task.h"

/**
 * Abstract base class for schedule representations.
 */
class Schedule {
 public:
  /** Prints current state to stdout. */
  void printState(bool short_output);

  /** Outputs solution to file stream in compatible format. */
  void writeToFile(FILE *stream);

  /** Checks schedule equality. */
  bool eq(Schedule* s);

  virtual ~Schedule() {}

  /** List of resources assigned to corresponding tasks. */
  int *ires;

  /** List of task start times. */
  int *start;

  /** Returns number of tasks. */
  int size() { return n; }

  /** Calculates fitness function. Caches result in _fitness. */
  int fitness();

  /**
   * Returns index of resource assigned to the task at index i.
   * @param i Index of the task.
   */
  inline int resource(int i) { return tasks[i]->res[ires[i]]; }

  /**
   * Number of resources capable of performing task at index i.
   * @param i Index of the task.
   */
  int max_res_count(int i) { return tasks[i]->res_size(); }

 protected:
  Schedule();
  Schedule(int* _ires) : Schedule() { ires = _ires; }

  /** Number of tasks. */
  int n;

  /** Cached fitness value for this specimen. */
  int _fitness = -1;

  /** List of tasks to complete. Shortcut to Project::tasks. */
  Task** tasks;

  /**
   * Finish time of the task at index i.
   * @param i Index of the task.
   */
  inline int finish_time(int i) { return start[i] + tasks[i]->duration; }

  /** Computes fitness and writes it to _fitness cache variable. */
  virtual void compute_fitness() = 0;
};

#endif  // MS_RCPSP_SCHEDULE_H
