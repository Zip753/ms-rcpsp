#ifndef MS_RCPSP_SCHEDULE_H
#define MS_RCPSP_SCHEDULE_H

#include <cstdio>
#include <cstdlib>
#include <vector>

#include "Project.h"
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
  void PrintState(bool short_output);

  /** Outputs solution to file stream in compatible format. */
  void Write(std::ostream &stream);

  virtual ~Schedule() = 0;

  /** List of resources assigned to corresponding tasks. */
  std::vector<size_t> ires;

  /** List of task start times. */
  std::vector<int> start;

  /** Returns number of tasks. */
  size_t size() const { return n; }

  /**
   * Calculates fitness function. Caches result in _fitness.
   * @see Schedule#compute_fitness
   * */
  int fitness();

  Task& task(size_t i) const { return Project::task(i); }

  /**
   * Returns index of resource assigned to the task at index i.
   * @param i Index of the task.
   */
  inline size_t resource(size_t i) const { return task(i).resource(ires[i]); }

  /**
   * Returns number of resources capable of performing task at index i.
   * @param i Index of the task.
   */
  size_t max_res_count(size_t i) const { return task(i).num_resources(); }

  /** Reset schedule representation to random state. */
  virtual void reset() = 0;

 protected:
  Schedule();
  Schedule(std::vector<size_t> _ires) : Schedule() { ires = _ires; }

  /** Number of tasks. */
  size_t n;

  /**
   * Cached fitness value for this specimen.
   * @see Schedule#fitness
   */
  int _fitness = -1;

  /**
   * Returns finish time of the task at index i.
   * @param i Index of the task.
   */
  inline int finish_time(size_t i) const {
    return start[i] + task(i).duration();
  }

  /**
   * Computes fitness and writes it to Schedule#_fitness cache variable.
   */
  virtual int compute_fitness() = 0;

  friend class Validator;
};

};  // namespace SchedulingProblem

#endif  // MS_RCPSP_SCHEDULE_H
