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
  virtual ~Schedule() = 0;

  /**
   * Calculates fitness function. Caches result in fitness_.
   * @return fitness value.
   * @see Schedule#compute_fitness
   * */
  int Fitness();

  double TotalCost() const;

  /** @return number of tasks. */
  size_t size() const { return size_; }

  inline Task& task(size_t i) const { return project_->task(i); }

  inline size_t capable_resource_idx(size_t i) const {
    return capable_resource_idx_[i];
  }

  inline void set_capable_resource_idx(size_t i, size_t new_idx) {
    capable_resource_idx_.at(i) = new_idx;
  }

  inline int start(size_t i) const { return start_[i]; }

  inline void set_start(size_t i, int new_start) { start_[i] = new_start; }

  /**
   * Returns index of resource assigned to i-th task.
   * @param i index of task.
   * @return index of resource assigned to the task.
   */
  inline size_t resource_idx(size_t i) const {
    return task(i).resource_idx(capable_resource_idx_[i]);
  }

  /**
   * Returns resource assigned to the task at index i.
   * @param i index of the task.
   */
  inline Resource& resource(size_t i) const {
    return project_->resource(resource_idx(i));
  }

  /** Reset schedule representation to random state. */
  virtual void Reset();

  /** Prints current state to stdout. */
  void PrintState(bool short_output);

  /**
   * Returns finish time of the task at index i.
   * @param i Index of the task.
   */
  inline int finish_time(size_t i) const {
    return start_[i] + task(i).duration();
  }

 protected:
  Schedule(Project* project_)
      : project_(project_), start_(std::vector<int>(project_->size(), 0)),
        size_(project_->size()) {}
  Schedule(Project* project_, std::vector<size_t> _ires)
      : Schedule(project_) { capable_resource_idx_ = _ires; }

  /**
   * Computes fitness and writes it to Schedule#_fitness cache variable.
   */
  virtual int ComputeDuration() = 0;

  /** Pointer to project for which the schedule is designated. */
  Project* project_;

  /** List of resources assigned to corresponding tasks. */
  std::vector<size_t> capable_resource_idx_;

  /** List of task start times. */
  std::vector<int> start_;

  /** Number of tasks. */
  size_t size_;

  bool operator==(const Schedule& other) const;

 private:
  /**
   * Cached fitness value for this specimen.
   * @see Schedule#fitness
   */
  int fitness_ = -1;
};

};  // namespace SchedulingProblem

#endif  // MS_RCPSP_SCHEDULE_H
