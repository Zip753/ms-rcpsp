#ifndef MS_RCPSP_TASK_H
#define MS_RCPSP_TASK_H

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
  Task(int _id, int _dur, std::vector<int> _dep, std::vector<int> _res)
      : id(_id), duration(_dur), dep(_dep), res(_res) {}
  ~Task();

  /** Task ID, as specified in input file. */
  int id;
  /** Task duration. */
  int duration;
  /** List of dependencies, i.e. tasks that have to be completed before this
   * task. */
  std::vector<int> dep;
  /** List of resources capable of completing the task. */
  std::vector<int> res;
  /** List of inverse dependencies. */
  std::vector<int> next;

  /** Returns number of resources capable of completing the task. */
  int res_size() const { return res.size(); }

  /** Returns number of dependencies, i.e. tasks that have to be completed
   * before this task. */
  int dep_size() const { return dep.size(); }
};

};  // namespace SchedulingProblem

#endif  // MS_RCPSP_TASK_H
