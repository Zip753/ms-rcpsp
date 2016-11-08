#ifndef MS_RCPSP_TASK_H
#define MS_RCPSP_TASK_H

#include <cstdlib>
#include <vector>

namespace SchedulingProblem {

/** @brief Representation of task. */
class Task {
 public:
  /**
   * @param _id ID of the task.
   * @param _dur Duration of the task.
   * @param _ndep Number of dependencies.
   * @param _dep List of dependencies.
   * @param _nres Number of capable resources.
   * @param _res List of capable resources.
   */
  Task(int _id, int _dur, std::vector<size_t> _dep, std::vector<size_t> _res)
      : id_(_id), duration_(_dur), dependency_(_dep), resource_(_res) {}
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

  // TODO: make next private.
  /** List of inverse dependencies. */
  std::vector<size_t> next;

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
