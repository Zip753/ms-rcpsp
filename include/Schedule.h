#ifndef MS_RCPSP_SCHEDULE_H
#define MS_RCPSP_SCHEDULE_H

#include <cstdio>

#include "Task.h"

/**
 * @brief Base abstract class for specimen (schedule) representations.
 *
 * If you want to implement your own representation of schedule, you must
 * create a subclass of Schedule and implement Schedule#compute_fitness
 * function. Then you have to instantiate all Crossover and Mutator operators
 * you're going to use for your new subclass. For instantiation example see
 * src/UniformCrossover.cpp.
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

  /**
   * Calculates fitness function. Caches result in _fitness.
   * @see Schedule#compute_fitness
   * */
  int fitness();

  /**
   * Returns index of resource assigned to the task at index i.
   * @param i Index of the task.
   */
  inline int resource(int i) { return tasks[i]->res[ires[i]]; }

  /**
   * Returns number of resources capable of performing task at index i.
   * @param i Index of the task.
   */
  int max_res_count(int i) { return tasks[i]->res_size(); }

 protected:
  Schedule();
  Schedule(int* _ires) : Schedule() { ires = _ires; }

  /** Number of tasks. */
  int n;

  /**
   * Cached fitness value for this specimen.
   * @see Schedule#fitness
   */
  int _fitness = -1;

  /** List of tasks to complete. Shortcut to Project::tasks. */
  Task** tasks;

  /**
   * Returns finish time of the task at index i.
   * @param i Index of the task.
   */
  inline int finish_time(int i) { return start[i] + tasks[i]->duration; }

  /**
   * Computes fitness and writes it to Schedule#_fitness cache variable.
   */
  virtual void compute_fitness() = 0;
};

#endif  // MS_RCPSP_SCHEDULE_H
