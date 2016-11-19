#ifndef MS_RCPSP_TASK_H
#define MS_RCPSP_TASK_H

#include <cstdlib>
#include <vector>

namespace SchedulingProblem {

/** @brief Representation of task. */
class Task {
 public:
  /**
   * @param id_ ID of the task.
   * @param duration_ Duration of the task.
   * @param dependencies_ List of dependencies.
   * @param resources_ List of capable resources.
   */
  Task(int id_, int duration_, std::vector<size_t> dependencies_,
       std::vector<size_t> resources_) : id_(id_), duration_(duration_),
                                         dependency_(dependencies_),
                                         resource_(resources_) {}
  ~Task();

  inline int id() const { return id_; }

  inline int duration() const { return duration_; }

  inline size_t resource(size_t i) const { return resource_[i]; }

  /** Returns number of resources capable of completing the task. */
  inline size_t num_resources() const { return resource_.size(); }

  inline size_t dependency(size_t i) const { return dependency_[i]; }

  /** Returns number of dependencies, i.e. tasks that have to be completed
   * before this task. */
  inline size_t num_dependencies() const { return dependency_.size(); }

 private:
  /** Task ID, as specified in input file. */
  int id_;
  /** Task duration. */
  int duration_;
  /** List of dependencies, i.e. tasks that have to be completed before this
   * task. */
  std::vector<size_t> dependency_;
  /** List of resources capable of completing the task. */
  std::vector<size_t> resource_;
};

};  // namespace SchedulingProblem

#endif  // MS_RCPSP_TASK_H
