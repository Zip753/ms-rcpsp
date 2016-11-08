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
  /** Creates singleton instance. */
  static void create(size_t _n,
                     const std::vector<Task> &_tasks,
                     size_t _res_count,
                     const std::vector<int> &_res_id,
                     const std::vector<double> &_res_sal);

  /** Returns the number of tasks in the project. */
  inline static size_t size() { return project_->n; }

  /** Returns number of resources. */
  inline static size_t get_res_count() { return project_->res_count; }

  /**
   * Returns resource ID of the resource at the given index.
   * @param res index of the resource
   */
  inline static int get_res_id(size_t res) {
    return project_->res_id[res];
  }

  /**
   * Returns the hourly salary of the resource at the given index.
   * @param res index of the resource
   */
  inline static double get_salary(size_t res) {
    return project_->res_salary[res];
  }

  static Task& task(size_t i) { return project_->tasks_[i]; }

 private:
  /** List of project tasks. */
  std::vector<Task> tasks_;
  /** Number of tasks. */
  size_t n;
  /** IDs of resources. */
  std::vector<int> res_id;
  /** Salaries of resources. */
  std::vector<double> res_salary;
  /** Number of resources. */
  size_t res_count;
  /** Shortcut to Project. */
  static std::unique_ptr<Project> project_;
  /** @see ProjectReader::read() */
  Project(size_t _n, const std::vector<Task> &_tasks, size_t _res_count,
          const std::vector<int> &_res_id, const std::vector<double> &_res_sal)
      : tasks_(_tasks), n(_n), res_id(_res_id), res_salary(_res_sal),
        res_count(_res_count) {}
};

};  // namespace SchedulingProblem

#endif  // MS_RCPSP_PROJECT_H
