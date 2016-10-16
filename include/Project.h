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
  static void create(int _n,
                     const std::vector<Task*> &_tasks,
                     int _res_count,
                     const std::vector<int> &_res_id,
                     const std::vector<double> &_res_sal);

  /** Returns the number of tasks in the project. */
  inline static int size() { return _project->n; }

  /** Returns number of resources. */
  inline static int get_res_count() { return _project->res_count; }

  /**
   * Returns resource ID of the resource at the given index.
   * @param res index of the resource
   */
  inline static int get_res_id(int res) { return _project->res_id[res]; }

  /**
   * Returns the hourly salary of the resource at the given index.
   * @param res index of the resource
   */
  inline static double get_salary(int res) { return _project->res_salary[res]; }

  ~Project();

  static std::vector<Task*>& Tasks() { return _project->tasks; }

 private:
  /** List of project tasks. */
  std::vector<Task*> tasks;
  /** Number of tasks. */
  int n;
  /** IDs of resources. */
  std::vector<int> res_id;
  /** Salaries of resources. */
  std::vector<double> res_salary;
  /** Number of resources. */
  int res_count;
  /** Shortcut to Project. */
  static std::unique_ptr<Project> _project;
  /** @see ProjectReader::read() */
  Project(int _n, const std::vector<Task*> &_tasks, int _res_count,
          const std::vector<int> &_res_id, const std::vector<double> &_res_sal)
      : tasks(_tasks), n(_n), res_id(_res_id), res_salary(_res_sal),
        res_count(_res_count) {}
};

};  // namespace SchedulingProblem

#endif  // MS_RCPSP_PROJECT_H
