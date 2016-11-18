#ifndef MS_RCPSP_PROJECT_H
#define MS_RCPSP_PROJECT_H

#include <memory>
#include <vector>

#include "Task.h"

namespace SchedulingProblem {

/**
 * @brief Singleton representation of project in the scheduling problem.
 */
class Project {

 public:
  Project(const std::vector<Task> &tasks_,
          const std::vector<int> &res_id_,
          const std::vector<double> &res_salary_);

  /** Returns the number of tasks in the project. */
  inline size_t size() const { return tasks_.size(); }

  /** Returns number of resources. */
  inline size_t num_resources() const { return res_id_.size(); }

  /**
   * Returns resource ID of the resource at the given index.
   * @param res index of the resource
   */
  inline int resource_id(size_t res) const { return res_id_[res]; }

  /**
   * Returns the hourly salary of the resource at the given index.
   * @param res index of the resource
   */
  inline double resource_salary(size_t res) const { return res_salary_[res]; }

  Task& task(size_t i) { return tasks_[i]; }

 private:
  /** List of project tasks. */
  std::vector<Task> tasks_;
  /** IDs of resources. */
  std::vector<int> res_id_;
  /** Salaries of resources. */
  std::vector<double> res_salary_;
};

};  // namespace SchedulingProblem

#endif  // MS_RCPSP_PROJECT_H
