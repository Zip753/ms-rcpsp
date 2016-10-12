#ifndef MS_RCPSP_SCHEDULE_H
#define MS_RCPSP_SCHEDULE_H

#include <cstdio>

#include "Task.h"

namespace SchedulingProblem {

class Validator;

/**
 * @brief Base abstract class for specimen (schedule) representations.
 *
 * If you want to implement your own representation of schedule, you must
 * create a subclass of Schedule and implement Schedule#compute_fitness
 * function. Then you have to instantiate all Crossover and Mutator operators
 * you're going to use for your new subclass. For instantiation example see
 * src/UniformCrossover.cpp. Finally, you have to define equality operator,
 * for clone removal to work.
 */
class Schedule {
 public:
  /** Prints current state to stdout. */
  void printState(bool short_output);

  /** Outputs solution to file stream in compatible format. */
  void writeToFile(FILE* stream);

  virtual ~Schedule() = 0;

  /** List of resources assigned to corresponding tasks. */
  int* ires;

  /** List of task start times. */
  int* start;

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
  inline int resource(int i) const { return tasks[i]->res[ires[i]]; }

  /**
   * Returns number of resources capable of performing task at index i.
   * @param i Index of the task.
   */
  int max_res_count(int i) const { return tasks[i]->res_size(); }

  /** Reset schedule representation to random state. */
  virtual void reset() = 0;

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
  inline int finish_time(int i) const { return start[i] + tasks[i]->duration; }

  /**
   * Computes fitness and writes it to Schedule#_fitness cache variable.
   */
  virtual int compute_fitness() = 0;

  friend class Validator;
};

};  // namespace SchedulingProblem

#endif  // MS_RCPSP_SCHEDULE_H
